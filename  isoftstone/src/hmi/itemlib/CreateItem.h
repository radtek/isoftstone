
#ifndef CREATE_ITEM_H
#define CREATE_ITEM_H

#include <QGraphicsItem>

#include "itemlib.h"

#include "Text_Auto.h"
#include "Rect_Auto.h"
#include "Circle_Auto.h"
#include "Circlearc_Auto.h"
#include "Pie_Auto.h"
#include "Line_Auto.h"
#include "Ellipse_Auto.h"
#include "Polygon_Auto.h"
#include "Polyline_Auto.h"
#include "Triangle_Auto.h"
#include "Diamond_Auto.h"
#include "Handline_Auto.h"
#include "Image_Auto.h"
#include "Roundrect_Auto.h"

#define CLONE_ITEM(ITEM_CLASS) \
	ITEM_CLASS* pClone = new ITEM_CLASS(); \
	pClone->m_AttrInfo = m_AttrInfo; \
	pClone->m_Info = m_Info; \
	return pClone;

// 代理
class EXPORT_ITEMLIB CGraphicsItemProxy 
{
public:

	static CGraphicsItemProxy* instance();

	CGraphicsItemProxy(QGraphicsItem* parent = NULL);

	~CGraphicsItemProxy();

	virtual QGraphicsItem* createItem(const QString& strItem,const QMap<QString,QString>& attrMap);

	virtual QGraphicsItem* clone();

protected:

	QMap<QString,CGraphicsItemBase*> m_ItemMap;
	QGraphicsItem* m_Parent;
};

// 文本
class EXPORT_ITEMLIB CGraphicsTextItem : public CText_Auto ,public QGraphicsTextItem
{
public:

	CGraphicsTextItem(QGraphicsItem* parent = NULL);

	virtual QGraphicsItem* clone();
	virtual void draw();

protected:


};

// 直线
class EXPORT_ITEMLIB CGraphicsLineItem : public CLine_Auto,public QGraphicsLineItem
{
public:

	CGraphicsLineItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 矩形
class EXPORT_ITEMLIB CGraphicsRectItem : public CRect_Auto,public QGraphicsRectItem
{
public:

	CGraphicsRectItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 圆
class EXPORT_ITEMLIB CGraphicsCircleItem : public CCircle_Auto,public QGraphicsEllipseItem
{
public:

	CGraphicsCircleItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 小圆
class EXPORT_ITEMLIB CGraphicsPinItem : public CGraphicsCircleItem
{
public:

	CGraphicsPinItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 椭圆
class EXPORT_ITEMLIB CGraphicsEllipseItem : public CEllipse_Auto,public QGraphicsEllipseItem
{
public:

	CGraphicsEllipseItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 多边形
class EXPORT_ITEMLIB CGraphicsPolygonItem : public CPolygon_Auto,public QGraphicsPolygonItem
{
public:

	CGraphicsPolygonItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

typedef CGraphicsPolygonItem CGraphicsHandgonItem;

// 三角形
class EXPORT_ITEMLIB CGraphicsTriangleItem : public CTriangle_Auto,public QGraphicsPolygonItem
{
public:

	CGraphicsTriangleItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 菱形
class EXPORT_ITEMLIB CGraphicsDiamondItem : public CDiamond_Auto,public QGraphicsPolygonItem
{
public:

	CGraphicsDiamondItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 多线段
class EXPORT_ITEMLIB CGraphicsPolylineItem : public CPolyline_Auto,public QGraphicsPathItem
{
public:

	CGraphicsPolylineItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

typedef CGraphicsPolylineItem CGraphicsHandlineItem;

// 圆弧
class EXPORT_ITEMLIB CGraphicsCircleArcItem : public CCirclearc_Auto,public QGraphicsPathItem
{
public:

	CGraphicsCircleArcItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 椭圆弧
class EXPORT_ITEMLIB CGraphicsEllipseArcItem : public CGraphicsItemBase,public QGraphicsPathItem
{
public:

	CGraphicsEllipseArcItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 圆角矩形
class EXPORT_ITEMLIB CGraphicsRoundRectItem : public CRoundrect_Auto,public QGraphicsPathItem
{
public:

	CGraphicsRoundRectItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

};

// 位图
class EXPORT_ITEMLIB CGraphicsPixmapItem : public CImage_Auto,public QGraphicsPixmapItem
{
public:

	CGraphicsPixmapItem(QGraphicsItem* parent = NULL);

	virtual void draw();

	virtual QGraphicsItem* clone();

private:

	QString m_imageDir;

};

// 组合
class EXPORT_ITEMLIB CGraphicsGroupItem : public QGraphicsItemGroup
{
public:

	CGraphicsGroupItem(QGraphicsItem* parent = NULL);

	virtual void loadItem(const QString& fileName,QString& strID);

	virtual QGraphicsItemGroup* clone();

	virtual void copy(QGraphicsItemGroup* pGroupItem);

	virtual void paint();

protected:
	
	QString m_ItemFile;

	QString m_devref;

};

// 间隔图元
class EXPORT_ITEMLIB CGraphicsComponent : public QGraphicsItem
{
public:

	CGraphicsComponent(QGraphicsItem* parent = NULL);

	QRectF boundingRect(void) const;

	virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );

	void setPen(const QPen& pen);

	void setBrush(const QBrush& brush);

	virtual QGraphicsItem* clone();

	virtual void loadItem(const QString& fileName,QString& strID);

	QString getFileName();

protected:

	QString m_ItemFile;

	int		m_width;
	int		m_height;
};

#endif 