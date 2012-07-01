#ifndef CLASS_UICONTEXT_AUTO_H
#define CLASS_UICONTEXT_AUTO_H

#include <QGraphicsItem>
#include <QDataStream>
#include <QString>
#include <QObject>
#include <QFontMetrics>
#include <QFont>
#include <QRect>
#include <QRectF>
#include <QPen>
#include <QBrush>
#include <QPainter>
#include <QPixmap>
#include <QVariant>

#include <math.h>

#include "rapidxml.hpp"
#include "interface.h"
#include "GEnum.h"
#include "itembase.h"


using namespace rapidxml;


struct UiContext_Struct
{

	UiContext_Struct& operator=(const UiContext_Struct& cp)
	{
		return *this;
	}
};

class CUiContext_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase 
{
public:
	virtual void serialize(QDataStream& out) const
	{
	}

	virtual void deserialize( QDataStream& out)
	{
	}
	virtual void serialize(xml_node<char>* node) const
	{
		xml_attribute<char>* attr = NULL;

	}

	virtual void deserialize( xml_node<char>* node)
	{
		xml_attribute<char>* attr = NULL;

	}
	UiContext_Struct getInfo()
	{
		return m_Info;
	}
protected:

	UiContext_Struct m_Info ;
};

#endif
