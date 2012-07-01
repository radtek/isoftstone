
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QStringList>
#include <QFile>
#include <QRegExp>
#include <QMap>
#include <QVector>
#include <math.h>

#include "transcommon.h"

void transformBus(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("d"))
		{
			QString dv = attrMap.value("d");
			QRegExp exp("(\\s|,)");
			QStringList lst = dv.split(exp);
			if (lst.count() > 0)
			{
				attrs << "d";

				QString svgd = QString("M ");
				for (int i = 0 ; i < lst.count() ; i++)
				{
					svgd = svgd + lst[i] + " ";
					if (i > 0 && i%2 == 1 && i < lst.count() -1)
					{
						svgd += "L ";
					}
				}
				values.append(svgd.simplified());
			}
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("voltype"))
		{
			attrs << "class";
			QString cls = attrMap.value("voltype");
			values.append("kV500");
		}
		startElement(writer,"path",attrs,values)
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR(writer,"_BusbarSection",id)
			}
			endElement(writer);
		}

	}
	endElement(writer);
}

void transformBreaker(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		//if (attrMap.contains("w"))
		{
			attrs << "width";
			values.append("31.3");
		}
		//if (attrMap.contains("w"))
		{
			attrs << "height";
			values.append("26");
		}
		if (attrMap.contains("devref"))
		{
			attrs << "xlink:href";
			QString href = attrMap.value("devref");
			values.append(href);
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("voltype"))
		{
			attrs << "class";
			QString cls = attrMap.value("voltype");
			values.append("kV500");
		}
 		if (attrMap.contains("tfr"))
 		{
			//attrs << "transform";
			//values.append(attrMap.value("tfr"));
 			//QStringList values1 = attrMap.value("tfr").split(' ');
 			//if (values1.count() > 0)
 			//{
 			//	attrs << "transform";
 			//	QString rotate = values1[0];
 			//	values.append(rotate);
 			//}
 		}
		startElement(writer,"use",attrs,values);
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR(writer,"_Breaker",id);
				//writeMeas(writer,"_Measurement_P",id);
			}
			endElement(writer);
		}
	}
	endElement(writer);
}

void transformDisconnector(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		QString roundBox = attrMap.value("p_RoundBox");
		QStringList lstBox = roundBox.split(',');
		if (lstBox.count() == 4)
		{
			attrs << "width";
			float w = lstBox[2].toFloat();
			values.append(QString::number(w - 5));
			attrs << "height";
			float h = lstBox[3].toFloat();
			values.append(QString::number(h - 5));
		}
		else
		{
			attrs << "width";
			values.append("11");
			attrs << "height";
			values.append("20");
		}
		if (attrMap.contains("devref"))
		{
			attrs << "xlink:href";
			QString href = attrMap.value("devref");
			values.append(href);
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("voltype"))
		{
			attrs << "class";
			QString cls = attrMap.value("voltype");
			values.append("kV500");
		}
		if (attrMap.contains("tfr"))
		{
			//attrs << "transform";
			//values.append(attrMap.value("tfr"));
			//QStringList values1 = attrMap.value("tfr").split(' ');
			//if (values1.count() > 0)
			//{
			//	attrs << "transform";
			//	QString rotate = values1[0];
			//	values.append(rotate);
			//}
		}
		startElement(writer,"use",attrs,values);
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR(writer,"_Disconnector",id);
				//writeMeas(writer,"_Measurement_P",id);
			}
			endElement(writer);
		}
	}
	endElement(writer);
}

void transformTransformer2(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		//if (attrMap.contains("w"))
		{
			attrs << "width";
			values.append("58.6");
		}
		//if (attrMap.contains("w"))
		{
			attrs << "height";
			values.append("46");
		}
		if (attrMap.contains("devref"))
		{
			attrs << "xlink:href";
			QString href = attrMap.value("devref");
			values.append(href);
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("voltype"))
		{
			attrs << "class";
			QString cls = attrMap.value("voltype");
			values.append("kV-1");
		}
		if (attrMap.contains("tfr"))
		{
			//attrs << "transform";
			//values.append(attrMap.value("tfr"));
			//QStringList values1 = attrMap.value("tfr").split(' ');
			//if (values1.count() > 0)
			//{
			//	attrs << "transform";
			//	QString rotate = values1[0];
			//	values.append(rotate);
			//}
		}
		startElement(writer,"use",attrs,values);
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR(writer,"_PowerTransformer",id);
			}
			endElement(writer);
		}
	}
	endElement(writer);
}

void transformTransformer3(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	transformTransformer2(attrMap,writer,nID);
}

