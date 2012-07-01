#include "creatpro.h"

#define WRITELINE(TEXT) \
	stream << TEXT << "\n";

CCreatPro::CCreatPro(const QString& dir):m_mainDir(dir)
{
}

void CCreatPro::execute()
{
    // ��һ�� �� ͨ��entryList �ҵ����б��ļ����µ��������ļ���
    QDir dir(m_mainDir);
    QStringList lstDir = dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);

	// �ڶ�����ͨ��������ʽ����ÿ���ļ��У�ͨ��truncate��ʽд��qmake_vc.bat,��ǰ�ļ���.pro
    foreach(QString strDir,lstDir)
    {
		//�����ļ�·�������ļ�
        QString tmpDir = m_mainDir + "/" + strDir;

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
        }

		//����.pro�ļ�
		 QFile filepro(tmpDir + "/" + strDir + ".pro");
		 QDir dirpro(m_mainDir + "/" + strDir);

		//���ļ�д������
		if (filepro.open(QFile::WriteOnly | QFile::Truncate))
		{
			QTextStream stream(&filepro);
			WRITELINE( "\n");
			WRITELINE("include(../osg.pri)");
	
			// ������: pro��headers Ҫ�������ļ���������.h �ļ���ͬ��д��cpp
			// ��������h�ļ�
			WRITELINE( "\n");
			WRITELINE( "HEADER +=  \\");
			QStringList lstFile = dirpro.entryList(QStringList() << QString("*.h"), QDir::Files);
			//���������ļ������
			foreach(QString strFile, lstFile)
			{
				WRITELINE(QString("\t\t") + strFile + " \\");
			}
			WRITELINE( "\n\n");

			// ��������cpp�ļ�
			WRITELINE( "SOURCES +=  \\");
			lstFile = dirpro.entryList(QStringList() << QString("*.cpp"), QDir::Files );
			//���������ļ������
			foreach(QString strFile, lstFile)
			{
				WRITELINE(QString("\t\t") + strFile + " \\");
			}
			WRITELINE( "\n\n");
			
			stream.flush();
			filepro.close();
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
			WRITELINE( "\n");					
			WRITELINE("nmake");

			stream.flush();
			filenmake.close();
		}
    }
	 // ���Ĳ����˳��ļ��У����ݴ����ļ������һ�����ƣ���д ���ļ���.pro��д��SUBDIRSֵ
	QString dirName = dir.dirName();
	QFile file(m_mainDir + "/" + dirName + ".pro");
	if (file.open(QFile::WriteOnly | QFile::Truncate))
	{
		QTextStream stream(&file);

		WRITELINE( "\n");
		WRITELINE("TEMPLATE = subdirs" );

		WRITELINE( "SUBDIRS +=  \\");
		QStringList lstDir = dir.entryList(QDir::Dirs | QDir::NoDot | QDir::NoDotDot);
		foreach(QString strDir, lstDir)
		{
			WRITELINE(QString("\t\t") + strDir + QString(" \\"));
		}
		WRITELINE( "\n\n");
		
		stream.flush();
		file.close();
	}
		
}
