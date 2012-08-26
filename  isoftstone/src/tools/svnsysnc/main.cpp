
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
	e_ADD,
	eSVN_ADD,
	eSVN_DELETE,
	eSVN_MODIFY,
	eSVN_SYNC,
	eSVN_REVERSE,
};

typedef QPair<ESVNOP,QString> CMDPair;

QList< CMDPair > g_CommandList;

void svnsync(const QString& sourceDir,const QString& destDir);		// 正向同步
void reversedelete(const QString& sourceDir,const QString& destDir); // 反向删除

QFileInfoList filterDir(const QFileInfoList& allInfo);

void svnadd(const QString& source,const QString& dest,bool bDir = false);
void svndelete(const QString& dest,bool bDir = false);
void svnmodify(const QString& source,const QString& dest);
bool isSvnDir(const QString& dir);	
bool isNoNeedUpdate(const QString& dirName);
void writebat();

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
		reversedelete(sourceDir,destDir);
		writebat();
	}

	return 0;

}

void svnsync(const QString& strSource,const QString& strDest)
{
	// 加载源和目的地址 文件和文件夹，然后进行对比
	QFileInfo sourceInfo(strSource);
	QFileInfo destInfo(strDest);

	if (isNoNeedUpdate(sourceInfo.fileName()))
	{
		return;
	}
	if (!sourceInfo.exists())
	{
		return;
	}
	if (sourceInfo.isDir()) // 文件夹
	{
		CMDPair pair;
		pair.first = eSVN_SYNC;
		pair.second = sourceInfo.absoluteFilePath();
		g_CommandList.append(pair);

		if (destInfo.exists())
		{
			QDir sourceDir(strSource);
			QDir destDir(strDest);
			QFileInfoList sourceDirList = sourceDir.entryInfoList(QDir::Dirs|QDir::Files|QDir::NoDot|QDir::NoDotDot,QDir::DirsLast);

			foreach(const QFileInfo& info,sourceDirList)
			{
				qDebug() << info.absoluteFilePath();
				// 递归处理每一个文件或者文件夹
				svnsync(info.absoluteFilePath(),strDest + "/" + info.fileName());
			}
		}
		else // 不存在则拷贝目录
		{
			svnadd(strSource,strDest,true);
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
			svnadd(strSource,strDest,false);
		}
	}
}

void reversedelete(const QString& strSource,const QString& strDest)
{
	QFileInfo sourceInfo(strSource);
	QFileInfo destInfo(strDest);
	if (!destInfo.exists())
	{
		return;
	}
	if (destInfo.isDir()) // 文件夹
	{
		CMDPair pair;
		pair.first = eSVN_REVERSE;
		pair.second = destInfo.absoluteFilePath();
		g_CommandList.append(pair);

		QDir sourceDir(strSource);
		QDir destDir(strDest);
		QFileInfoList allDirList = destDir.entryInfoList(QDir::Dirs|QDir::Files|QDir::NoDot|QDir::NoDotDot,QDir::DirsLast);
		QFileInfoList destDirList = filterDir(allDirList);
		QStringList sourceList = sourceDir.entryList(QDir::Dirs|QDir::Files|QDir::NoDot|QDir::NoDotDot,QDir::DirsLast);
		foreach(const QFileInfo& info,destDirList)
		{
			QString filename = info.fileName();
			if (!sourceList.contains(filename))
			{
				svndelete(info.absoluteFilePath(),info.isDir());
			}
			else if(info.isDir()) // 如果为目录，递归进行删除
			{
				reversedelete(strSource + "/" + info.fileName(),info.absoluteFilePath());
			}
		}
	}
	else
	{
		if (!sourceInfo.exists())
		{
			svndelete(destInfo.absoluteFilePath(),false);
		}
	}
}


QFileInfoList filterDir(const QFileInfoList& allInfo)
{
	QFileInfoList filterList;
	foreach(const QFileInfo& info,allInfo)
	{
		QString fileName = info.fileName();
		bool bFilter = false;
		bFilter = fileName.contains("debug",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains("release",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains("release",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".moc",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".rcc",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains("svn.",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".ui",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".pdb",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".idb",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".vcproj",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".user",Qt::CaseInsensitive);
		bFilter = bFilter || fileName.contains(".sln",Qt::CaseInsensitive);

		if (!bFilter )
		{	
			if (info.isDir())
			{
				bool bsvn = isSvnDir(info.absoluteFilePath());
				if (bsvn)
				{
					filterList.append(info);
				}
			}
			else
			{
				filterList.append(info);
			}
		}
	}
	return filterList;
}


void svnadd(const QString& source,const QString& dest,bool bDir)
{
	
	CMDPair pair;
	pair.first = e_ADD;
	if (bDir)
	{
		pair.second = "xcopy " + QString(source).replace('/','\\') + " " + QString(dest).replace('/','\\') + " /e /i"; 
	}
	else
	{
		pair.second = "copy " + QString(source).replace('/','\\') + " " + QString(dest).replace('/','\\') + " /Y"; 
	}
	
	g_CommandList.append(pair);
	qDebug() << pair.second;

	pair.first = eSVN_ADD;
	pair.second = "svn add "+ QString(dest).replace('/','\\');
	g_CommandList.append(pair);
	qDebug() << pair.second;
}

void svndelete(const QString& dest,bool bDir )
{
	if (bDir && !isSvnDir(dest))
	{
		return;
	}

	CMDPair pair;
	pair.first = eSVN_DELETE;
	pair.second = "svn rm " + QString(dest).replace('/','\\');
	g_CommandList.append(pair);
	qDebug() << pair.second;
}

void svnmodify(const QString& source,const QString& dest)
{
	CMDPair pair;
	pair.first = eSVN_MODIFY;
	pair.second = "copy " + QString(source).replace('/','\\') + " " + QString(dest).replace('/','\\') + " /Y"; 
	g_CommandList.append(pair);
	qDebug() << pair.second;
}

bool isSvnDir(const QString& strDir)
{
	QDir dir(strDir);
	QStringList dirList = dir.entryList(QDir::Dirs|QDir::Hidden|QDir::NoDot|QDir::NoDotDot,QDir::DirsLast);
	if (dirList.contains(".svn"))
	{
		return true;
	}
	return false;
}

bool isNoNeedUpdate(const QString& dirName)
{
	if (dirName.toUpper() == "THIRDPARTY" ||
		dirName.toUpper() == "PROJECT-TOOLS")
	{
		return true;
	}
	return false;
}

void writebat()
{
	QFile file("svncommit.bat");
	if (file.open(QFile::WriteOnly | QFile::Truncate)) 
	{
		QTextStream out(&file);
		foreach(const CMDPair& pair,g_CommandList)
		{
			if (pair.first == e_ADD)
			{
				out << "REM ADD \n";
			}
			else if (pair.first == eSVN_ADD)
			{
				out << "REM SVN ADD \n";
			}
			else if (pair.first == eSVN_MODIFY)
			{
				out << "REM MODIFY \n";
			}
			else if (pair.first == eSVN_DELETE)
			{
				out << "REM SVN DELETE \n";
			}
			else if (pair.first == eSVN_SYNC)
			{
				out << "REM  SYNC PWD = " << pair.second << "\n";
				continue;
			}
			else if (pair.first == eSVN_REVERSE)
			{
				out << "REM  REVERSE PWD = " << pair.second << "\n";
				continue;
			}
			out << pair.second << "\n\n";

		}
		out.flush();
	}
	file.close();
}