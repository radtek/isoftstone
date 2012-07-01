
#include "func.h"

QMutex mutex;
long fileCount;

extern QMap<QString,QString> attrTypeMap;
extern QMap<QString,QString> valueMap;

QStringList getGFileDir(const QString& dirName)
{
	QStringList lstRet;
	QDir dir(dirName);
	QFileInfoList lstInfo = dir.entryInfoList();
	foreach(QFileInfo info ,lstInfo)
	{
		QString baseName = info.fileName();
		if (info.isDir() &&  baseName != ".." && baseName != ".")
		{
			QString path = info.absoluteFilePath();
			lstRet.append(path);
		}
	}
	return lstRet;
}

void createInfo_H(std::string dir)
{
	QThreadPool::globalInstance()->setMaxThreadCount(20);
	QTime time;
	time.start();

	if (QDir::home().exists(QString::fromStdString(dir)))
	{
		QMap<QString,QStringList> classMap;
		if (0)
		{
			QStringList subdirs = getGFileDir(QString::fromStdString(dir));
			classMap = mappedReduced(subdirs,statistics_m,reduce);
		}
		else
		{
			QStringList filter;
			filter << "g";
			QStringList lstFile = getFileRecusive(QString::fromStdString(dir),filter);
			classMap = mappedReduced(lstFile.begin(),lstFile.end(),statistics,reduce);
		}
		print("info.h" , classMap);

		// 将所有不同属性输出到文件，然后确定数据类型
		QSet<QString> attrSet;
		QMapIterator<QString,QStringList> iter(classMap);
		while(iter.hasNext())
		{
			iter.next();
			foreach(QString attr,iter.value())
			{
				if (attrSet.contains(attr) == false)
				{
					attrSet.insert(attr);
				}
			}
		}
		QStringList lstAttr = attrSet.toList();
		qSort(lstAttr.begin(),lstAttr.end(),caseInsensitiveLessThan);
		print("attr.h",lstAttr);
	}

	qDebug() << "消耗时间 ：" << time.elapsed();
}


QStringList getGFileRecusive(const QString& dirName)
{
	QStringList lstRet;
	QDir dir(dirName);
	QFileInfoList lstInfo = dir.entryInfoList();
	foreach(QFileInfo info ,lstInfo)
	{
		QString baseName = info.fileName();
		if (info.isDir() &&  baseName != ".." && baseName != ".")
		{
			QString path = info.absoluteFilePath();
			lstRet = lstRet + getGFileRecusive(path);
		}
		else
		{
			if (info.suffix() == "g")
			{
				lstRet.append(info.absoluteFilePath());
			}
		}
	}
	return lstRet;
}

QStringList getFileRecusive(const QString& dirName,const QStringList& filters)
{
	QStringList lstRet;
	QDir dir(dirName);
	QFileInfoList lstDir = dir.entryInfoList();
	foreach(QFileInfo info ,lstDir)
	{
		QString baseName = info.fileName();
		if (info.isDir() &&  baseName != ".." && baseName != ".")
		{
			QString path = info.absoluteFilePath();
			lstRet = lstRet + getFileRecusive(path,filters);
		}
		else if(info.isFile())
		{
			const QString& ext = info.suffix();
			if (filters.contains(ext))
			{
				lstRet.append(info.absoluteFilePath());
			}
		}
	}
	return lstRet;
}

void statistics(const QString& fileName,QMap<QString,QStringList>& classMap)
{
	QDomDocument doc("doc");
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		return;
	}
	QString errorStr;
	int errorLine;
	int errorColumn;

	if (!doc.setContent(&file, true, &errorStr, &errorLine,&errorColumn)) 
	{
		return ;
	}
	QDomElement root = doc.documentElement();
	if (root.childNodes().count() > 0)
	{
		QDomElement ele = root.firstChildElement();
		if (ele.childNodes().count() > 0)
		{
			for(int i = 0; i < ele.childNodes().count() ; i++)
			{
				QDomNode node = ele.childNodes().at(i);
				QString name = node.nodeName();
				name = name.replace('-','_');

				if (classMap.contains(name) == false)
				{
					QStringList lstAttr;
					QDomNamedNodeMap attrMap = node.attributes();
					for (int i = 0 ; i < attrMap.count() ; i++)
					{
						QString attrName = attrMap.item(i).nodeName();
						attrName = attrName.replace('-','_');
						// 特殊属性名进行处理
						if (attrName == "switch")
						{
							attrName = "switch_rep";
						}

						lstAttr.append(attrName);
					}
					qSort(lstAttr.begin(), lstAttr.end(), caseInsensitiveLessThan);
					classMap.insert(name,lstAttr);
				}
			}
		}
	}
	file.close();
	QMutexLocker locker(&mutex);
	std::cout << fileName.toStdString() << "  Num:" << ++fileCount << std::endl;
}

QMap<QString,QStringList> statistics(const QString& fileName)
{
	QMap<QString,QStringList> subMap;
	statistics(fileName,subMap);
	return subMap;
}

QMap<QString,QStringList> statistics_m(const QString& dirName)
{
	QMap<QString,QStringList> subMap;
	QStringList files = getGFileRecusive(dirName);
	foreach(QString file,files)
	{
		statistics(file,subMap);
	}
	return subMap;
}

