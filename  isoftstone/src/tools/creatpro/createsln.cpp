
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QUuid>

#include "createsln.h"
#include "common.h"

CCreateSln::CCreateSln()
{
	m_rootNode = new CProjectNode(NULL);
}

CCreateSln::~CCreateSln()
{
	if (m_stream)
	{
		m_stream->flush();
		delete m_stream;
	}
	if (m_file)
	{
		m_file->close();
		delete m_file;
	}
}

void CCreateSln::setSlnName(QString folder)
{
	QDir dir(folder);
	m_mainFolder = dir.canonicalPath();
	//创建qmake_vc.bat文件
	m_file = new QFile(folder + "/" + dir.dirName() + ".sln");

	//打开文件写入内容
	if (m_file->open(QFile::WriteOnly | QFile::Truncate))
	{
		m_stream = new QTextStream(m_file);
		m_stream->setCodec("UTF-8");
		m_stream->setGenerateByteOrderMark(true);
	}
}

void CCreateSln::run()
{
	if(m_stream == NULL)
	{
		return;
	}
	*m_stream << ENDLINE;
	*m_stream << "Microsoft Visual Studio Solution File, Format Version 10.00" << ENDLINE;
	*m_stream << "# Visual Studio 2008" << ENDLINE;
	execute(m_rootNode,m_mainFolder);
	for (int i = 0 ; i < m_rootNode->getChildList().count() ; i++)
	{
		m_rootNode->getChildList().at(i)->write2File(*m_stream);
	}
	writeGlobal();
}

void CCreateSln::writeGlobal()
{
	*m_stream << "Global" << ENDLINE;
	*m_stream << "\tGlobalSection(NestedProjects) = preSolution" << ENDLINE;

	QMap<QString,QString>::Iterator iter = m_nodeMap.begin();
	for (;iter != m_nodeMap.end() ; iter++)
	{
		QString key = iter.key();
		QString value = iter.value();
		*m_stream << "\t\t" << key << " = " << value << ENDLINE;
	}

	*m_stream << "\tEndGlobalSection" << ENDLINE;
	*m_stream << "EndGlobal" << ENDLINE;
}

void CCreateSln::execute(CProjectNode* parent,QString folder)
{
	QDir dir(folder);
	QFileInfoList lst = dir.entryInfoList(QDir::Dirs| QDir::Files | QDir::NoDot | QDir::NoDotDot);

	foreach(QFileInfo info,lst)
	{
		if(info.isDir())
		{
			CProjectNode* child = new CProjectNode(parent);
			child->setItemName(info.baseName());
			QString guid = QUuid::createUuid().toString().toUpper();
			child->setItemGuid(guid);
			parent->addChild(child);
			if (parent->getParent())
			{
				m_nodeMap.insert(child->getItemGuid(),parent->getItemGuid());
			}
			QString childfolder = folder + "/" + info.fileName();
			execute(child,childfolder);
		}
		else if(info.isFile())
		{
			if(filter(info))
			{
				QString path = info.canonicalFilePath();
				QString key = getRelativePath(path);
				parent->addItem(key,key);
			}
		}

	}
}

QString CCreateSln::getRelativePath(QString path)
{
	QString tmp = path;
	tmp.replace(m_mainFolder + "/","");
	return tmp;
}

bool CCreateSln::filter(QFileInfo info )
{
	QString filename = info.completeBaseName();
	QString suffix = info.completeSuffix();
	if (suffix == QString("h"))
	{
		return true;
	}
	else if (suffix == QString("hpp"))
	{
		return true;
	}
	else if (suffix == QString("cpp"))
	{
		return true;
	}
	else if (suffix == QString("ec"))
	{
		return true;
	}
	else if (suffix == QString("4gl"))
	{
		return true;
	}
	else if (suffix == QString("c"))
	{
		return true;
	}
	else if(filename == QString("makefile"))
	{
		return true;
	}
	else
	{
		return false;
	}
}