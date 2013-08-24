#include "creatpro.h"

#include "common.h"

CCreatPro::CCreatPro()
{
}

// qmake -tp vc -r 

void CCreatPro::execute(QString maindir)
{
    // 第一步 ： 通过entryList 找到所有本文件夹下的所有子文件夹
    QDir dir(maindir);
    QStringList lstDir = dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);

	// 第二步：通过遍历方式进入每个文件夹，通过truncate方式写入qmake_vc.bat,当前文件夹.pro
    foreach(QString strDir,lstDir)
    {
		//根据文件路径进入文件
        QString tmpDir = maindir + "/" + strDir;
		
		execute(tmpDir);

		//创建qmake_vc.bat文件
        QFile file(tmpDir + "/qmake_vc.bat");

		//打开文件写入内容
        if (file.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream stream(&file);
            WRITELINE("qmake -t vcapp" );
            WRITELINE("@pause");

            stream.flush();
            file.close();
			std::cout << file.fileName().toLocal8Bit().data() << ENDLINE;
        }

		//创建.pro文件
		 QFile filepro(tmpDir + "/" + strDir + ".pro");
		 QDir dirpro(maindir + "/" + strDir);

		//打开文件写入内容
		if (filepro.open(QFile::WriteOnly | QFile::Truncate))
		{
			QTextStream stream(&filepro);
			WRITELINE( ENDLINE);
			//WRITELINE("include(../osg.pri)");
			WRITELINE("DEPENDPATH += ../../include");

			WRITELINE("INCLUDEPATH += DEPENDPATH");
	
			// 第三步: pro中headers 要搜索本文件夹下所有.h 文件，同理写入cpp
			// 查找所有h文件
			WRITELINE( ENDLINE);
			WRITELINE( "HEADER +=  \\");
			QStringList lstFile = dirpro.entryList(QStringList() << QString("*.h") << QString("*.hpp"), QDir::Files);
			//遍历所有文件并添加
			foreach(QString strFile, lstFile)
			{
				WRITELINE(QString("\t\t") + strFile + " \\");
			}
			WRITELINE( ENDLINE);

			// 查找所有cpp文件
			WRITELINE( "SOURCES +=  \\");
			lstFile = dirpro.entryList(QStringList() << QString("*.cpp") << QString("*.cxx") << QString("*.c") << QString("*.ec") << QString("*.4gl")  << QString("*makefile") , QDir::Files );
			//遍历所有文件并添加
			foreach(QString strFile, lstFile)
			{
				WRITELINE(QString("\t\t") + strFile + " \\");
			}
			WRITELINE( ENDLINE);
			
			stream.flush();
			filepro.close();

			std::cout << filepro.fileName().toLocal8Bit().data()<< ENDLINE;
		}

		//第五步：创建qtnmake.bat文件，可直接生成可执行文件
		//call "%VS90COMNTOOLS%"\vsvars32.bat
		//nmake
		//创建qmake_vc.bat文件
		QFile filenmake(tmpDir + "/qtnmake.bat");

		//打开文件写入内容
		if (filenmake.open(QFile::WriteOnly | QFile::Truncate))
		{
			QTextStream stream(&filenmake);
			WRITELINE("call \"%VS90COMNTOOLS%\"\\vsvars32.bat");
			WRITELINE( ENDLINE);					
			WRITELINE("nmake");

			stream.flush();
			filenmake.close();
			std::cout << filenmake.fileName().toLocal8Bit().data();
		}
    }
	 // 第四步：退出文件夹，根据传入文件夹最后一个名称，编写 主文件夹.pro，写入SUBDIRS值
	QString dirName = dir.dirName();
	QFile file(maindir + "/" + dirName + ".pro");
	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		QTextStream stream(&file);

		WRITELINE( ENDLINE);
		WRITELINE("TEMPLATE = subdirs" );

		WRITELINE( "SUBDIRS +=  \\");
		QStringList lstDir = dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
		foreach(QString strDir, lstDir)
		{
			WRITELINE(QString("\t\t") + strDir + QString(" \\"));
		}
		WRITELINE( ENDLINE);
		
		stream.flush();
		file.close();
		std::cout << file.fileName().toLocal8Bit().data()<< ENDLINE;
	}
		
}
