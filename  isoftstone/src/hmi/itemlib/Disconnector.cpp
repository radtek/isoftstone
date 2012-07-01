
#include "Disconnector.h"
#include "ItemFactory.h"

CDisconnector::CDisconnector(QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	
}

CDisconnector::CDisconnector(const Disconnector_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CDisconnector::type() const
{
	return CIMGDisconnector;
}

QGraphicsItemGroup* CDisconnector::clone() 
{
	CDisconnector* pClone = new CDisconnector();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CDisconnector::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CDisconnector::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

void CDisconnector::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}
