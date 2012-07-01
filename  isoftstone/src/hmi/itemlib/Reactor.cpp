
#include "Reactor.h"
#include "ItemFactory.h"

CReactor_P::CReactor_P(QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	
}

CReactor_P::CReactor_P(const Reactor_P_Struct& attrInfo,QGraphicsItem* parent ):CGraphicsGroupItem(parent)
{
	m_Info = attrInfo;
}

int	 CReactor_P::type() const
{
	return CIMGReactor_P;
}

QGraphicsItemGroup* CReactor_P::clone() 
{
	CReactor_P* pClone = new CReactor_P();
	pClone->copy(this);
	pClone->m_AttrInfo = m_AttrInfo;
	pClone->m_Info = m_Info; 
	return pClone;
}

void CReactor_P::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
	// �˴���������ͼԪλ�ã���Ϊ��û�м���ͼԪ���м�
}

void CReactor_P::draw()
{
	m_devref = m_Info.devref;
	CGraphicsGroupItem::paint();
	setPos(m_Info.x, m_Info.y);
}


