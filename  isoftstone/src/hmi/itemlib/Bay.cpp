
#include "Bay.h"
#include "ItemFactory.h"
#include "CreateItem.h"

CBay::CBay(QGraphicsItem* parent ):CGraphicsComponent(parent)
{
	
}

CBay::CBay(const Bay_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsComponent(parent)
{
	m_Info = attrInfo;
}

int	 CBay::type() const
{
	return CIMGBay;
}

QGraphicsItem* CBay::clone() 
{
	CBay* pClone = new CBay();
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CBay::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
	// 此处不能设置图元位置，因为还没有加入图元，切记
}

void CBay::draw()
{
	m_devref = m_Info.devref;
	QGraphicsItem* pItem = CItemFactory::instance()->getItem(m_devref);
	CGraphicsComponent* pBay = dynamic_cast<CGraphicsComponent*>(pItem);
	if (pBay)
	{
		QString strID;
		loadItem(pBay->getFileName(),strID);
	}

	setPos(m_Info.x, m_Info.y);
}


