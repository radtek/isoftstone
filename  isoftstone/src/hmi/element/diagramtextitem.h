
#ifndef DIAGRAMTEXTITEM_H
#define DIAGRAMTEXTITEM_H

#include <QtGui>

#include "element.h"
#include "interface.h"
#include "inline.h"

class EXPORT_ELEMENT DiagramTextItem : public QGraphicsTextItem, public ISerialize
{
    Q_OBJECT

public:

    enum { Type = UserType + 3 };

    DiagramTextItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const { return Type; }

	bool getFocus();

	virtual void serialize(QDataStream& out) const;
	virtual void deserialize( QDataStream& out);

signals:
    void lostFocus(DiagramTextItem *item);
    void selectedChange(QGraphicsItem *item);

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void focusOutEvent(QFocusEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
};



#endif