void transformACLineEnd(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{

}

void transformConnectLine(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("d"))
		{
			QString dv = attrMap.value("d");
			QRegExp exp("(\\s|,)");
			QStringList lst = dv.split(exp);
			if (lst.count() > 0)
			{
				attrs << "d";
 				QString svgd = QString("M ");
 				for (int i = 0 ; i < lst.count() ; i++)
 				{
 					svgd = svgd + lst[i] + " ";
 					if (i > 0 && i%2 == 1 && i < lst.count() -1)
 					{
 						svgd += "L ";
 					}
 				}
				values.append(svgd.simplified());
			}
		}
		//if (attrMap.contains("lw"))
		{
			attrs << "stroke";
			values.append("rgb(255,255,0)");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("voltype"))
		{
			attrs << "class";
			QString cls = attrMap.value("voltype");
			values.append("kV220");
		}
		startElement(writer,"path",attrs,values)
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR_Link(writer,id)
			}
			endElement(writer);
		}

	}
	endElement(writer);
}

void transformCapacitor_P(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		//if (attrMap.contains("w"))
		{
			attrs << "width";
			values.append("23.2");
		}
		//if (attrMap.contains("w"))
		{
			attrs << "height";
			values.append("38");
		}
		if (attrMap.contains("devref"))
		{
			attrs << "xlink:href";
			QString href = attrMap.value("devref");
			values.append(href);
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		//if (attrMap.contains("voltype"))
		{
			attrs << "class";
			QString cls = attrMap.value("voltype");
			values.append("kV66");
		}
		if (attrMap.contains("tfr"))
		{
			// 此处处理不合理，会造成图元偏差很大
			//attrs << "transform";
			//values.append(attrMap.value("tfr"));
			//QStringList values1 = attrMap.value("tfr").split(' ');
			//if (values1.count() > 0)
			//{
			//	attrs << "transform";
			//	QString rotate = values1[0];
			//	values.append(rotate);
			//}
		}
		startElement(writer,"use",attrs,values);
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
// 				writePSR(writer,"_Breaker",id);
// 				writeMeas(writer,"_Measurement_P",id);
			}
			endElement(writer);
		}
	}
	endElement(writer);
}

void transformReactor_P(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{

}

void transformText(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			float y = 0;
			attrs << "y";
			y = attrMap.value("y").toFloat();
// 			float fh = attrMap.value("p_FontHeight").toFloat();
// 			if (y < fh)
// 			{
// 				y = fh;
// 			}
			values.append(QString::number(y));
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append(QString("rgb(") + attrMap.value("lc") + ")");

			attrs << "fill";
			values.append(QString("rgb(") + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("p_FontWidth"))
		{
			attrs << "font-size";
			QString fs = attrMap.value("p_FontWidth");
			values.append(fs);
		}
		//if (attrMap.contains("p_FontWidth"))
		{
			attrs << "font-weight";
			//QString fs = attrMap.value("p_FontWidth");
			values.append("bolder");
		}
		if (attrMap.contains("font-family"))
		{
			attrs << "font-family";
			QString cls = attrMap.value("font-family");
			values.append(QObject::tr("宋体"));
		}
		//if (attrMap.contains("lc"))
// 		{
// 			attrs << "fill";
// 			QString lc = attrMap.value("lc");
// 			//values.append(QString("rgb(") + lc + ")");
// 			values.append("rgb(255,255,255)");
// 		}
		startElement(writer,"text",attrs,values);
		if (attrMap.contains("ts"))
		{
			writer.writeCharacters(attrMap.value("ts"));
		}
		endElement(writer);
	}
}

void transformDText(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("p_FontWidth"))
		{
			attrs << "font-size";
			QString cls = attrMap.value("p_FontWidth");
			values.append(cls);
		}
		if (attrMap.contains("font-family"))
		{
			attrs << "font-family";
			QString cls = attrMap.value("font-family");
			values.append("Dialog");
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			QString lc = attrMap.value("lc");
			values.append(QString("rgb(") + lc + ")");
		}
		startElement(writer,"text",attrs,values);
		writer.writeCharacters("↓0.0");
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR(writer,"_Measurement_A",id);
			}
			endElement(writer);
		}
	}
	endElement(writer);
}

void transformRect(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		if (attrMap.contains("w"))
		{
			attrs << "width";
			values.append(attrMap.value("w"));
		}
		if (attrMap.contains("h"))
		{
			attrs << "height";
			values.append(attrMap.value("h"));
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		//if (attrMap.contains("stroke"))
		{
			attrs << "lineStyle";
			//QString cls = attrMap.value("stroke");
			values.append("0");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			//QString cls = attrMap.value("stroke");
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"rect",attrs,values);
		endElement(writer);
	}
}

