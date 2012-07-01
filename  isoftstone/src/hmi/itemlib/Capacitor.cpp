
#include "Capacitor.h"
#include "ItemFactory.h"

CCapacitor_P::CCapacitor_P(QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{

}

CCapacitor_P::CCapacitor_P(const Capacitor_P_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CCapacitor_P::type() const
{
	return CIMGCapacitor_P;
}

QGraphicsItemGroup* CCapacitor_P::clone() 
{
	CCapacitor_P* pClone = new CCapacitor_P();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CCapacitor_P::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CCapacitor_P::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

void CCapacitor_P::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}


