
#include "GroundDisconnector.h"
#include "ItemFactory.h"

CGroundDisconnector::CGroundDisconnector(QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	
}

CGroundDisconnector::CGroundDisconnector(const GroundDisconnector_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CGroundDisconnector::type() const
{
	return CIMGDisconnector;
}

QGraphicsItemGroup* CGroundDisconnector::clone() 
{
	CGroundDisconnector* pClone = new CGroundDisconnector();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CGroundDisconnector::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CGroundDisconnector::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

void CGroundDisconnector::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}
