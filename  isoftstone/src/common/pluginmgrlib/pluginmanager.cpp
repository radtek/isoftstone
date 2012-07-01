/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: pluginmanager.cpp
** ժҪ: Ӧ�ó��������������ܶ�̬��
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2011.11.1
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2011.10.13   V1.0      ����
** ������	   2011.11.4    V1.0      �޸�
**
****************************************************************************/

#include "pluginmanager.h"
#include <QLibrary>
#include <QDir>
#include <QSettings>
#include <QCoreApplication>
#include <QDebug>

#include "macro.h"

IPluginBase* CPluginManager::getPlugin(const QString& pluginName)
{
	#ifdef Q_WS_WIN
		QString realPluginName = pluginName;
	#else
		QString realPluginName = QString("lib") + pluginName;
	#endif

	return m_pluginMap.value(realPluginName, NULL);
}


CPluginManager::CPluginManager()
{
	m_pMenuBar = NULL;
}


bool CPluginManager::loadPlugin(const QString& pluginName)
{
	bool bLoadOk = false;

	DLLFun fun = reinterpret_cast<DLLFun>(QLibrary::resolve(pluginName, "getPlugin"));
	IPluginBase* pPlugin;
	if(fun != NULL)
	{
		pPlugin = (*fun)();
		if (pPlugin != NULL)	//��������ɹ�
		{
			EPluginType eType = pPlugin->getPluginInfo().eType;
			m_pluginMap.insert(pluginName, pPlugin);
			m_pluginInfo[pluginName].bStatus = true;
			m_pluginInfo[pluginName].description = pPlugin->getPluginInfo().description;
			QString tmpStr = pPlugin->getPluginInfo().description;
			m_pluginInfo[pluginName].icon = pPlugin->getPluginInfo().icon;
			bLoadOk = true;
		}
		else
		{
			bLoadOk = false;
		}
	}
	return bLoadOk;
}

bool CPluginManager::setPluginEnabled(const QString& pluginName, bool bEnabled)
{	
	bool bRet = true;
	m_pluginInfo[pluginName].bStatus = bEnabled;
	// �Ѿ����ص�,����ʹ�ñ�־

	QMap<QString, IPluginBase*>::iterator it = m_pluginMap.find(pluginName);
	if(it != m_pluginMap.end())
	{		
		IPluginBase* pPlugin = (*it);
		IPluginApplication* pApp = dynamic_cast<IPluginApplication*>(pPlugin);
		if (pApp->isPluginEnabled() != bEnabled)
		{
			pApp->setPluginEnabled(bEnabled);
			
			m_pluginInfo[pluginName].bStatus = bEnabled;
			m_pluginInfo[pluginName].description = pPlugin->getPluginInfo().description;
		}
	}
	else
	{
		// ���û�м��ز���Ҫʹ�ã�����ز����ʹ��
		if (bEnabled == true)
		{
			if(loadPlugin(pluginName))	//���سɹ�
			{			
				IPluginBase* pPluginLib = m_pluginMap[pluginName];
				IPluginApplication* pApp = dynamic_cast<IPluginApplication*>(pPluginLib);
				pApp->setParentWindow(m_pParent);
				loadMenuBar(pPluginLib);
				m_pluginInfo[pluginName].bStatus = true;				
			}
			else
			{
				bRet = false;
				m_pluginInfo[pluginName].bStatus = false;
			}
		}
	}

	if(true == bRet)
	{
		savePluginStatus(pluginName, bEnabled);
	}

	return bRet;
}

QMap<QString, PluginInfo> CPluginManager::getPluginInfo()
{
	return m_pluginInfo;
}

void CPluginManager::loadMenuBar(IPluginBase* pPluginLib)
{
	if(!m_pMenuBar) return;
	IPluginApplication* pApp = dynamic_cast<IPluginApplication*>(pPluginLib);
	if (pApp)
	{
		pApp->load(m_pMenuBar);
		pApp->setPluginEnabled(true);
	}
}

