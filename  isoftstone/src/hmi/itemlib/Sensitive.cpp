
#include "Sensitive.h"

CSensitive::CSensitive(QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{

}

CSensitive::CSensitive(const Sensitive_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	m_Info =attrInfo;
}

int	 CSensitive::type() const
{
	return CIMGSensitive;
}

QGraphicsItemGroup* CSensitive::clone() 
{
	CLONE_ITEM(CSensitive);
}

void CSensitive::init() 
{
	//setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CSensitive::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

QRectF CSensitive::boundingRect() const 
{
	return QRectF(0,0,m_Info.p_RoundBox.width(),m_Info.p_RoundBox.height());
}