void transformRoundRect(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			values.append(attrMap.value("x"));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			values.append(attrMap.value("y"));
		}
		if (attrMap.contains("w"))
		{
			attrs << "width";
			values.append(attrMap.value("w"));
		}
		if (attrMap.contains("h"))
		{
			attrs << "height";
			values.append(attrMap.value("h"));
		}
		if (attrMap.contains("rx"))
		{
			attrs << "rx";
			values.append(attrMap.value("rx"));
		}
		if (attrMap.contains("ry"))
		{
			attrs << "ry";
			values.append(attrMap.value("ry"));
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		//if (attrMap.contains("stroke"))
		{
			attrs << "lineStyle";
			//QString cls = attrMap.value("stroke");
			values.append("0");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			//QString cls = attrMap.value("stroke");
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"rect",attrs,values);
		endElement(writer);
	}
}

void transformLine(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x1"))
		{
			attrs << "x1";
			values.append(attrMap.value("x1"));
		}
		if (attrMap.contains("y1"))
		{
			attrs << "y1";
			values.append(attrMap.value("y1"));
		}
		if (attrMap.contains("x2"))
		{
			attrs << "x2";
			values.append(attrMap.value("x2"));
		}
		if (attrMap.contains("y2"))
		{
			attrs << "y2";
			values.append(attrMap.value("y2"));
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"line",attrs,values);
		endElement(writer);
	}
}

void transformPin(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	transformCircle(attrMap,writer,nID);
}

void transformEclipse(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("cx"))
		{
			attrs << "cx";
			values.append(attrMap.value("cx"));
		}
		if (attrMap.contains("cy"))
		{
			attrs << "cy";
			values.append(attrMap.value("cy"));
		}
		if (attrMap.contains("rx"))
		{
			attrs << "rx";
			values.append(attrMap.value("rx"));
		}
		if (attrMap.contains("ry"))
		{
			attrs << "ry";
			values.append(attrMap.value("ry"));
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"eclipse",attrs,values);
		endElement(writer);
	}
}

void transformCircle(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("cx"))
		{
			attrs << "cx";
			values.append(attrMap.value("cx"));
		}
		if (attrMap.contains("cy"))
		{
			attrs << "cy";
			values.append(attrMap.value("cy"));
		}
		if (attrMap.contains("r"))
		{
			attrs << "r";
			values.append(attrMap.value("r"));
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"circle",attrs,values);
		endElement(writer);
	}
}

void transformCircleArc(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;
		QString strD = "M ";
		
		qreal cx;
		qreal cy;
		qreal r;
		qreal a1;
		qreal a2;

		if (attrMap.contains("cx"))
		{
			cx = attrMap["cx"].toFloat();
		}
		if (attrMap.contains("cy"))
		{
			cy = attrMap["cy"].toFloat();
		}
		if (attrMap.contains("r"))
		{
			r = attrMap["r"].toFloat();
		}
		if (attrMap.contains("a1"))
		{
			a1 = attrMap["a1"].toFloat();
		}
		if (attrMap.contains("a2"))
		{
			a2 = attrMap["a2"].toFloat();
		}

		strD += QString::number(cx + r*COS(a2)) + " ";
		strD += QString::number(cy + r*SIN(a2)) + " ";
		strD += "A ";
		strD += QString::number(r) + " ";
		strD += QString::number(r) + " ";
		strD += "0 1 1 ";
		strD += QString::number(cx + r*COS(a1)) + " ";
		strD += QString::number(cy + r*SIN(a1));

		if(1)
		{
			attrs << "d";
			values.append(strD);
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"path",attrs,values);
		endElement(writer);
	}
}

