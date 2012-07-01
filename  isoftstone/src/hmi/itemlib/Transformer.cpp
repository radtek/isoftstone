
#include "Transformer.h"
#include "ItemFactory.h"

CTransformer2::CTransformer2(QGraphicsItem* parent):CGraphicsGroupItem(parent)
{
	
}

CTransformer2::CTransformer2(const Transformer2_Struct& attrInfo,QGraphicsItem* parent):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CTransformer2::type() const
{
	return CIMGTransformer2;
}

QGraphicsItemGroup* CTransformer2::clone() 
{
	CTransformer2* pClone = new CTransformer2();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CTransformer2::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
	// 此处不能设置图元位置，因为还没有加入图元，切记
}

void CTransformer2::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}

void CTransformer2::setValue(const QVariant& varValue) 
{
	Q_UNUSED(varValue);
}


//  CTransformer3

CTransformer3::CTransformer3(QGraphicsItem* parent):CGraphicsGroupItem(parent)
{

}

CTransformer3::CTransformer3(const Transformer3_Struct& attrInfo,QGraphicsItem* parent):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CTransformer3::type() const
{
	return CIMGTransformer3;
}

QGraphicsItemGroup* CTransformer3::clone() 
{
	CTransformer3* pClone = new CTransformer3();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CTransformer3::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
	// 此处不能设置图元位置，因为还没有加入图元，切记
}

void CTransformer3::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}


void CTransformer3::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}
