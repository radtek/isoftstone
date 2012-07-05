
#ifndef ITEM_BASE_H
#define ITEM_BASE_H

#include <QtGui>

#include "macro.h"

class CGraphicsItemBase
{
public:

	virtual void init() {};
	virtual void draw() {};
	virtual QGraphicsItem* clone() = 0;

	virtual uint getItemID(){ return 0;};

	void setGraphAttrMap(const QMap<QString,QString>& attrMap)
	{
		m_AttrInfo.clear();
		m_AttrInfo = attrMap;
	}

	void setAttrValue(const QString& strAttr,const QString& value )
	{
		m_AttrInfo[strAttr] = value;
	}

	QString getAttrValue(const QString& strAttr)
	{
		if (m_AttrInfo.contains(strAttr))
		{
			return m_AttrInfo[strAttr];
		}
		else
		{
			return "";
		}
	}

	QPen getPen()
	{
		QPen pen;
		QStringList lstLc = getAttrValue("lc").split(',');
		if (lstLc.count() > 2)
		{
			QColor lc = QColor::fromRgb(lstLc[0].toInt(),lstLc[1].toInt(),lstLc[2].toInt());
			pen.setColor(lc);
		}
		pen.setWidth(getAttrValue("lw").toInt());
		pen.setStyle(Qt::PenStyle(getAttrValue("ls").toInt()));
		return pen;
	}

	void drawPen(QAbstractGraphicsShapeItem* pItem )
	{
		pItem->setPen(getPen());
	}
	void drawPen(QGraphicsLineItem* pItem )
	{
		pItem->setPen(getPen());
	}
	void drawBrush(QAbstractGraphicsShapeItem* pItem )
	{
		QBrush brush;
		QStringList lstFc = getAttrValue("fc").split(',');
		if (lstFc.count() > 2)
		{
			QColor fc = QColor::fromRgb(lstFc[0].toInt(),lstFc[1].toInt(),lstFc[2].toInt());
			brush.setColor(fc);
		}
		brush.setStyle(Qt::BrushStyle(getAttrValue("fm").toInt()));
		pItem->setBrush(brush);
	}

	void drawTfr(QGraphicsItem* pItem )
	{
		QStringList lstTfr = getAttrValue("tfr").split(' ');
		if (lstTfr.count() > 1)
		{
			QString strScale = lstTfr[1].remove("scale(").remove(")");
			qreal fscale = qMax(strScale.split(',')[0].toFloat(),strScale.split(',')[1].toFloat());
			pItem->setScale(fscale);
		}
	}

	void drawText(QGraphicsTextItem* pItem)
	{
		QFont font;
		//字体宽度
		font.setWeight(getAttrValue("p_FontWidth").toInt());
		//字体大小
		font.setPixelSize(getAttrValue("fs").toInt());
		//字间距
		font.setWordSpacing(getAttrValue("p_FontInterval").toInt());
		//字体高度
		//字体类型
		QString strFamily(getAttrValue("ff"));

		if (!strFamily.isEmpty())
		{
			font.setFamily(strFamily);
		}

		pItem->setFont(font);
		pItem->setPos(getAttrValue("x").toFloat(),getAttrValue("y").toFloat());

		//字体颜色
		QStringList lstLc = getAttrValue("lc").split(',');
		if (lstLc.count() > 2)
		{
			QColor color = QColor::fromRgb(lstLc[0].toInt(),lstLc[1].toInt(),lstLc[2].toInt());
			pItem->setDefaultTextColor(color);
		}

		pItem->setPlainText(getAttrValue("ts"));

		drawTfr(pItem);
	}

	void drawLine(QGraphicsLineItem* pItem)
	{
		float x1 = getAttrValue("x1").toFloat();
		float y1 = getAttrValue("y1").toFloat();
		float x2 = getAttrValue("x2").toFloat();
		float y2 = getAttrValue("y2").toFloat();

		if (x1 == x2 && y1 == y2)
		{
			return ;
		}

		drawPen(pItem);

		QPointF start;
		start.setX(x1);
		start.setY(y1);
		QPointF end;
		end.setX(x2);
		end.setY(y2);

		QLineF line(start,end);
		pItem->setLine(line);
	}

	void drawRect(QGraphicsRectItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);

