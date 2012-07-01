#ifndef CLASS_CONNECTLINE_H
#define CLASS_CONNECTLINE_H


#include "interface.h"
#include "itemlib.h"
#include "ConnectLine_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CConnectLine :public QGraphicsPathItem, public CConnectLine_Auto,public CStaticItemBase
{
public:

	CConnectLine(QGraphicsItem* parent = NULL);

	CConnectLine(const ConnectLine_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItem* clone() ;

protected:

};

#endif
