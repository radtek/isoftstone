
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStringList>
#include <QFile>
#include <QRegExp>
#include <QMap>
#include <QSet>
#include <QVector>
#include <QTextStream>
#include <iostream>

#include "transcommon.h"
#include "transform.h"
#include "common.h"

typedef void (*FUNC)(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);

QMap<QString,FUNC> g_FuncPointer;

extern QMap<QString,QString> g_SymbolMap;

void initFuncPointer()
{
	g_FuncPointer.insert("Bus",&transformBus);
	g_FuncPointer.insert("CBreaker",&transformBreaker);
	g_FuncPointer.insert("Disconnector",&transformDisconnector);
	g_FuncPointer.insert("Transformer2",&transformTransformer2);
	g_FuncPointer.insert("Transformer3",&transformTransformer3);
	g_FuncPointer.insert("ACLineEnd",&transformACLineEnd);
	g_FuncPointer.insert("ConnectLine",&transformConnectLine);
	g_FuncPointer.insert("Capacitor_P",&transformCapacitor_P);
	g_FuncPointer.insert("Reactor_P",&transformReactor_P);
	g_FuncPointer.insert("Text",&transformText);
	g_FuncPointer.insert("text",&transformText);
	g_FuncPointer.insert("DText",&transformDText);
	g_FuncPointer.insert("rect",&transformRect);
	g_FuncPointer.insert("roundrect",&transformRoundRect);
	g_FuncPointer.insert("line",&transformLine);
	g_FuncPointer.insert("pin",&transformPin);
	g_FuncPointer.insert("circle",&transformCircle);
	g_FuncPointer.insert("circlearc",&transformCircleArc);
	g_FuncPointer.insert("ellipsearc",&transformEclipseArc);
	g_FuncPointer.insert("diamond",&transformDiamond);
	g_FuncPointer.insert("triangle",&transformTriangle);
	g_FuncPointer.insert("polygon",&transformPolygon);
	g_FuncPointer.insert("polyline",&transformPolyline);
	g_FuncPointer.insert("Curve",&transformCurve);
	g_FuncPointer.insert("Table",&transformTable);
	g_FuncPointer.insert("Bar",&transformBar);
	g_FuncPointer.insert("image",&transformImage);
	g_FuncPointer.insert("poke",&transformPoke);
	g_FuncPointer.insert("Clock",&transformClock);
	g_FuncPointer.insert("ACLine",&transformACLine);
}


void writeHeaderLayer(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QXmlStreamWriter& writer)
{
	QString width = "2000";
	QString height = "1200";
	if (layerMap.contains("Layer"))
	{
		width = layerMap["Layer"][0]["w"];
		height = layerMap["Layer"][0]["h"];
	}	
	startElement(writer,"g","id","Head_Layer");
	{
		startElement(writer,"rect","x" << "y" << "width" << "height" << "fill","0"<<"0" << width << height << "rgb(0,0,0)");
		endElement(writer);
	}
	endElement(writer);
}

bool transformNode(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QXmlStreamWriter& writer)
{
		
	QMap<QString,QVector<QMap<QString,QString> > > layerMapCopy = layerMap;
	
	writeHeaderLayer(layerMapCopy,writer);
	
 	QStringList layers;
	// 基本图元
 	layers << "rect" <<"circle" <<"polygon"<<"polylin"<<"circlearc"<<"eclipsearc"<<"pin"<<"triangle" << "line"<<"diamond";
	// 电气图元
	layers << "roundrect"<<"ConnectLine" << "ACLineEnd" << "Bus" << "Disconnector" << "CBreaker" << "Transformer2" << "Transformer3";

	layers << "image"<<"Clock"<<"ACLine"<<"Sensitive";
	// 重要文字
 	layers <<"text"<<"Text" << "poke" << "DText";

	int nID = 0;

	foreach(QString layerName,layers)
	{
		if (layerMapCopy.contains(layerName) == false)
		{
			continue;
		}

		startElement(writer,"g","id",layerName + "_Layer");
		{
			const QVector<QMap<QString,QString> >& vecValues = layerMapCopy.value(layerName);
			for (int i = 0 ; i < vecValues.count();i++)
			{
				const QMap<QString,QString>& attrMap = vecValues[i];
				transformNode(layerName,attrMap,writer,++nID);
			}
		}
		endElement(writer);

		layerMapCopy.remove(layerName);
	}

	QMapIterator<QString,QVector<QMap<QString,QString> > > iter(layerMapCopy);
	while(iter.hasNext())
	{
		iter.next();
		QString layerName = iter.key();
		if (layerName == "Layer" || layerName == "svg")
		{
			continue;
		}
		startElement(writer,"g","id",layerName + "_Layer");
		{
			const QVector<QMap<QString,QString> >& vecValues = layerMapCopy.value(layerName);
			for (int i = 0 ; i < vecValues.count();i++)
			{
				const QMap<QString,QString>& attrMap = vecValues[i];
				transformNode(layerName,attrMap,writer,++nID);
			}
		}
		endElement(writer);

		layerMapCopy.remove(layerName);
	}

	return true;
}

