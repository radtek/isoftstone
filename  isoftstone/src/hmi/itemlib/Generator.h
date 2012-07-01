#ifndef CLASS_GENERATOR_H
#define CLASS_GENERATOR_H

#include "interface.h"
#include "itemlib.h"
#include "Generator_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CGenerator : public CGraphicsGroupItem,public CGenerator_Auto,public CStaticItemBase
{
public:

	CGenerator(QGraphicsItem* parent = NULL);

	CGenerator(const Generator_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

	//virtual void setValue(const QVariant& varValue) ;


protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:

};

#endif
