#ifndef CLASS_BUS_H
#define CLASS_BUS_H

#include "interface.h"
#include "itemlib.h"
#include "Bus_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CBus :public QGraphicsLineItem, public CBus_Auto,public CDynamicItemBase
{
public:

	CBus(QGraphicsItem* parent = NULL);

	CBus(const Bus_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItem* clone() ;

	virtual void setValue(const QVariant& varValue) ;


protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:


};

#endif
