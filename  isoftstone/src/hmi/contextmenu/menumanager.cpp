

#include <QtGui>
#include <stdlib.h>
#include <QDir>

#include "macro.h"
#include "menumanager.h"
#include "cmloader.h"
#include "menuloader.h"

CMenuManager::CMenuManager(QObject* parent):QObject(parent)
{
	m_Parent = dynamic_cast<QWidget*>(parent);
}

CMenuManager::~CMenuManager()
{
}


void CMenuManager::init() 
{
	m_ActionLoader = new CMLoader;

	char* visdir = getenv(PROJECT_HOME);
#ifdef Q_WS_WIN
	QString dirName = QString(visdir) + "/bin";
	QString filter = "cm_*.dll";
#else
	QString dirName = QString(visdir) + "/lib";
	QString filter = "libcm_*.so";
#endif
	m_ActionLoader->loadBatchDLL(dirName,filter,"getPlugin");;
	m_MenuLoader = new CMenuLoader(this);
}

void CMenuManager::destroy() 
{
	if (m_MenuLoader)
	{
		delete m_MenuLoader;
		m_MenuLoader = NULL;
	}
}

void CMenuManager::onActionClick()
{
	QAction* pAction = qobject_cast<QAction*>(sender());
	if (pAction)
	{
		int nCommand =  pAction->data().toInt();
		IPluginAction* pAction = NULL;
		pAction = m_ActionLoader->getAction(nCommand);

		if (pAction)
		{
			pAction->onClick();
		}
		else
		{
			QMessageBox::information(m_Parent,tr("功能提示"),tr("此功能可能没有实现，请见谅！"));
		}
	}
}

QMenu* CMenuManager::getContextActions(int nMetaType, qint64 nAppType) 
{
	return m_MenuLoader->getMenu(nAppType,nMetaType);
}

IPluginAction* CMenuManager::getPluginAction(const QString& strCommand)
{
	return m_ActionLoader->getAction(strCommand);
}