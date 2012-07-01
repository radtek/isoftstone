
#ifndef TRANSCOMMON_H
#define TRANSCOMMON_H


#include <QMap>
#include <QString>
#include <QTextStream>

#define startElement(writer,name,lstNames,lstValues,level) \
	{\
		QStringList attrNames ; \
		attrNames << lstNames; \
		QStringList attrValues ; \
		attrValues << lstValues; \
		QString strTab = ""; \
		for(int l = 0 ; l < level ; l++) \
		{ \
				strTab += "\t"; \
		} \
		writer << strTab << name << "\n"; \
		writer << strTab << "{" << "\n"; \
		if(attrNames.count() == attrValues.count() && attrNames[0] != "") \
		{ \
			int i = 0; \
			foreach(QString attr,attrNames) \
			{ \
				writer << strTab << "\t" << attr << ": " << attrValues[i++] << "\n"; \
			} \
		}

#define endElement(writer) \
		writer << strTab << "}" << "\n"; \
	}

inline void readRect(const QMap<QString,QString>& attrMap,QStringList& attrs,QStringList& values,const QString& attr)
{
	if (attrMap.contains(attr))
	{
		if (attr == "w")
		{
			attrs << "width";
		}
		else if (attr == "h")
		{
			attrs << "height";
		}
		else
		{
			attrs << attr;
		}
		values.append(attrMap[attr]);
	}
}

inline void readLC(const QMap<QString,QString>& attrMap,QStringList& attrs,QStringList& values)
{
	if (attrMap.contains("lc"))
	{
		attrs << "color";
		values.append("Qt.rgba(" + attrMap.value("lc") + ",255)");
	}
}

inline void readLW(const QMap<QString,QString>& attrMap,QStringList& attrs,QStringList& values)
{
	if (attrMap.contains("lw"))
	{
		attrs << "width";
		values.append(attrMap.value("lw"));
	}
}

inline void readFC(const QMap<QString,QString>& attrMap,QStringList& attrs,QStringList& values)
{
	if(attrMap.contains("fc"))
	{
		int fm = 0;
		if (attrMap.contains("fm"))
		{
			fm = attrMap["fm"].toInt();
		}
		if (fm > 0)
		{
			attrs << "fill";
			values.append(QString("Qt.rgba(") + attrMap.value("fc") + ",255)");
		}
	}
}

inline void readTfr(QTextStream& writer,const QMap<QString,QString>& attrMap,QStringList& attrs,QStringList& values)
{
	if (attrMap.contains("tfr"))
	{
		startElement(writer,"transform","","",2);

		QStringList values1 = attrMap.value("tfr").split(' ');
		if (values1.count() > 0)
		{
			QString v = QString("Rotation {");
			QString rotate = values1[0];
			v = v + "angle:" + rotate.remove("rotate(").remove(")");
			v += "}";
			
			writer << "\t\t\t" << v << "\n";
		}
		if (values1.count() > 1)
		{
			QString v = QString("Scale {");
			QString scale = values1[1];
			scale.remove("scale(").remove(")");
			QStringList lst = scale.split(",");
			if (lst.count() > 0)
			{
				v = v + "xScale:" + lst[0];
			}
			if (lst.count() > 1)
			{
				v = v + "; yScale:" + lst[1];
			}
			
			v += "}";
			writer << "\t\t\t" << v << "\n";
		}

		endElement(writer);
	}
}


// 基本图元
void transformRect(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformRoundRect(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformLine(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformPin(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformEclipse(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformCircle(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformCircleArc(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformEclipseArc(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformDiamond(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformTriangle(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformPolygon(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformPolyline(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);

// G 文件电力图元
void transformBus(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformBreaker(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformDisconnector(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformTransformer2(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformTransformer3(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformACLineEnd(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformConnectLine(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformCapacitor_P(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformReactor_P(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformText(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformDText(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformCurve(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformTable(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformBar(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformImage(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformPoke(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformClock(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformACLine(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
void transformSensitive(const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);

#endif
