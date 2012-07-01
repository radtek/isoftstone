#ifndef CLASS_GROUNDDISCONNECTOR_H
#define CLASS_GROUNDDISCONNECTOR_H

#include "interface.h"
#include "itemlib.h"
#include "GroundDisconnector_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CGroundDisconnector : public CGraphicsGroupItem,public CGroundDisconnector_Auto,public CDynamicItemBase
{
public:

	CGroundDisconnector(QGraphicsItem* parent = NULL);

	CGroundDisconnector(const GroundDisconnector_Struct& attrInfo,QGraphicsItem* parent = NULL);

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
