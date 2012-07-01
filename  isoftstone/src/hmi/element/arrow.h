
#ifndef ARROW_H
#define ARROW_H

#include <QtGui>

#include "element.h"
#include "interface.h"
#include "inline.h"
#include "diagramitem.h"


class EXPORT_ELEMENT Arrow : public QGraphicsLineItem,public ISerialize
{
public:

    enum { Type = UserType + 4 };

	Arrow();

    Arrow(DiagramItem *startItem, DiagramItem *endItem,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const { return Type; }

    QRectF boundingRect() const;

    QPainterPath shape() const;

    void setColor(const QColor &color);

	void setScene(QGraphicsScene* scene);

    DiagramItem *startItem() const;

    DiagramItem *endItem() const;

	static void drawArraw(QGraphicsScene* scene,QGraphicsLineItem **linkLine,const QColor& lineColor);

	void build();
	virtual void serialize(QDataStream& out) const;
	virtual void deserialize( QDataStream& out);

public slots:

    void updatePosition();

protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

private:

	QGraphicsScene* m_scene;
    DiagramItem* m_StartItem;
    DiagramItem* m_EndItem;
    QColor		 m_Color;
    QPolygonF	 m_ArrowHead;
};



#endif
