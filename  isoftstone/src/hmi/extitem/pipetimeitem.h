
#ifndef PIPE_TIME_ITEM_H
#define PIPE_TIME_ITEM_H

#include "extitem.h"

class EXPORT_EXTITEM CPipeTimeItem : public QGraphicsObject
{

public:

	CPipeTimeItem(QGraphicsItem* parent = 0);


	virtual QRectF boundingRect() const;

	virtual void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

	void setTimeColor(QColor color);

	QColor getTimeColor();

protected:

	virtual void timerEvent(QTimerEvent * event);

private:

	void drawPipeText(QPainter *painter, QRect &rect, char *cText);

	void drawPipeNum(QPainter *painter, QRect &rect, int wNumber);

private:

	QRectF		m_Rect;
	QColor		m_timecolor;					//时间颜色
	QFont		m_timepipefont;					//晶体管字体
	int			m_timerID;

};

#endif