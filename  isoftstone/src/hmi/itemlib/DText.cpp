
#include "DText.h"

CDText::CDText(QGraphicsItem* parent):QGraphicsTextItem(parent)
{
	init();
}

CDText::CDText(const DText_Struct& attrInfo,QGraphicsItem* parent):QGraphicsTextItem(parent)
{
	m_Info = attrInfo;
	init();
}

int	 CDText::type() const
{
	return CIMGDText;
}

void CDText::init()
{
	//setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CDText::draw()
{
	drawText(this);
}

QGraphicsItem* CDText::clone()
{
	CDText* pItem = new CDText(m_Info);
	return pItem;
}

uint CDText::getItemID()
{
	return m_Info.id;
}

quint64 CDText::keyID()
{
	return m_Info.keyid;
}

void CDText::setValue(const QVariant& varValue) 
{
	 m_Info.ts = qvariant_cast<QString>(varValue);
	 setAttrValue("ts",m_Info.ts);

	 setPlainText(m_Info.ts);
}

