#ifndef CLASS_BAY_H
#define CLASS_BAY_H

#include "interface.h"
#include "itemlib.h"
#include "Bay_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CBay : public CGraphicsComponent,public CBay_Auto,public CStaticItemBase
{
public:

	CBay(QGraphicsItem* parent = NULL);

	CBay(const Bay_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItem* clone() ;

protected:

	QString m_fileName;
	QString m_devref;
};

#endif
