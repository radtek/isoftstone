#ifndef CLASS_REACTOR_H
#define CLASS_REACTOR_H

#include "interface.h"
#include "itemlib.h"
#include "Reactor_P_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CReactor_P : public CGraphicsGroupItem,public CReactor_P_Auto,public CStaticItemBase
{
public:

	CReactor_P(QGraphicsItem* parent = NULL);

	CReactor_P(const Reactor_P_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

protected:


};

#endif
