#ifndef CLASS_TEXT_H
#define CLASS_TEXT_H

#include "interface.h"
#include "itemlib.h"
#include "Text_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CText : public CGraphicsTextItem,public CStaticItemBase
{
public:

	CText(QGraphicsItem* parent = NULL );

	CText(const Text_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual QGraphicsItem* clone();

	virtual uint getItemID();

	virtual int	 type() const;

	virtual void init();

};

#endif
