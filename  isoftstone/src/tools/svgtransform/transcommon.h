
#ifndef TRANSCOMMON_H
#define TRANSCOMMON_H

#define startElement(writer,name,lstNames,lstValues) \
	{\
		QStringList attrNames ; \
		attrNames << lstNames; \
		QStringList attrValues ; \
		attrValues << lstValues; \
		writer.writeStartElement(name); \
		writer.setAutoFormattingIndent(writer.autoFormattingIndent()+1); \
		if(attrNames.count() == attrValues.count() ) \
		{ \
			int i = 0; \
			foreach(QString attr,attrNames) \
			{ \
				writer.writeAttribute(attr,attrValues[i++]); \
			} \
		}

#define endElement(writer) \
		writer.setAutoFormattingIndent(writer.autoFormattingIndent()-1); \
		writer.writeEndElement(); \
	}

#define writePSR(writer,label,id) \
	{ \
		startElement(writer,"cge:PSR_Ref","ObjectID"<<"ObjectName",QString(label) + "_" + id << "null"); \
		endElement(writer); \
	}

#define writeMeas(writer,label,id) \
	{ \
		startElement(writer,"cge:Meas_Ref","ObjectID",QString(label) + "_" + id ); \
		endElement(writer); \
	}

#define writePSR_Link(writer,id) \
	{ \
		startElement(writer,"cge:PSR_Link","MaxPinNum"<<"ObjectIDnd"<<"ObjectIDznd",QString::number(2) << QString::number(2) + "_0" << QString::number(2) + "_1"); \
		endElement(writer); \
	}

#define writeElementNoAttr(writer,name) \
	{ \
		startElement(writer,name,"1"<<"2","null"); \
		endElement(writer); \
	}

#define COS(X) (cos(X/180*3.1415926))
#define SIN(X) (sin(-1*X/180*3.1415926))

#include <QMap>
#include <QString>
#include <QXmlStreamWriter>

// 基本图元
void transformRect(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformRoundRect(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformLine(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformPin(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformEclipse(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformCircle(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformCircleArc(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformEclipseArc(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformDiamond(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformTriangle(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformPolygon(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformPolyline(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);

// G 文件电力图元
void transformBus(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformBreaker(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformDisconnector(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformTransformer2(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformTransformer3(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformACLineEnd(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformConnectLine(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformCapacitor_P(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformReactor_P(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformText(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformDText(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformCurve(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformTable(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformBar(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformImage(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformPoke(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformClock(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformACLine(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
void transformSensitive(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);

#endif
