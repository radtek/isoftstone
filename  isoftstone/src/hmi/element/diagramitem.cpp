
#include "resource.h"
#include "diagramitem.h"
#include "arrow.h"

DiagramItem::DiagramItem(QMenu *contextMenu,
						 QGraphicsItem *parent, QGraphicsScene *scene)
						 : QGraphicsPolygonItem(parent, scene)
{
	myContextMenu = contextMenu;
}

DiagramItem::DiagramItem(DiagramType diagramType, QMenu *contextMenu,
             QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsPolygonItem(parent, scene)
{
    myDiagramType = diagramType;
    myContextMenu = contextMenu;

    QPainterPath path;
    switch (myDiagramType) {
        case StartEnd:
            path.moveTo(200, 50);
            path.arcTo(150, 0, 50, 50, 0, 90);
            path.arcTo(50, 0, 50, 50, 90, 90);
            path.arcTo(50, 50, 50, 50, 180, 90);
            path.arcTo(150, 50, 50, 50, 270, 90);
            path.lineTo(200, 25);
            myPolygon = path.toFillPolygon();
            break;
        case Conditional:
            myPolygon << QPointF(-100, 0) << QPointF(0, 100)
                      << QPointF(100, 0) << QPointF(0, -100)
                      << QPointF(-100, 0);
            break;
        case Step:
            myPolygon << QPointF(-100, -100) << QPointF(100, -100)
                      << QPointF(100, 100) << QPointF(-100, 100)
                      << QPointF(-100, -100);
            break;
        default:
            myPolygon << QPointF(-120, -80) << QPointF(-70, 80)
                      << QPointF(120, 80) << QPointF(70, -80)
                      << QPointF(-120, -80);
            break;
    }
    setPolygon(myPolygon);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

void DiagramItem::removeArrow(Arrow *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1)
        arrows.removeAt(index);
}

void DiagramItem::removeArrows()
{
    foreach (Arrow *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void DiagramItem::addArrow(Arrow *arrow)
{
    arrows.append(arrow);
}

QPixmap DiagramItem::image() const
{
	return CResource::createPixmap(myPolygon,QColor("orange"));
}

void DiagramItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    myContextMenu->exec(event->screenPos());
}

QVariant DiagramItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (Arrow *arrow, arrows) {
            arrow->updatePosition();
        }
    }

    return value;
}

void DiagramItem::serialize(QDataStream& out) const
{
	out << myDiagramType;
	out << shape();
	out << brush();
	out << pen();
	qreal zvalue = zValue();
	out << zvalue;
	QPointF point = pos();
	out << point;
	out << *this;
}

void DiagramItem::deserialize( QDataStream& out)
{
	qint32 ntype;
	out >> ntype;
	myDiagramType = DiagramType(ntype);

	QPainterPath paths;
	out >> paths;
	setPolygon(paths.toFillPolygon());

	QBrush brush;
	out >> brush;
	setBrush(brush);

	QPen pen;
	out >> pen;
	setPen(pen);

	qreal zvalue;
	out >> zvalue;
	setZValue(zvalue);

	QPointF point;
	out >> point;
	setPos(point);

	out >> *this;

}