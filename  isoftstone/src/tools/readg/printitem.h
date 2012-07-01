
#include <QGraphicsItem>

class QPen;

class CGraphicsItemBase
{
public:

	virtual QGraphicsItem* createItem() = 0;

	virtual QGraphicsItem* clone() = 0;

	void setAttrMap(const QMap<QString,QString>& attrMap);

protected:
	QPen drawPen();
	void drawPen(QAbstractGraphicsShapeItem* pItem);
	void drawPen(QGraphicsLineItem* pItem);
	void drawBrush(QAbstractGraphicsShapeItem* pItem);

protected:

	QMap<QString,QString>	m_AttrMap;

	QGraphicsItem*			m_Parent;

};


// 文本
class CGraphicsTextItem : public CGraphicsItemBase
{
public:

	CGraphicsTextItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 直线
class CGraphicsLineItem : public CGraphicsItemBase
{
public:

	CGraphicsLineItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 矩形
class CGraphicsRectItem : public CGraphicsItemBase
{
public:

	CGraphicsRectItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 圆
class CGraphicsCircleItem : public CGraphicsItemBase
{
public:

	CGraphicsCircleItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 小圆
class CGraphicsPinItem : public CGraphicsCircleItem
{
public:

	CGraphicsPinItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 椭圆
class CGraphicsEllipseItem : public CGraphicsItemBase
{
public:

	CGraphicsEllipseItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 多边形
class CGraphicsPolygonItem : public CGraphicsItemBase
{
public:

	CGraphicsPolygonItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

typedef CGraphicsPolygonItem CGraphicsHandgonItem;

// 三角形
class CGraphicsTriangleItem : public CGraphicsItemBase
{
public:

	CGraphicsTriangleItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 菱形
class CGraphicsDiamondItem : public CGraphicsItemBase
{
public:

	CGraphicsDiamondItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 多线段
class CGraphicsPolylineItem : public CGraphicsItemBase
{
public:

	CGraphicsPolylineItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

typedef CGraphicsPolylineItem CGraphicsHandlineItem;

// 圆弧
class CGraphicsCircleArcItem : public CGraphicsItemBase
{
public:

	CGraphicsCircleArcItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 椭圆弧
class CGraphicsEllipseArcItem : public CGraphicsItemBase
{
public:

	CGraphicsEllipseArcItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 圆角矩形
class CGraphicsRoundRectItem : public CGraphicsItemBase
{
public:

	CGraphicsRoundRectItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// 位图
class CGraphicsPixmapItem : public CGraphicsItemBase
{
public:

	CGraphicsPixmapItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

private:

	QString m_imageDir;

};

