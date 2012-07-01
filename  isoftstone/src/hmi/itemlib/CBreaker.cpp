
#include "config.h"

#include "CBreaker.h"
#include "ItemFactory.h"

CCBreaker::CCBreaker(QGraphicsItem* parent):CGraphicsGroupItem(parent)
{

}

CCBreaker::CCBreaker(const CBreaker_Struct& attrInfo,QGraphicsItem* parent):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

CCBreaker::~CCBreaker() 
{
}

int	 CCBreaker::type() const
{
	return CIMGCBreaker;
}

QGraphicsItemGroup* CCBreaker::clone() 
{
	CCBreaker* pClone = new CCBreaker();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CCBreaker::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
	// 此处不能设置图元位置，因为还没有加入图元，切记
}

void CCBreaker::draw()
{
 	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

void CCBreaker::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}

