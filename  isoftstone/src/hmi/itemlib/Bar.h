#ifndef CLASS_BAR_H
#define CLASS_BAR_H

#include "interface.h"
#include "itemlib.h"
#include "Bar_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CBar :public QGraphicsRectItem, public CBar_Auto,public CDynamicItemBase
{
public:

	CBar(QGraphicsItem* parent = NULL);

	CBar(const Bar_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	QGraphicsItem* clone(void);

	virtual QRectF boundingRect() const ;

	virtual void setValue(const QVariant& varValue) ;


protected:

	//virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

private:

};

#endif
