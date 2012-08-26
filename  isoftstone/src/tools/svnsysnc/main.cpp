
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QList>
#include <QFileInfo>
#include <QStringList>
#include <QDebug>
#include <QSettings>
#include <QtCore>
#include <QThreadPool>
#include <iostream>

// 用于记录添加和删除的操作，保存到文件中

enum ESVNOP
{
	eSVN_ADD,
	eSVN_DELETE,
	eSVN_MODIFY,
};

typedef QPair<ESVNOP,QString> CMDPair;

QList< CMDPair > g_CommandList;

void svnsync(const QString& sourceDir,const QString& destDir);

void svnadd(const QString& source,const QString& dest,bool bDir = false);
void svndelete(const QString& dest,bool bDir = false);
void svnmodify(const QString& source,const QString& dest);
bool isSvnDir(const QString& dir);	

int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

	QString sourceDir;
	QString destDir;
	if (argc > 2)
	{
		sourceDir = argv[1];
		destDir = argv[2];

		qDebug() << sourceDir;
		qDebug() << destDir;
		svnsync(sourceDir,destDir);
	}

	return 0;

}

void svnsync(const QString& strSource,const QString& strDest)
{
	// 加载源和目的地址 文件和文件夹，然后进行对比
	QFileInfo sourceInfo(strSource);
	QFileInfo destInfo(strDest);
	if (!sourceInfo.exists())
	{
		return;
	}
	if (sourceInfo.isDir()) // 文件夹
	{
		if (destInfo.exists())
		{
			QDir sourceDir(strSource);
			QDir destDir(strDest);
			QFileInfoList sourceDirList = sourceDir.entryInfoList(QDir::AllDirs|QDir::NoDot|QDir::NoDotDot);

			foreach(const QFileInfo& fileinfo,sourceDirList)
			{
				// 递归处理每一个文件或者文件夹
				svnsync(fileinfo.absoluteFilePath(),strDest + "/" + fileinfo.fileName());
			}
		}
		else // 不存在则拷贝目录
		{
			svnadd(strSource,strDest);
		}
	}
	else if(sourceInfo.isFile())
	{
		if (destInfo.exists())
		{
			svnmodify(strSource,strDest);
		}
		else
		{
			svnadd(strSource,strDest);
		}
	}
}

void svnadd(const QString& source,const QString& dest,bool bDir)
{
	CMDPair pair;
	pair.first = eSVN_ADD;
	pair.second = "copy " + source + " " + dest; 
	g_CommandList.append(pair);

	pair.first = eSVN_ADD;
	pair.second = "svn add "+ dest;
	g_CommandList.append(pair);
}

void svndelete(const QString& dest,bool bDir )
{
	if (isSvnDir(dest))
	{
		CMDPair pair;
		pair.first = eSVN_DELETE;
		if (bDir)
		{
			pair.second = "svn rm " + dest;
		}
		g_CommandList.append(pair);
	}
}

void svnmodify(const QString& source,const QString& dest)
{
	CMDPair pair;
	pair.first = eSVN_MODIFY;
	pair.second = "copy " + source + " " + dest; 
	g_CommandList.append(pair);
}

bool isSvnDir(const QString& strDir)
{
	QDir dir(strDir);
	QStringList dirList = dir.entryList(QDir::AllDirs|QDir::NoDot|QDir::NoDotDot);
	if (dirList.contains(".svn"))
	{
		return true;
	}
	return false;
}