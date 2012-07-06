
#ifndef PROJECT_CONFIG_H
#define PROJECT_CONFIG_H

#include <QString>
#include "common.h"

class EXPORT_COMMON CConfig
{
public:

	static CConfig* instance();

	static QString getSubDirName(const QString& fileName);

	QString getLogDir();
	QString getConfigDir();
	QString getDataDir();
	QString getGraphDir();
	QString getElementDir();
	QString getBayDir();
	QString getImageDir();
	QString getImagePath(const QString& fileName);
	QString getFilePath(const QString& fileName);
	QString getQmlDir();
	QString getDisplayDir();
	QString getCurveDir();
	QString getTableDir();
	QString getBackupDir();

	QString getConfigValue(const QString& fileName,const QString& groupName,const QString& attrName);

private:

	CConfig();

	void init();

private:

	QString		m_home;
	QString		m_dataHome;
	
};

#endif