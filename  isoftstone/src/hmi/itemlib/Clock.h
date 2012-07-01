#ifndef CLASS_CLOCK_H
#define CLASS_CLOCK_H

#include "interface.h"
#include "itemlib.h"
#include "Clock_Auto.h"
#include "CreateItem.h"

#include <QGraphicsProxyWidget>
#include <QLCDNumber>

class EXPORT_ITEMLIB CClock : public QGraphicsProxyWidget,public CClock_Auto ,public CStaticItemBase
{
public:

	CClock(QGraphicsItem* parent = NULL);

	~CClock();

	CClock(const Clock_Struct& attrInfo,QGraphicsItem* parent = NULL);

	virtual int	 type() const;

	virtual void init();

	virtual QGraphicsItem* clone(void);

	virtual void draw();

protected:

	void update();

	virtual void timerEvent(QTimerEvent * );

protected:

	int		m_timerID;
	QLCDNumber* m_lcd;
	int		m_digit;

};

#endif