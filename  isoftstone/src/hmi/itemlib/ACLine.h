#ifndef CLASS_ACLINE_H
#define CLASS_ACLINE_H

#include "interface.h"
#include "itemlib.h"
#include "ACLine_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CACLine : public QGraphicsPathItem,public CACLine_Auto ,public CDynamicItemBase
{
public:

	CACLine(QGraphicsItem* parent = NULL);

	CACLine(const ACLine_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual QGraphicsItem* clone(void);

	virtual void draw();

	virtual void setValue(const QVariant& varValue) ;

protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

};

#endif