void transformEclipseArc(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;
		QString strD = "M ";

		qreal cx;
		qreal cy;
		qreal rx;
		qreal ry;
		qreal a1;
		qreal a2;

		//if (attrMap.contains("sta"))
		//{
		//	if (attrMap["sta"].toInt() == 0)
		//	{
		//		return;
		//	}
		//}

		if (attrMap.contains("cx"))
		{
			cx = attrMap["cx"].toFloat();
		}
		if (attrMap.contains("cy"))
		{
			cy = attrMap["cy"].toFloat();
		}
		if (attrMap.contains("rx"))
		{
			rx = attrMap["rx"].toFloat();
		}
		if (attrMap.contains("ry"))
		{
			ry = attrMap["ry"].toFloat();
		}
		if (attrMap.contains("a1"))
		{
			a1 = attrMap["a1"].toFloat();
		}
		if (attrMap.contains("a2"))
		{
			a2 = attrMap["a2"].toFloat();
		}

		strD += QString::number(cx + rx*COS(a2)) + " ";
		strD += QString::number(cy + ry*SIN(a2)) + " ";
		strD += "A ";
		strD += QString::number(rx) + " ";
		strD += QString::number(ry) + " ";
		strD += "0 1 1 ";
		strD += QString::number(cx + rx*COS(a1)) + " ";
		strD += QString::number(cy + ry*SIN(a1));

		if(1)
		{
			attrs << "d";
			values.append(strD);
		}
		if(1)
		{
			attrs << "fill";
			values.append("none");
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"path",attrs,values);
		endElement(writer);
	}
}

void transformDiamond(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;
		QString strD = "";

		qreal x;
		qreal y;
		qreal w;
		qreal h;

		if (attrMap.contains("x"))
		{
			x = attrMap["x"].toFloat();
		}
		if (attrMap.contains("y"))
		{
			y = attrMap["y"].toFloat();
		}
		if (attrMap.contains("w"))
		{
			w = attrMap["w"].toFloat();
		}
		if (attrMap.contains("h"))
		{
			h = attrMap["h"].toFloat();
		}

		strD += QString::number(x + w/2) + "," + QString::number(y) + " ";
		strD += QString::number(x + w) + "," + QString::number(y + h/2) + " ";
		strD += QString::number(x + w/2) + "," + QString::number(y + h) + " ";
		strD += QString::number(x ) + "," + QString::number(y + h/2) ;

		if(1)
		{
			attrs << "points";
			values.append(strD);
		}
		if(1)
		{
			attrs << "fill";
			values.append("none");
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"polygon",attrs,values);
		endElement(writer);
	}
}

void transformTriangle(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;
		QString strD = "";

		qreal x;
		qreal y;
		qreal w;
		qreal h;

		if (attrMap.contains("x"))
		{
			x = attrMap["x"].toFloat();
		}
		if (attrMap.contains("y"))
		{
			y = attrMap["y"].toFloat();
		}
		if (attrMap.contains("w"))
		{
			w = attrMap["w"].toFloat();
		}
		if (attrMap.contains("h"))
		{
			h = attrMap["h"].toFloat();
		}

		strD += QString::number(x + w/2) + "," + QString::number(y) + " ";
		strD += QString::number(x + w) + "," + QString::number(y + h) + " ";
		strD += QString::number(x ) + "," + QString::number(y + h) ;

		if(1)
		{
			attrs << "points";
			values.append(strD);
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"polygon",attrs,values);
		endElement(writer);
	}
}

void transformPolygon(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString strD = "";

		if (attrMap.contains("d"))
		{
			strD = attrMap["d"];
		}

		if(1)
		{
			attrs << "points";
			values.append(strD);
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"polygon",attrs,values);
		endElement(writer);
	}
}

void transformPolyline(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString strD = "";

		if (attrMap.contains("d"))
		{
			strD = attrMap["d"];
		}

		if(1)
		{
			attrs << "points";
			values.append(strD);
		}
		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			values.append(attrMap.value("lw"));
		}
		startElement(writer,"polyline",attrs,values);
		endElement(writer);
	}
}

void transformCurve(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{

}

void transformTable(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{

}

void transformBar(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{

}
void transformImage(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("x"))
		{
			attrs << "x";
			float x = attrMap.value("x").toFloat();
			x = x+5;
			values.append(QString::number(x));
		}
		if (attrMap.contains("y"))
		{
			attrs << "y";
			float y = attrMap.value("y").toFloat();
			y = y-14;
			values.append(QString::number(y));
		}
		if (attrMap.contains("w"))
		{
			attrs << "width";
			values.append(attrMap.value("w"));
		}
		if (attrMap.contains("h"))
		{
			attrs << "height";
			values.append(attrMap.value("h"));
		}
		if (attrMap.contains("ahref"))
		{
			attrs << "xlink:href";
			values.append(QString("../../image/")+ attrMap.value("ahref"));
		}
		startElement(writer,"image",attrs,values);
		endElement(writer);
	}
}

void transformPoke(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("ahref"))
		{
			attrs << "xlink:href";
			values.append(QString("")+ attrMap.value("ahref"));
		}

		startElement(writer,"a",attrs,values);
		{
			QStringList attrs;
			QStringList values;
			if (attrMap.contains("p_RoundBox"))
			{
				QString roundBox = attrMap.value("p_RoundBox");
				QStringList lstBox = roundBox.split(',');
				if (lstBox.count() == 4)
				{
					attrs << "x";
					values.append(lstBox[0]);
					attrs << "y";
					float y = lstBox[1].toFloat();
					y = y-10;
					values.append(QString::number(y));
					attrs << "width";
					values.append(lstBox[2]);
					attrs << "height";
					values.append(lstBox[3]);
				}
			}
			if (1)
			{
				attrs << "fill";
				values.append("blue");
			}
			if (1)
			{
				attrs << "lineStyle";
				values.append("1");
			}
			if (1)
			{
				attrs << "stroke";
				values.append("1");
			}
			if (1)
			{
				attrs << "opacity";
				values.append("0.0");
			}
			startElement(writer,"rect",attrs,values);
			endElement(writer);
		}
		endElement(writer);
	}
}

