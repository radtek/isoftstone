#include "creatpro.h"

#include "common.h"

CCreatPro::CCreatPro()
{
}

// qmake -tp vc -r 

void CCreatPro::execute(QString maindir)
{
    // ��һ�� �� ͨ��entryList �ҵ����б��ļ����µ��������ļ���
    QDir dir(maindir);
    QStringList lstDir = dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);

	// �ڶ�����ͨ��������ʽ����ÿ���ļ��У�ͨ��truncate��ʽд��qmake_vc.bat,��ǰ�ļ���.pro
    foreach(QString strDir,lstDir)
    {
		//�����ļ�·�������ļ�
        QString tmpDir = maindir + "/" + strDir;
		
		execute(tmpDir);

		//����qmake_vc.bat�ļ�
        QFile file(tmpDir + "/qmake_vc.bat");

		//���ļ�д������
        if (file.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream stream(&file);
            WRITELINE("qmake -t vcapp" );
            WRITELINE("@pause");

            stream.flush();
            file.close();
			std::cout << file.fileName().toLocal8Bit().data() << ENDLINE;
        }

		//����.pro�ļ�
		 QFile filepro(tmpDir + "/" + strDir + ".pro");
		 QDir dirpro(maindir + "/" + strDir);

		//���ļ�д������
		if (filepro.open(QFile::WriteOnly | QFile::Truncate))
		{
			QTextStream stream(&filepro);
			WRITELINE( ENDLINE);
			//WRITELINE("include(../osg.pri)");
			WRITELINE("DEPENDPATH += ../../include");

			WRITELINE("INCLUDEPATH += DEPENDPATH");
	
			// ������: pro��headers Ҫ�������ļ���������.h �ļ���ͬ��д��cpp
			// ��������h�ļ�
			WRITELINE( ENDLINE);
			WRITELINE( "HEADER +=  \\");
			QStringList lstFile = dirpro.entryList(QStringList() << QString("*.h") << QString("*.hpp"), QDir::Files);
			//���������ļ������
			foreach(QString strFile, lstFile)
			{
				WRITELINE(QString("\t\t") + strFile + " \\");
			}
			WRITELINE( ENDLINE);

			// ��������cpp�ļ�
			WRITELINE( "SOURCES +=  \\");
			lstFile = dirpro.entryList(QStringList() << QString("*.cpp") << QString("*.cxx") << QString("*.c") << QString("*.ec") << QString("*.4gl")  << QString("*makefile") , QDir::Files );
			//���������ļ������
			foreach(QString strFile, lstFile)
			{
				WRITELINE(QString("\t\t") + strFile + " \\");
			}
			WRITELINE( ENDLINE);
			
			stream.flush();
			filepro.close();

			std::cout << filepro.fileName().toLocal8Bit().data()<< ENDLINE;
		}

		//���岽������qtnmake.bat�ļ�����ֱ�����ɿ�ִ���ļ�
		//call "%VS90COMNTOOLS%"\vsvars32.bat
		//nmake
		//����qmake_vc.bat�ļ�
		QFile filenmake(tmpDir + "/qtnmake.bat");

		//���ļ�д������
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
	 // ���Ĳ����˳��ļ��У����ݴ����ļ������һ�����ƣ���д ���ļ���.pro��д��SUBDIRSֵ
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