		pItem->setRect(getAttrValue("x").toInt(),getAttrValue("y").toInt(),getAttrValue("w").toInt(),getAttrValue("h").toInt());
	}

	void drawCircle(QGraphicsEllipseItem* pItem)
	{
		int r = getAttrValue("r").toInt();
		if (r == 0)
		{
			return ;
		}

		drawPen(pItem);
		drawBrush(pItem);

		pItem->setRect(getAttrValue("cx").toInt() - r, getAttrValue("cy").toInt() - r,2 * r , 2 * r);
	}

	void drawEllipse(QGraphicsEllipseItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);

		pItem->setRect(getAttrValue("cx").toInt(), getAttrValue("cy").toInt(), getAttrValue("rx").toInt(), getAttrValue("ry").toInt());
	}

	void drawEllipseArc(QGraphicsPathItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);
		QPainterPath path;
		qreal cx = getAttrValue("cx").toFloat();
		qreal cy = getAttrValue("cy").toFloat();
		qreal rx = getAttrValue("rx").toFloat();
		qreal ry = getAttrValue("ry").toFloat();
		qreal a1 = getAttrValue("a1").toFloat();
		qreal a2 = getAttrValue("a2").toFloat();

		QRectF round(cx-rx,cy-ry,2*rx,2*ry);
		qreal  span = a2 - a1;
		path.arcTo(round,a1*16,span*16);
		pItem->setPath(path);
	}

	void drawCircleArc(QGraphicsPathItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);
		QPainterPath path;
		int cx = getAttrValue("cx").toInt();
		int cy = getAttrValue("cy").toInt();
		int r  = getAttrValue("r").toInt();
		int a1 = getAttrValue("a1").toInt();
		int a2 = getAttrValue("a2").toInt();

		QRectF round(cx-r,cy-r,2*r,2*r);
		int  span = qAbs(a1 - a2);

		float aa = SIN(a1);
		float bb = COS(a1);
		int fa = -1*( r * aa);
		int fb = 1*(r * bb);

		path.moveTo(cx + fb,cy + fa);
		path.arcTo(round,a1,span);
		pItem->setPath(path);
	}

	void drawRoundRect(QGraphicsPathItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);
		QPainterPath path;
		qreal x = getAttrValue("x").toFloat();
		qreal y = getAttrValue("y").toFloat();
		qreal w = getAttrValue("w").toFloat();
		qreal h = getAttrValue("h").toFloat();
		qreal cx = getAttrValue("cx").toFloat();
		qreal cy = getAttrValue("cy").toFloat();

		path.addRoundedRect(x,y,w,h,cx,cy);
		pItem->setPath(path);
	}

	void drawTriangle(QGraphicsPolygonItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);

		QPolygonF d;
		d.append(QPointF(-getAttrValue("w").toDouble()/2,getAttrValue("h").toDouble()/2));
		d.append(QPointF(getAttrValue("w").toDouble()/2,getAttrValue("h").toDouble()/2));
		d.append(QPointF(0,-getAttrValue("h").toDouble()/2));
		pItem->setPolygon(d);

		pItem->setPos(getAttrValue("x").toFloat(),getAttrValue("y").toFloat());
	}

	void drawDiamond(QGraphicsPolygonItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);

		qreal x;
		qreal y;
		qreal w;
		qreal h;

		x = getAttrValue("x").toFloat();
		y = getAttrValue("y").toFloat();
		w = getAttrValue("w").toFloat();
		h = getAttrValue("h").toFloat();

		QPolygonF d;
		d.append(QPointF(x + w/2,y));
		d.append(QPointF(x + w,y + h/2));
		d.append(QPointF(x + w/2,y + h));
		d.append(QPointF(x,y + h/2));
		pItem->setPolygon(d);
	}

	void drawPolygon(QGraphicsPolygonItem* pItem)
	{
		drawPen(pItem);
		drawBrush(pItem);

		QPolygonF d;
		QStringList lstPath = getAttrValue("d").split(' ');
		int iCount = lstPath.size();
		for (int j = 0; j < iCount; j++)
		{
			QStringList lstPoint = lstPath[j].split(',');
			if (lstPoint.count() > 1)
			{
				d.append(QPointF(lstPoint[0].toDouble(), lstPoint[1].toDouble()));
				lstPoint.clear();
			}
		}
		pItem->setPolygon(d);
	}

	void drawPolyline(QGraphicsPathItem* pItem)
	{
		drawPen(pItem);
		QPainterPath path;
		QPolygonF d;
		QStringList lstPath = getAttrValue("d").split(' ');
		int iCount = lstPath.size();
		for (int j = 0; j < iCount; j++)
		{
			QStringList lstPoint = lstPath[j].split(',');
			if (lstPoint.count() > 1)
			{
				d.append(QPointF(lstPoint[0].toDouble(), lstPoint[1].toDouble()));
				lstPoint.clear();
			}
		}
		if (d.count() > 0)
		{
			path.moveTo(d[0]);
		}
		for (int i = 1; i < d.count() ; i++)
		{
			path.lineTo(d[i]);
		}
		pItem->setPath(path);
	}

	void drawImage(QGraphicsPixmapItem* pItem)
	{
		QByteArray qbr = qgetenv(DATA_HOME);
		QString imageDir = QString(qbr.data()) + "/image/";
		QString strFile = imageDir + getAttrValue("ahref");

		qreal x = getAttrValue("x").toFloat();
		qreal y = getAttrValue("y").toFloat();
		qreal w = getAttrValue("w").toFloat();
		qreal h = getAttrValue("h").toFloat();
		QPixmap pix;
		pix.load(strFile);
		//pix.scaled(w,h);
		pItem->setPixmap(pix);
		pItem->setPos(x,y);
		
	}

protected:

	QMap<QString,QString>	m_AttrInfo;

};

#endif