void transformClock(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	transformRect(attrMap,writer,nID);
}

void transformACLine(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	startElement(writer,"g","id",strID)
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("d"))
		{
			QString dv = attrMap.value("d");
			QRegExp exp("(\\s|,)");
			QStringList lst = dv.split(exp);
			if (lst.count() > 0)
			{
				attrs << "d";
				//QString svgd = QString("M ") + lst[0] + " " + lst[1] + " L " + lst[2] + " " + lst[3]; 
				//QString svgd = QString("M ") + lst[0] + " " + lst[1] + " L " + lst[2] + " " + lst[3]; 
				QString svgd = QString("M ");
				for (int i = 0 ; i < lst.count() ; i++)
				{
					svgd = svgd + lst[i] + " ";
					if (i > 0 && i%2 == 1 && i < lst.count() -1)
					{
						svgd += "L ";
					}
				}
				values.append(svgd.simplified());
			}
		}
		if (attrMap.contains("id"))
		{
			attrs << "id";
			id = attrMap.value("id");
			values.append(id);
		}
		if (attrMap.contains("tfr"))
		{
			//attrs << "transform";
			//values.append(attrMap.value("tfr"));
			//QStringList values1 = attrMap.value("tfr").split(' ');
			//if (values1.count() > 0)
			//{
			//	attrs << "transform";
			//	QString rotate = values1[0];
			//	values.append(rotate);
			//}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			QString cls = attrMap.value("lc");
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		startElement(writer,"path",attrs,values);
		endElement(writer);
		{
			startElement(writer,"metadata","1"<<"2","null") 
			{
				//writePSR(writer,"_ACLineSegment",id)
			}
			endElement(writer);
		}

	}
	endElement(writer);
}

void transformSensitive(const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID)
{
	QString strID = QString::number(nID);
	{
		QStringList attrs;
		QStringList values;

		QString id ;

		if (attrMap.contains("p_RoundBox"))
		{
			QString roundBox = attrMap.value("p_RoundBox");
			QStringList lstBox = roundBox.split(',');
			if (lstBox.count() == 4)
			{
				float x = lstBox[0].toFloat();
				float y = lstBox[1].toFloat();
				float w = lstBox[2].toFloat();
				float h = lstBox[3].toFloat();
				float cx = x + w/2;
				float cy = y + h/2;
				float r = std::min(w/4,h/4);

				attrs << "cx";
				values.append(QString::number(cx));
				attrs << "cy";
				values.append(QString::number(cy));
				attrs << "r";
				values.append(QString::number(r));
			}
		}

		if(attrMap.contains("fc"))
		{
			attrs << "fill";
			int fm = 0;
			if (attrMap.contains("fm"))
			{
				fm = attrMap["fm"].toInt();
			}
			if (fm > 0)
			{
				values.append(QString("rgb(") + attrMap.value("fc") + ")");
			}
			else
			{
				values.append("none");
			}
		}
		if (attrMap.contains("lc"))
		{
			attrs << "stroke";
			values.append("rgb(" + attrMap.value("lc") + ")");
		}
		//if (attrMap.contains("stroke"))
		{
			attrs << "lineStyle";
			//QString cls = attrMap.value("stroke");
			values.append("0");
		}
		if (attrMap.contains("lw"))
		{
			attrs << "stroke-width";
			//QString cls = attrMap.value("stroke");
			values.append(attrMap.value("lw"));
		}
		//if (attrMap.contains("xlink:href"))
		//{
		//	attrs << "xlink:href";
		//	QString href = attrMap.value("xlink:href");
		//	values.append(href);
		//}
		startElement(writer,"circle",attrs,values);
		endElement(writer);
	}
}