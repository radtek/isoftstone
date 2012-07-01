#ifndef CLASS_CBREAKER_H
#define CLASS_CBREAKER_H

#include <QGraphicsItem>
#include <QDataStream>
#include <QString>

#include "interface.h"
#include "itemlib.h"
#include "CBreaker_Auto.h"
#include "CreateItem.h"

class EXPORT_ITEMLIB CCBreaker : public CGraphicsGroupItem,public CCBreaker_Auto,public CDynamicItemBase
{
public:

	CCBreaker(QGraphicsItem* parent = NULL);

	CCBreaker(const CBreaker_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual ~CCBreaker();

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItemGroup* clone() ;

	virtual void setValue(const QVariant& varValue) ;


protected:


private:

	//实时库中取得的数据,即熔断器的开、合状态
	int m_nSta;
};

#endif