void reduce(QMap<QString,QStringList>& resultMap,const QMap<QString,QStringList>& oneMap)
{
	QMapIterator<QString,QStringList> iter(oneMap);
	while (iter.hasNext())
	{
		iter.next();
		QString key = iter.key();
		if (resultMap.contains(key) == false)
		{
			resultMap.insert(key,iter.value());
		}
	}

}

void print(const QString& fileName,const QMap<QString,QStringList>& classMap)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&file);
	QMapIterator<QString,QStringList> iter(classMap);
	out << "#ifndef GFILE_STRUCT_H\n";
	out << "#define GFILE_STRUCT_H\n\n";

	while (iter.hasNext())
	{
		iter.next();
		QString className = iter.key(); 
		QString firstLetter = className.left(1);
		className.replace(0,1,firstLetter.toUpper());
		out << "class " << className << "_Struct" << "\n";
		out <<"{\n";
		out << "public:\n";
		foreach(QString attr,iter.value())
		{
			QString strType = "QString";
			if (attrTypeMap.contains(attr))
			{
				strType = attrTypeMap[attr];
				if (strType == "long")
				{
					strType = "quint64";
				}
				else if (strType == "rect")
				{
					strType = "QRect";
				}
				else if (strType == "polygon")
				{
					strType = "QPolygonF";
				}
				else if (strType == "color")
				{
					strType = "QColor";
				}
				else if (strType == "string")
				{
					strType = "QString";
				}
				else if (strType == "int")
				{
					strType = "int ";
				}
				else if (strType == "uint")
				{
					strType = "uint ";
				}
				else if (strType == "qreal")
				{
					strType = "qreal ";
				}
				else if (strType == "double")
				{
					strType = "double ";
				}
				else if (strType == "tfr")
				{
					strType = "QThree";
				}
			}
			out << "\t" << strType <<"\t\t " << attr << ";\n";
		}
		out << "};\n\n";
	}
	out << "#endif\n";
	out.flush();
	file.close();
}



void print(const QString& fileName,const QMap<QString,QString>& attrValue)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&file);
	QMapIterator<QString,QString> iter(attrValue);
	while(iter.hasNext())
	{
		iter.next();
		out << iter.key() << " : " << iter.value() << "\n";
	}
	out.flush();
	file.close();
}

void print(const QString& fileName,const QStringList& attrLst)
{
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&file);
	for(int i = 0 ; i < attrLst.count() ; i++)
	{
		out << attrLst[i] << "\n";
	}
	out.flush();
	file.close();
}

void printEnum(const QString& source,const QString& dest)
{
	QFile sourcefile(source);
	if (!sourcefile.open(QIODevice::ReadOnly))
	{
		return;
	}

	QFile destfile(dest);
	if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}

	QTextStream out(&destfile);
	out << "#ifndef GFILE_ENUM_H\n";
	out << "#define GFILE_ENUM_H\n\n";
	out << "#include <QGraphicsItem>\n\n";
	out << "enum GEnum\n";
	out << "{\n";
	out <<"\tEUserType = QGraphicsItem::Type + 1,\n";

	QTextStream in(&sourcefile);
	while(!in.atEnd())
	{
		QString line = in.readLine();
		if (line.contains("class",Qt::CaseInsensitive))
		{
			QStringList lst = line.split(' ');
			if (lst.count() > 1)
			{
				out <<"\tE" << lst[1].remove("_Struct") << ",\n";
			}
		}
	}
	out << "};\n\n\n";

	out << "inline char* toString(GEnum eType)\n";
	out <<"{\n";
	out <<"\tswitch(eType)\n";
	out << "\t{\n";

	in.seek(0);
	while(!in.atEnd())
	{
		QString line = in.readLine();
		if (line.contains("class",Qt::CaseInsensitive))
		{
			QStringList lst = line.split(' ');
			if (lst.count() > 1)
			{
				QString strEnum = "E" + lst[1].remove("_Struct");
				QString strTab = getTabSpace(strEnum);
				out <<  "\tcase " << strEnum <<":" << strTab << "return \"" << strEnum << "\";" << "\n";
			}
		}
	}
	out <<"\tdefault:\t\t\treturn \"UnKnown\";\n";
	out << "\t}\n";
	out <<"}\n";

	out << "#endif\n";
	out.flush();
	destfile.close();
}

void readType(const QString& fileName,QMap<QString,QString>& attrType)
{
	attrType.clear();

	QSettings st(fileName,QSettings::IniFormat);
	st.beginGroup("ATTRIBUTE");
	QStringList keys = st.childKeys();
	foreach(QString attr,keys)
	{
		QString value = st.value(attr).toString();
		attrType.insert(attr,value);
	}
	st.endGroup();

}

QString getTabSpace(QString strText)
{
	QString strTab = "";
	int num = 3 - (strText.length()  )/6;
	for (int i = 0 ; i < num ;i++)
	{
		strTab += "\t";
	}
	if (strText.length() > 9)
	{
		strTab = "\t";
	}
	return strTab;
}

