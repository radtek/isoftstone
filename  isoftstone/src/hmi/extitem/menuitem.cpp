
#include "menuitem.h"


CMenuItem::CMenuItem(const QPixmap &pixmap, QAction* pAction,QGraphicsObject *parent ): 
QGraphicsObject(parent), m_pixmap(pixmap),m_action(pAction),m_text(pAction->text()),m_parentMenu(parent)
{
	setAcceptsHoverEvents(true);
	setAcceptHoverEvents(true);
	setZValue(1000);

	setFlag(QGraphicsItem::ItemIsFocusable);

	m_bSubMenu = false;
	if (pAction->menu() != NULL)
	{
		m_bSubMenu = true;
	}
	m_bShowed = false;
	m_bMenu = true;
	m_defaultColor = QColor(4802889);
	m_defaultColor.setAlpha(200);
	m_bkColor = m_defaultColor;
	m_factor = 1;
}

void CMenuItem::setBackPixmap(QPixmap& bkPixmap)
{
	m_bkPixmap = bkPixmap;
}

void CMenuItem::setItemWidth(int w)
{
	m_bkRect = boundingRect();
	m_bkRect.setWidth(w);
	update();
}

void CMenuItem::setStyle(bool bMenu )
{
	m_bMenu = bMenu;
}

void CMenuItem::setScaleFactor(qreal xfactor,qreal yfactor)
{
}

QRectF CMenuItem::boundingRect() const
{
	if (m_pixmap.isNull())
	{
		QRectF r(0, 0, 150, 25);
		m_bkRect = r;
	}
	else
	{
		m_bkRect.setX(0);
		m_bkRect.setY(0);
		m_bkRect.setWidth(m_pixmap.width());
		m_bkRect.setHeight(m_pixmap.height());
	}
	
	return m_bkRect;
}

QAction* CMenuItem::getAction()
{
	return m_action;
}

void CMenuItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	painter->save();
	painter->setPen(QColor(2471412));
	if (m_bMenu)
	{
		bool down = option->state & QStyle::State_Sunken;
		QRectF r = m_bkRect;
		int length = m_text.length();

		QBrush brush(m_bkColor,Qt::SolidPattern);
		painter->setBrush(brush);
		painter->drawRoundedRect(r,r.height()/10, r.height()/10, Qt::RelativeSize);

		painter->setPen(Qt::white);
		painter->setFont(QFont("Arial", r.height()/2));
		if (m_bSubMenu)
		{
			int diff = r.height()/3;
			QPointF pos1 = QPointF(r.right() -r.height()/2 - diff ,r.top() + diff);
			QPointF pos2 = QPointF(r.right() -r.height()/2 - diff ,r.bottom() - diff);
			QPointF pos3 = QPointF(r.right() -r.width()/10,r.top() + r.height()/2 );
			QPolygonF polygon ;
			polygon.append(pos1);
			polygon.append(pos2);
			polygon.append(pos3);

			QBrush brush2(Qt::black,Qt::SolidPattern);
			painter->setBrush(brush2);
			painter->drawPolygon(polygon,Qt::OddEvenFill);
		}
		painter->drawText(m_bkRect, Qt::AlignCenter, m_text);
	}
	else
	{
		painter->drawPixmap(QRect(0,0,ITEM_WIDTH,ITEM_HEIGHT), m_pixmap);
	}

	painter->restore();
}

void CMenuItem::mousePressEvent(QGraphicsSceneMouseEvent *)
{
	m_bkColor = Qt::lightGray;
	m_bShowed = !m_bShowed;
	emit onClicked(m_bSubMenu);
	m_action->trigger();
	
}

void CMenuItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
	m_bkColor = m_defaultColor;
	update();
}

void CMenuItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
	if (m_bMenu)
	{
		m_bkColor = Qt::blue;
	}

	update();

	if (m_bSubMenu)
	{
		emit onClicked(m_bSubMenu);
	}
	
	emit onHoverEntered(m_bSubMenu);
}

void CMenuItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	m_bkColor = m_defaultColor;
	update();
	emit onHoverLeaved();
}

void CMenuItem::setTransform2(qreal scale,qreal rotate)
{
	QTransform transform;
	transform.translate(boundingRect().width()/2,boundingRect().height()/2);
	//transform.scale(scale,scale);
	transform.rotate(rotate,Qt::XAxis);
	transform.translate(-boundingRect().width()/2,-boundingRect().height()/2);
	setTransform(transform,false);
	update();
}
