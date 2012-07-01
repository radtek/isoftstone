
#include "Generator.h"
#include "ItemFactory.h"

CGenerator::CGenerator(QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{

}

CGenerator::CGenerator(const Generator_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CGenerator::type() const
{
	return CIMGGenerator;
}

QGraphicsItemGroup* CGenerator::clone() 
{
	CGenerator* pClone = new CGenerator();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CGenerator::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CGenerator::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

// void CGenerator::setValue(const QVariant& varValue) 
// {
// 	 Q_UNUSED(varValue);
// }


