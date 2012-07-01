
#include <math.h>

#include "ConnectLine.h"

#define DRAW_NOTHING	-1//不绘制
#define DRAW_ORINGNAL	0//绘制原形

CConnectLine::CConnectLine(QGraphicsItem* parent):QGraphicsPathItem(parent)
{

}

CConnectLine::CConnectLine(const ConnectLine_Struct& attrInfo,QGraphicsItem* parent):QGraphicsPathItem(parent)
{
	m_Info = attrInfo;
}

int	 CConnectLine::type() const
{
	return CIMGConnectLine;
}

QGraphicsItem* CConnectLine::clone() 
{
	 CConnectLine* cl = new CConnectLine(m_Info);
	 return cl;
}

void CConnectLine::init() 
{
	setFlags(QGraphicsItem::ItemIsFocusable|QGraphicsItem::ItemIsSelectable);
}

void CConnectLine::draw()
{
	drawPolyline(this);
}