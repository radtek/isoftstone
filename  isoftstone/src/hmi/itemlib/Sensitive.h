#ifndef CLASS_SENSITIVE_H
#define CLASS_SENSITIVE_H

#include "interface.h"
#include "itemlib.h"
#include "Sensitive_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CSensitive : public CGraphicsGroupItem,public CSensitive_Auto,public CStaticItemBase
{
public:

	CSensitive(QGraphicsItem* parent = NULL);

	CSensitive(const Sensitive_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

	virtual QRectF boundingRect() const ;

protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:

};

#endif
