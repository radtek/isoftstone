
#include "Poke.h"
#include "event.h"
#include "config.h"

CPoke::CPoke(QGraphicsItem* parent ):QGraphicsRectItem(parent)
{
}

CPoke::CPoke(const Poke_Struct& attrInfo,QGraphicsItem* parent )
{
	m_Info = attrInfo;
}

int	 CPoke::type() const
{
	return CIMGPoke;
}

QGraphicsItem* CPoke::clone() 
{
	 CPoke* cl = new CPoke(m_Info);
	 return cl;
}

void CPoke::init() 
{
	setAcceptHoverEvents(true);
	setAcceptsHoverEvents(true);
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
	setCursor(Qt::PointingHandCursor);
	m_rect = QRectF(m_Info.x,m_Info.y,m_Info.w,m_Info.h);
	m_rect.setX(m_Info.x- m_Info.p_RoundBox.x() - m_Info.p_RoundBox.width()/2.0);
	m_rect.setY(m_Info.y - m_Info.p_RoundBox.y() - m_Info.p_RoundBox.height()/2.0);
	m_rect.setWidth(m_Info.w);
	m_rect.setHeight(m_Info.h);

	m_refFile = m_Info.ahref;
	setToolTip(m_refFile);

	setZValue(1000);
}

void CPoke::draw()
{
	drawPen(this);
	setRect(getAttrValue("x").toInt(),getAttrValue("y").toInt(),getAttrValue("w").toInt(),getAttrValue("h").toInt());
}

void CPoke::hoverEnterEvent ( QGraphicsSceneHoverEvent * event )
{
	QPen pen;
	pen.setWidth(1);
	pen.setColor(Qt::yellow);
	setPen(pen);
}

void CPoke::hoverLeaveEvent ( QGraphicsSceneHoverEvent * event )
{
	setPen(Qt::NoPen);
}

void CPoke::mousePressEvent( QGraphicsSceneMouseEvent * event )
{
	if (event->buttons() & Qt::LeftButton)
	{
		QString fileName = CConfig::instance()->getFilePath(m_Info.ahref);
		QApplication::postEvent(scene(),new CSceneFileChangeEvent(fileName));
	}
}