
#include <QXmlStreamReader>
#include <QTextStream>
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

typedef void (*FUNC)(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);

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


void writeHeaderLayer(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QTextStream& writer)
{
	QString width = "2000";
	QString height = "1200";
	if (layerMap.contains("Layer"))
	{
		width = layerMap["Layer"][0]["w"];
		height = layerMap["Layer"][0]["h"];
	}	
	startElement(writer,"g","id","Head_Layer",1);
	{

	}
	endElement(writer);
}

bool transformNode(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QTextStream& writer)
{
		
	QMap<QString,QVector<QMap<QString,QString> > > layerMapCopy = layerMap;
	
	//writeHeaderLayer(layerMapCopy,writer);

	int nID = 0;
	
//  	QStringList layers;
// 	// 基本图元
//  	layers << "rect" <<"circle" <<"polygon"<<"polylin"<<"circlearc"<<"eclipsearc"<<"pin"<<"triangle" << "line"<<"diamond";
// 	// 电气图元
// 	layers << "roundrect"<<"ConnectLine" << "ACLineEnd" << "Bus" << "Disconnector" << "CBreaker" << "Transformer2" << "Transformer3";
// 
// 	layers << "image"<<"Clock"<<"ACLine"<<"Sensitive";
// 	// 重要文字
//  	layers <<"text"<<"Text" << "poke" << "DText";
// 
// 	
// 
// 	foreach(QString layerName,layers)
// 	{
// 		if (layerMapCopy.contains(layerName) == false)
// 		{
// 			continue;
// 		}
// 
// 		startElement(writer,"g","id",layerName + "_Layer",1);
// 		{
// 			const QVector<QMap<QString,QString> >& vecValues = layerMapCopy.value(layerName);
// 			for (int i = 0 ; i < vecValues.count();i++)
// 			{
// 				const QMap<QString,QString>& attrMap = vecValues[i];
// 				transformNode(layerName,attrMap,writer,++nID);
// 			}
// 		}
// 		endElement(writer);
// 
// 		layerMapCopy.remove(layerName);
// 	}

	QMapIterator<QString,QVector<QMap<QString,QString> > > iter(layerMapCopy);
	while(iter.hasNext())
	{
		iter.next();
		QString layerName = iter.key();
		if (layerName == "Layer" || layerName == "svg")
		{
			continue;
		}
		//startElement(writer,layerName,"","",1);
		{
			const QVector<QMap<QString,QString> >& vecValues = layerMapCopy.value(layerName);
			for (int i = 0 ; i < vecValues.count();i++)
			{
				const QMap<QString,QString>& attrMap = vecValues[i];
				transformNode(layerName,attrMap,writer,++nID);
			}
		}
		//endElement(writer);
	}

	return true;
}

bool transformNode(const QVector<QPair<QString,QMap<QString,QString> > >& vecMap,QTextStream& writer)
{
	QVectorIterator<QPair<QString,QMap<QString,QString> > > iter(vecMap);
	int nID = 0;
	while(iter.hasNext())
	{
		QPair<QString,QMap<QString,QString> > pair = iter.next();
		QString layerName = pair.first;
		if (layerName == "Layer" || layerName == "svg")
		{
			continue;
		}

		const QMap<QString,QString>& attrMap = pair.second;
		transformNode(layerName,attrMap,writer,++nID);
	}
	return true;
}

bool transformNode(const QString& name,const QMap<QString,QString>& attrMap,QTextStream& writer,int nID)
{
	if (g_FuncPointer.contains(name))
	{
		(*g_FuncPointer[name])(attrMap,writer,nID);
		return true;
	}
	return false;
}

bool transformG2QML(const QString& gFile,QString& svgFile)
{
	QMap<QString,QVector<QMap<QString,QString> > > layerMap;
	QVector<QPair<QString,QMap<QString,QString> > > vecLayer;
	QSet<QString> devRefSet;
	readElement(gFile,layerMap,vecLayer,devRefSet);
	
	svgFile = gFile;
	svgFile = svgFile.replace(gFile.count() -2,2,".qml");
	QFile file2(svgFile);
	if (!file2.open(QIODevice::WriteOnly | QIODevice::Truncate))
		return false;

	QTextStream writer(&file2);

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

	writer << "\nimport QmlItem 1.0";
	writer << "\nimport QtQuick 1.0\n\n";

	QString width = layerMap["Layer"][0]["w"];
	QString height = layerMap["Layer"][0]["h"];

	startElement(writer,"Item","width" << "height",width << height,0); // begin of qml
	writer << "\n";
	// 实例节点
	transformNode(vecLayer,writer);

	// 根节点结束
	endElement(writer); // end of qml
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
		bool bret = transformG2QML(fileName,svgFile);
		if (bret)
		{
			nRet++;
		}
	}
	return nRet;
}