void CPluginManager::loadDir()
{	

#ifdef Q_WS_WIN
	char* visdir = getenv(PROJECT_HOME);
	QString dirName = QString(visdir) + "/bin";
	QString ext = ".dll";

	QStringList filters ;
	filters << "pl_*.dll";
	filters << "em_*.dll";
	
#else
	QString ext = ".so";

	char* visdir = getenv(PROJECT_HOME);
	QString dirName = QString(visdir) + "/lib";
	QStringList filters ;
	filters << "libpl_*.so";
	filters << "libem_*.so";
#endif

	QDir dir(dirName);
	dir.setNameFilters(filters);
	dir.setFilter(QDir::Files);
	QStringList pluginList = dir.entryList();
	QStringList currentDirPlugin;	//�洢��ǰĿ¼���	

	foreach(QString pluginName, pluginList)
	{
		QString fileName = pluginName;
		QString baseName = pluginName.remove(ext,Qt::CaseInsensitive);
		
		// �����������Ĳ������������
		if(QLibrary::isLibrary(fileName))
		{
			currentDirPlugin.append(baseName);
		}
		
		// �����жϸò���Ƿ��������
		if(QLibrary::isLibrary(fileName)/* && enabledPlugins.contains(baseName)*/)
		{
			setPluginEnabled(pluginName,true);			
		}
		else
		{
			m_pluginInfo[baseName].bStatus = false;
		}
	}

	// ɾ�������Ϣ�в�������Ŀ¼�е�����
	foreach(QString pluginName, m_pluginInfo.keys())
	{
		if(!currentDirPlugin.contains(pluginName))
		{
			m_pluginInfo.remove(pluginName);
		}
	}
}

QStringList CPluginManager::loadEnabledPlugins()
{
	char* visdir = getEnvStr(PROJECT_HOME);
	QString settingName = QString(visdir) + "/config/plugin_manager.ini";
	QSettings settings(settingName, QSettings::IniFormat);
	settings.setIniCodec("GB2312");

	QStringList plugins = settings.childGroups();
	QStringList enabledPlugins;
	for (int i = 0; i < plugins.count(); i++) 
	{
		QString pluginName = plugins[i];
		settings.beginGroup(pluginName);
		bool bEnabled = settings.value("LOAD").toBool();
		if(bEnabled == true)
		{
			enabledPlugins.append(pluginName);
		}
		//QString description = settings.value("DESC").toString();
		//m_pluginInfo[pluginName].description = description;
		settings.endGroup();
	}
	return enabledPlugins;
}

void CPluginManager::clearPluginList()
{
	m_pluginInfo.clear();
}

void CPluginManager::initMenuBar(QMenuBar* pMenuBar)
{
	m_pMenuBar = pMenuBar;
	loadDir();
}

CPluginManager::~CPluginManager()
{
	destroy();
}

void CPluginManager::setParentWindow(QWidget* pParentWindow)
{
	m_pParent = pParentWindow;
	QMapIterator<QString,IPluginBase*> iter(m_pluginMap);
	while(iter.hasNext())
	{
		iter.next();
		QString pluginName = iter.key();
		bool bEnabled = m_pluginInfo.value(pluginName).bStatus;
		if(bEnabled)
		{
			iter.value()->setParentWindow(pParentWindow);
		}
	}
}

void CPluginManager::destroy()
{
	QMapIterator<QString, IPluginBase*> iter(m_pluginMap);
	while(iter.hasNext())
	{
		iter.next();
		IPluginBase* pPluginLib = iter.value();
		if(pPluginLib && pPluginLib->getPluginInfo().eType == eApplicationPlugin)
		{
			IPluginApplication* pApp = dynamic_cast<IPluginApplication*>(pPluginLib);
			if (pApp)
			{
				pApp->unload();
			}
		}
		//delete pPluginLib;
	}
}

void CPluginManager::savePluginStatus(const QString& pluginName, const bool& bEnabled)
{
	char* visdir = getEnvStr(PROJECT_HOME);
	QString settingName = QString(visdir) + "/config/plugin_manager.ini";
	QSettings settings(settingName, QSettings::IniFormat);
	settings.setIniCodec("GB2312");
	settings.beginGroup(pluginName);
	settings.setValue("LOAD", bEnabled);
	settings.endGroup();		
}

void CPluginManager::savePluginDescription(const QString& pluginName, const QString& description)
{
	char* visdir = getEnvStr(PROJECT_HOME);
	QString settingName = QString(visdir) + "/config/plugin_manager.ini";
	QSettings settings(settingName, QSettings::IniFormat);
	settings.setIniCodec("GB2312");
	settings.beginGroup(pluginName);
	settings.setValue("DESC", description);
	settings.endGroup();
	m_pluginInfo[pluginName].description = description;
}

char* CPluginManager::getEnvStr(const char*)
{
#ifdef WIN32	
	char* visdir;
	size_t len;
	_dupenv_s(&visdir, &len, PROJECT_HOME);
#else
	char* visdir;
	visdir = getenv(PROJECT_HOME);
#endif
	return visdir;
}

void CPluginManager::setDataPointer(const QMap<int,void*>& pointerMap,bool bApp)
{
	QMapIterator<QString,IPluginBase*> iter(m_pluginMap);
	while(iter.hasNext())
	{
		iter.next();
		QString pluginName = iter.key();
		IPluginBase* pPlugin = iter.value();
		bool bEnabled = m_pluginInfo.value(pluginName).bStatus;
		if(bEnabled)
		{
			pPlugin->setDataPointer(pointerMap);
		}
	}
}
