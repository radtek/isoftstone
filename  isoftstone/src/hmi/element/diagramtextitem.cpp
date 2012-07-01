
#include "diagramtextitem.h"

DiagramTextItem::DiagramTextItem(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsTextItem(parent, scene)
{
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

bool DiagramTextItem::getFocus()
{
	QTextCursor cursor = textCursor();
	cursor.clearSelection();
	setTextCursor(cursor);
    
	if (toPlainText().isEmpty()) 
	{
		deleteLater();
		return false;
	}
	return true;
}

QVariant DiagramTextItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedHasChanged)
        emit selectedChange(this);
    return value;
}

void DiagramTextItem::focusOutEvent(QFocusEvent *event)
{
    setTextInteractionFlags(Qt::NoTextInteraction);
    emit lostFocus(this);
    QGraphicsTextItem::focusOutEvent(event);
}

void DiagramTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (textInteractionFlags() == Qt::NoTextInteraction)
        setTextInteractionFlags(Qt::TextEditorInteraction);
    QGraphicsTextItem::mouseDoubleClickEvent(event);
}


void DiagramTextItem::serialize(QDataStream& out) const
{
	out << textWidth();
	out << font();
	out << defaultTextColor();
	out << toPlainText();
	QPointF point = pos();
	out << point;
	out << *this;
}

void DiagramTextItem::deserialize( QDataStream& out)
{
	qreal textwidth;
	out >> textwidth;
	setTextWidth(textwidth);

	QFont font;
	out >> font;
	setFont(font);

	QColor color;
	out >> color;
	setDefaultTextColor(color);

	QString str;
	out >> str;
	setPlainText(str);

	QPointF point;
	out >> point;
	setPos(point);

	out >> *this;
}
