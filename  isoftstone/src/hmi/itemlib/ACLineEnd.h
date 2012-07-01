#ifndef CLASS_ACLINEEND_H
#define CLASS_ACLINEEND_H

#include "interface.h"
#include "itemlib.h"
#include "ACLineEnd_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CACLineEnd : public QGraphicsPathItem,public CACLineEnd_Auto,public CDynamicItemBase
{
public:

	CACLineEnd(QGraphicsItem* parent = NULL);

	CACLineEnd(const ACLineEnd_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	QGraphicsItem * clone(void);

	virtual void setValue(const QVariant& varValue) ;

protected:


private:

};

#endif
