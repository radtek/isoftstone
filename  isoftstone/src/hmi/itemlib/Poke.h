#ifndef CLASS_POKE_H
#define CLASS_POKE_H

#include "interface.h"
#include "itemlib.h"
#include "Poke_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CPoke :public QGraphicsRectItem, public CPoke_Auto,public CStaticItemBase
{
public:

	CPoke(QGraphicsItem* parent = NULL);

	CPoke(const Poke_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItem* clone() ;

protected:

	virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
	virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
	virtual void mousePressEvent( QGraphicsSceneMouseEvent * event );

private:

	QRectF m_rect;
	QString m_refFile;
};

#endif
