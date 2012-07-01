
#include "ACLineEnd.h"

CACLineEnd::CACLineEnd(QGraphicsItem* parent):QGraphicsPathItem(parent)
{
	init();
}

CACLineEnd::CACLineEnd(const ACLineEnd_Struct& attrInfo,QGraphicsItem* parent):QGraphicsPathItem(parent)
{
	m_Info = attrInfo;
	init();
}

int	 CACLineEnd::type() const
{
	return CIMGACLineEnd;
}

void CACLineEnd::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

QGraphicsItem * CACLineEnd::clone(void)
{
	CACLineEnd* cl = new CACLineEnd(m_Info);
	return cl;
}

void CACLineEnd::draw()
{
	drawPolyline(this);
}

void CACLineEnd::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}

