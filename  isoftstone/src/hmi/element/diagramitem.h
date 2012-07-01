
#ifndef DIAGRAMITEM_H
#define DIAGRAMITEM_H

#include <QtGui>

#include "element.h"
#include "interface.h"
#include "inline.h"

class Arrow;

class EXPORT_ELEMENT DiagramItem : public QGraphicsPolygonItem ,public ISerialize
{
public:
    enum { Type = UserType + 15 };
    enum DiagramType { Step, Conditional, StartEnd, Io };

	DiagramItem(QMenu *contextMenu,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    DiagramItem(DiagramType diagramType, QMenu *contextMenu,QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    void removeArrow(Arrow *arrow);

    void removeArrows();

    DiagramType diagramType() const { return myDiagramType; }

	QPolygonF polygon() const 
	{
		return QGraphicsPolygonItem::polygon(); 
	}

    void addArrow(Arrow *arrow);

    QPixmap image() const;

    int type() const { return Type;}

	virtual void serialize(QDataStream& out) const;
	virtual void deserialize( QDataStream& out);

protected:

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:

    DiagramType myDiagramType;
    QPolygonF myPolygon;
    QMenu *myContextMenu;
    QList<Arrow *> arrows;
};


#endif
