#ifndef CLASS_CAPCITOR_H
#define CLASS_CAPCITOR_H

#include "interface.h"
#include "itemlib.h"
#include "Capacitor_P_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CCapacitor_P : public CGraphicsGroupItem,public CCapacitor_P_Auto,public CDynamicItemBase
{
public:

	CCapacitor_P(QGraphicsItem* parent = NULL);

	CCapacitor_P(const Capacitor_P_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

	virtual void setValue(const QVariant& varValue) ;


protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:

};

#endif
