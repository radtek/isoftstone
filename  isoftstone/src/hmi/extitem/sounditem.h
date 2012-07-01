#ifndef SOUND_ITEM_H
#define SOUND_ITEM_H


#include "extitem.h"

class EXPORT_EXTITEM CSoundItem : public QGraphicsObject
{
    Q_OBJECT
public:
    CSoundItem(QGraphicsItem *parent = 0);

public slots:

    void setValue(int num);
	
	QRectF boundingRect() const;

protected:

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

	void paintAlarm(QPainter* painter);
	void paintRect(QPainter* painter);
	void paintNumber(QPainter* painter);

	void init();

private:

	int		m_value;
	QBrush	m_brush;
	QPen	m_pen;
	int		m_count;

};

#endif // MYLCDNUMBER_H
