
#include <math.h>

#include "ACLine.h"

#define MOVESTEP   8
#define QREAL_MARGIN  0.000001	//qreal���ͱ�����ȵıȽ�ԣ��
#define DYNAMICARROW_SIZE  15	//��̬��ͷ��С

CACLine::CACLine(QGraphicsItem* parent):QGraphicsPathItem(parent)
{
	init();
}

CACLine::CACLine(const ACLine_Struct& attrInfo,QGraphicsItem* parent):QGraphicsPathItem(parent)
{
	m_Info = attrInfo;
	init();
}

int	 CACLine::type() const
{
	return CIMGAcline;
}

void CACLine::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

QGraphicsItem* CACLine::clone(void)
{
	CACLine* cl = new CACLine(m_Info);
	return cl;
}

void CACLine::draw()
{
	drawPolyline(this);
}


void CACLine::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}
