#ifndef CLASS_DISCONNECTOR_H
#define CLASS_DISCONNECTOR_H

#include "interface.h"
#include "itemlib.h"
#include "Disconnector_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CDisconnector : public CGraphicsGroupItem,public CDisconnector_Auto,public CDynamicItemBase
{
public:

	CDisconnector(QGraphicsItem* parent = NULL);

	CDisconnector(const Disconnector_Struct& attrInfo,QGraphicsItem* parent = NULL);

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
