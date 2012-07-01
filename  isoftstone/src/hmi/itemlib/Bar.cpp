
#include "Bar.h"

CBar::CBar(QGraphicsItem* parent) :QGraphicsRectItem(parent)
{
}

int	 CBar::type() const
{
	return CIMGBar;
}

void CBar::init() 
{
}

QGraphicsItem* CBar::clone(void)
{
	return NULL;
}

QRectF CBar::boundingRect() const 
{
	 QRectF boundRect;

	 return boundRect;
}


void CBar::setValue(const QVariant& varValue) 
{
	 Q_UNUSED(varValue);
}

