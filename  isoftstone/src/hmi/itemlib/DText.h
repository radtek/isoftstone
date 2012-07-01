#ifndef CLASS_DTEXT_H
#define CLASS_DTEXT_H

#include "interface.h"
#include "itemlib.h"
#include "DText_Auto.h"
#include "CreateItem.h"

/*  图元由基础图形，自动序列化属性（包含模型属性），动态数据接口组成*/
class EXPORT_ITEMLIB CDText :public QGraphicsTextItem,public CDText_Auto, public CDynamicItemBase
{
public:

	CDText(QGraphicsItem* parent = NULL);

	CDText(const DText_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItem* clone();

	virtual uint getItemID();

	virtual quint64 keyID();

	virtual void setValue(const QVariant& varValue) ;
};

#endif
