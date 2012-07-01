
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


// �ı�
class CGraphicsTextItem : public CGraphicsItemBase
{
public:

	CGraphicsTextItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// ֱ��
class CGraphicsLineItem : public CGraphicsItemBase
{
public:

	CGraphicsLineItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// ����
class CGraphicsRectItem : public CGraphicsItemBase
{
public:

	CGraphicsRectItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// Բ
class CGraphicsCircleItem : public CGraphicsItemBase
{
public:

	CGraphicsCircleItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// СԲ
class CGraphicsPinItem : public CGraphicsCircleItem
{
public:

	CGraphicsPinItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// ��Բ
class CGraphicsEllipseItem : public CGraphicsItemBase
{
public:

	CGraphicsEllipseItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// �����
class CGraphicsPolygonItem : public CGraphicsItemBase
{
public:

	CGraphicsPolygonItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

typedef CGraphicsPolygonItem CGraphicsHandgonItem;

// ������
class CGraphicsTriangleItem : public CGraphicsItemBase
{
public:

	CGraphicsTriangleItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// ����
class CGraphicsDiamondItem : public CGraphicsItemBase
{
public:

	CGraphicsDiamondItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// ���߶�
class CGraphicsPolylineItem : public CGraphicsItemBase
{
public:

	CGraphicsPolylineItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

typedef CGraphicsPolylineItem CGraphicsHandlineItem;

// Բ��
class CGraphicsCircleArcItem : public CGraphicsItemBase
{
public:

	CGraphicsCircleArcItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// ��Բ��
class CGraphicsEllipseArcItem : public CGraphicsItemBase
{
public:

	CGraphicsEllipseArcItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// Բ�Ǿ���
class CGraphicsRoundRectItem : public CGraphicsItemBase
{
public:

	CGraphicsRoundRectItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

};

// λͼ
class CGraphicsPixmapItem : public CGraphicsItemBase
{
public:

	CGraphicsPixmapItem(QGraphicsItem* parent);

	virtual QGraphicsItem* createItem();

	virtual QGraphicsItem* clone();

private:

	QString m_imageDir;

};

