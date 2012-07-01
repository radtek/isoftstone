#ifndef CLASS_TRANSFORMER3_H
#define CLASS_TRANSFORMER3_H

#include "interface.h"
#include "itemlib.h"
#include "Transformer3_Auto.h"
#include "Transformer2_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CTransformer2 :public CGraphicsGroupItem, public CTransformer2_Auto,public CDynamicItemBase
{
public:

	CTransformer2(QGraphicsItem* parent = NULL);

	CTransformer2(const Transformer2_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

	virtual void setValue(const QVariant& varValue) ;


protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:

};

class EXPORT_ITEMLIB CTransformer3 :public CGraphicsGroupItem, public CTransformer3_Auto,public CDynamicItemBase
{
public:

	CTransformer3(QGraphicsItem* parent = NULL);

	CTransformer3(const Transformer3_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

	virtual void setValue(const QVariant& varValue) ;


protected:


private:

};

#endif
