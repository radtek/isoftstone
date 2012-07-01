
#ifndef CURVE_H
#define CURVE_H

#include <QtGui>
#include <QGraphicsItem>
#include <QGraphicsObject>

#include "itemlib.h"

class EXPORT_ITEMLIB CCurve : public QGraphicsObject
{
public:

	CCurve(QGraphicsItem* parent = 0 );

	~CCurve();
	
	void setCurveTitle(const QString& title);

	void setXTitle(const QString& title);
	void setYTitle(const QString& title);

	void setWidth(int width);
	void setHeight(int height);

	void setXAxis(qreal fStart,qreal fEnd,qreal fStep);
	void setYAxis(qreal fStart,qreal fEnd,qreal fStep);

	void setShowReal(bool breal);
	void setShowGrid(bool bgrid);
	void setShowMaxMin(bool bmaxmin);
	void setShowBackGround(bool bBack);

	void setBackGround(QColor bkColor);
	void setLineColor(quint64 keyid,QColor color);
	QColor getLineColor(quint64 keyid);

	void addCurve(quint64 keyid,QColor = Qt::red);
	void removeCurve(quint64 keyid);

	virtual QRectF boundingRect() const;
	virtual void   paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );


protected:

	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	virtual void wheelEvent ( QGraphicsSceneWheelEvent * event );
	virtual void dragEnterEvent ( QGraphicsSceneDragDropEvent * event );
	virtual void dragLeaveEvent ( QGraphicsSceneDragDropEvent * event );
	virtual void dragMoveEvent ( QGraphicsSceneDragDropEvent * event );
	virtual void dropEvent ( QGraphicsSceneDragDropEvent * event );
	virtual void timerEvent(QTimerEvent * event);

private:

	void init();

protected:

	int			m_width;
	int			m_height;

	QString		m_title;
	QString		m_xTitle;
	QString		m_yTitle;

	qreal		m_xStart;
	qreal		m_xEnd;
	qreal		m_xStep;

	qreal		m_yStart;
	qreal		m_yEnd;
	qreal		m_yStep;

	bool		m_bReal;
	bool		m_bGrid;
	bool		m_bMaxMin;
	bool		m_bBack;

	int			m_timerID;

	QColor		m_bkColor;
	QMap<quint64,QColor> m_colorMap;
	QMap<quint64,QVector<QVector2D > >	 m_ValueMap; // 存储某个测点的连续值
};

#endif