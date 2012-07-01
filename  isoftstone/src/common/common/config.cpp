
#include "macro.h"
#include "config.h"
#include "setting.h"

CConfig* CConfig::instance()
{
	static CConfig* s_instance = NULL;
	if (!s_instance)
	{
		s_instance = new CConfig;
	}
	return s_instance;
}

QString CConfig::getSubDirName(const QString& fileName)
{
	QString subDir = fileName.section(".",1,1);
	return subDir;
}

CConfig::CConfig()
{
	init();
}

void CConfig::init()
{
	QByteArray qbr = qgetenv(PROJECT_HOME);
	m_home = QString(qbr.data());

	qbr = qgetenv(DATA_HOME);
	m_dataHome = QString(qbr.data());
}

QString CConfig::getLogDir()
{
	return m_home + "/log/";
}

QString CConfig::getConfigDir()
{
	return m_home + "/config/";
}

QString CConfig::getDataDir()
{
	return m_dataHome;
}

QString CConfig::getGraphDir()
{
	return m_dataHome + "/display/";
}

QString CConfig::getElementDir()
{
	return m_dataHome + "/element/";
}

QString CConfig::getBayDir()
{
	return m_dataHome + "/bay/";
}

QString CConfig::getImageDir()
{
	return m_dataHome + "/image/";
}

QString CConfig::getImagePath(const QString& fileName)
{
	return getImageDir() + fileName;
}

QString CConfig::getFilePath(const QString& fileName)
{
	QString subDir = getSubDirName(fileName);
	QString strFile = getDisplayDir() + subDir + "/" + fileName;
	return strFile;
}

QString CConfig::getQmlDir()
{
	return m_home + "/qml/";
}

QString CConfig::getDisplayDir()
{
	return m_dataHome + "/display/";
}

QString CConfig::getCurveDir()
{
	return m_dataHome + "/curve/";
}

QString CConfig::getTableDir()
{
	return m_dataHome + "/table/";
}

QString CConfig::getConfigValue(const QString& fileName,const QString& groupName,const QString& attrName)
{
	CSettings ct(getConfigDir() + fileName);
	QString strValue = "";
	if (!groupName.isEmpty())
	{
		ct.beginGroup(groupName);
		strValue = ct.value(attrName).toString();
		ct.endGroup();
	}
	else
	{
		strValue = ct.value(attrName).toString();
	}
	return strValue;
}