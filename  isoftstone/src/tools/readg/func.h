
#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
#include <QtXml>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QDomDocument>
#include <QStringList>
#include <istream>
#include <iostream>
#include <QMutex>
#include <QMutexLocker>
#include <QThreadPool>
#include <QSettings>
#include <time.h>

#include <qtconcurrentmap.h>
#ifndef QT_NO_CONCURRENT
using namespace QtConcurrent;
#endif

void createInfo_H(std::string dir);
QString getTabSpace(QString strText);
QStringList getGFileDir(const QString& dirName);
QStringList getGFileRecusive(const QString& dirName);
QStringList getFileRecusive(const QString& dirName,const QStringList& filters);
void statistics(const QString& fileName,QMap<QString,QStringList>& classMap);
QMap<QString,QStringList> statistics(const QString& fileName);
QMap<QString,QStringList> statistics_m(const QString& fileName);
void reduce(QMap<QString,QStringList>& resultMap,const QMap<QString,QStringList>& oneMap);
void print(const QString& fileName,const QMap<QString,QStringList>& classMap);
void print(const QString& fileName,const QMap<QString,QString>& attrValue);
void print(const QString& fileName,const QStringList& attrLst);
void printEnum(const QString& source,const QString& dest);
void printClass(QMap<QString,QStringList> classMap);
void printImplHClass(QMap<QString,QStringList> classMap);
void printImplCPPClass(QMap<QString,QStringList> classMap);
void printClassFactory_H(QMap<QString,QStringList> classMap);
void printClassFactory_CPP(QMap<QString,QStringList> classMap);
void printClass(const QString& file,int nOp);
void readType(const QString& fileName,QMap<QString,QString>& attrType);

inline bool caseInsensitiveLessThan(const QString &s1, const QString &s2)
{
	return s1.toLower() < s2.toLower();
}

inline QString getAutoHome()
{
	QByteArray br = qgetenv("STONEDIR");
	QString dirHome = br.data();
	QString autoDir = dirHome + "/src/auto_element/";
	return autoDir;
}


#endif