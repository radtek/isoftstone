
#include <math.h>

#include "Bus.h"

CBus::CBus(QGraphicsItem* parent):QGraphicsLineItem(parent)
{

}

CBus::CBus(const Bus_Struct& attrInfo,QGraphicsItem* parent):QGraphicsLineItem(parent)
{
	m_Info = attrInfo;
}

int	 CBus::type() const
{
	return CIMGBus;
}

QGraphicsItem* CBus::clone() 
{
	 CBus* cl = new CBus(m_Info);
	 return cl;
}

void CBus::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CBus::draw()
{
	drawLine(this);
}

void CBus::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}
