
#include "Text.h"

CText::CText(QGraphicsItem* parent):CGraphicsTextItem(parent)
{
	init();
}

CText::CText(const Text_Struct& attrInfo,QGraphicsItem* parent):CGraphicsTextItem(parent)
{
	m_Info = attrInfo;
	init();
}

int	 CText::type() const
{
	return CIMGText;
}

QGraphicsItem* CText::clone()
{
	CText* pItem = new CText(m_Info);
	return pItem;
}

uint CText::getItemID()
{
	return m_Info.id;
}

void CText::init()
{
	//setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}
