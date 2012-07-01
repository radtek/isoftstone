
#include "symbol.h"
#include "common.h"

#include <iostream>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QStringList>
#include <QDomDocument>

extern QMap<QString,QString> g_SymbolMap;

// 读取svg图元文件中符号
QString createSvgSymbol(const QString& fileName,QString& strSymbol)
{
	QString strID;
	strSymbol.clear();
	
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QFileInfo fInfo(fileName);

	QTextStream reader(&file);
	reader.setCodec("UTF-8");
	std::cout << fileName.toStdString() << "\n";
	while (!reader.atEnd())
	{
		QString line = reader.readLine();
		if (line.contains("<svg"))
		{
			strSymbol = "<symbol";
			line = line.remove("<svg").remove(">").remove("\"");
			QStringList lstAttrs = line.split(' ');
			foreach (QString str,lstAttrs)
			{
				QStringList lst = str.split('=');
				//if (lst[0] == "name")
				//{
				//	strID = strID + lst[1] + ":";
				//}
				strID = fInfo.completeBaseName();
				strID += ".g";
				if (lst[0] =="id")
				{
					strID = strID  + ":" + QObject::tr(lst[1].toLocal8Bit().data());
					strSymbol = strSymbol + " id =\"" + strID + "\"";
				}
				else if (lst[0] == "viewBox")
				{
					strSymbol = strSymbol + " viewBox=\"" + lst[1];
				}
				else if (lst[0] == "name")
				{
					strSymbol = strSymbol + " name=\"" + lst[1] + "\"";
				}
				else
				{
					strSymbol =strSymbol + " " + str;
				}
			}
			strSymbol = strSymbol + "\">\n";
		}
		else if (!(line.contains("<?xml")||line.contains("<g ") || line.contains("</g>") || line.contains("</svg>")))
		{
			strSymbol += line + "\n";
		}
	}
	
	file.close();
	strSymbol = strSymbol +"</symbol>\n";
	return strID;
}

// 将svg图元文件生成到symbol.xml 符号文件中
void writeSymbols(QTextStream& out,QString strID,const QString& strSymbol)
{
	out << strSymbol;
}

void writeSymbols(const QString& dirName,const QString& fileName)
{
	QStringList lstRet;
	QStringList filter;
	filter << "svg";

	QMap<QString,QString> symbolMap;
	lstRet = getFileRecusive(dirName,filter);
	foreach(QString fileName,lstRet)
	{
		QString strSymbol;
		QString strID = createSvgSymbol(fileName,strSymbol);
		symbolMap.insert(strID,strSymbol);
	}

	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return ;

	QTextStream writer(&file);
	writer << "<?xml version=\"1.0\" encoding=\"gb2312\"?>\n";
	writer <<"<defs>\n";
	writeSymbols(writer,symbolMap);
	writer <<"</defs>\n";
	file.close();
}

void writeSymbols(QTextStream& out,const QMap<QString,QString>& symbolMap)
{
	QMapIterator<QString,QString> iter(symbolMap);
	while(iter.hasNext())
	{
		iter.next();

		writeSymbols(out,iter.key(),iter.value());
	}
}

void readSymbols(const QString& fileName,QMap<QString,QString>& symbolMap)
{
	symbolMap.clear();

	QDomDocument doc;
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
	{
		return;
	}
	if (doc.setContent(&file))
	{
		QDomNode pRoot = doc.firstChildElement("defs");
		if (pRoot.hasChildNodes())
		{
			QDomNodeList nodeList = pRoot.childNodes();
			for(int i = 0; i < nodeList.count();i++)
			{
				const QDomNode& pNode = nodeList.item(i);
				QString strID = pNode.toElement().attribute("id");

				QString strSymbol;
				QTextStream stream(&strSymbol);
				pNode.save(stream,1);
				symbolMap.insert(QString("#") + strID,strSymbol);
			}
		}

		file.close();
		return;
	}
}