bool transformNode(const QString& name,const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	if (g_FuncPointer.contains(name))
	{
		(*g_FuncPointer[name])(attrMap,writer,nID);
		return true;
	}
	return false;
}

bool transformNode(QXmlStreamReader& reader,QXmlStreamWriter& writer,int nID)
{
	const QString name = reader.name().toString();
	const QXmlStreamAttributes& gAttrs = reader.attributes ();
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		if (name == "Bus")
		{
			QStringList attrs;
			QStringList values;
		
			QString id ;

			if (gAttrs.hasAttribute("d"))
			{
				QString dv = gAttrs.value("d").toString();
				QRegExp exp("(\\s|,)");
				QStringList lst = dv.split(exp);
				if (lst.count() == 4)
				{
					attrs << "d";
					QString svgd = QString("M ") + lst[0] + " " + lst[1] + " L " + lst[2] + " " + lst[3]; 
					values.append(svgd);
				}
			}
			if (gAttrs.hasAttribute("lw"))
			{
				attrs << "stroke-width";
				values.append(gAttrs.value("lw").toString());
			}
			if (gAttrs.hasAttribute("id"))
			{
				attrs << "id";
				id = gAttrs.value("id").toString();
				values.append(id);
			}
			if (gAttrs.hasAttribute("voltype"))
			{
				attrs << "class";
				QString cls = gAttrs.value("voltype").toString();
				values.append(cls);
			}
			startElement(writer,"path",attrs,values)
			{
				startElement(writer,"metadata","1"<<"2","null") 
				{
					writePSR(writer,"_BusbarSection",id)
				}
				endElement(writer)
			}
			endElement(writer)
		}
	}
	endElement(writer)
	return true;
}

bool transformG2SVG(const QString& gFile,QString& svgFile)
{
	QMap<QString,QVector<QMap<QString,QString> > > layerMap;
	QSet<QString> devRefSet;
	readElement(gFile,layerMap,devRefSet);
	
	svgFile = gFile;
	svgFile = svgFile.replace(gFile.count() -2,2,".svg");
	QFile file2(svgFile);
	if (!file2.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return false;

	QXmlStreamWriter writer(&file2);

	writer.setAutoFormatting(true);
	writer.writeStartDocument();
	
	QString name;
	QString id;
	QString viewbox;

	// 根节点
	if (layerMap.contains("svg"))
	{
		name = layerMap["svg"][0]["name"];
		id = layerMap["svg"][0]["id"];
		viewbox = layerMap["svg"][0]["viewBox"];
	}	
	startElement(writer,"svg","name"<<"id"<<"viewBox",name<<id<<viewbox); // begin of svg

	startElement(writer,"defs","name"<<"id",name); // begin defs
	// CSS + SYMBOL

	if (devRefSet.count() > 0)
	{
		QFile filecss("style.css");
		if (filecss.open(QIODevice::ReadOnly))
		{
			QTextStream cssStream(&filecss);
			QString strCss = cssStream.readAll();
			startElement(writer,"style","type" ,"text/css");
			writer.writeCDATA(strCss);
			endElement(writer);
			filecss.close();
		}
		
		QSet<QString>::const_iterator iter = devRefSet.constBegin();
		while (iter != devRefSet.constEnd())
		{
			QString strDev = *iter;
			writer.writeDTD(g_SymbolMap[strDev]);
			iter++;
		}
	}
	endElement(writer);
	// 实例节点
	transformNode(layerMap,writer);

	// 根节点结束
	endElement(writer); // end of svg
	writer.writeEndDocument(); //doc
	file2.close();

	std::cout << svgFile.toStdString() << "\n";
	return true;
}

int  transformGDir(const QString& dirHome)
{
	// 递归转换特定目录下.g文件
	QStringList lstRet;
	QStringList filter;
	filter << "g";
	
	int nRet = 0;
	lstRet = getFileRecusive(dirHome,filter);
	foreach(QString fileName,lstRet)
	{
		QString svgFile;
		bool bret = transformG2SVG(fileName,svgFile);
		if (bret)
		{
			nRet++;
		}
	}
	return nRet;
}