
#include <QGraphicsLineItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItemGroup>

#include <math.h>
#include <qmath.h>
#include <QPen>
#include <QColor>
#include <QFont>
#include <QObject>
#include <QPainterPath>
#include <QSet>
#include <QDebug>
#include <QFileInfo>

#include <QStringList>

#include "common.h"
#include "macro.h"
#include "CreateItem.h"
#include "ialgorithm.h"
#include "ItemFactory.h"

CGraphicsItemProxy* CGraphicsItemProxy::instance()
{
	static CGraphicsItemProxy* s_instance = NULL;
	if (!s_instance)
	{
		s_instance = new CGraphicsItemProxy(NULL);
	}
	return s_instance;
}

CGraphicsItemProxy::CGraphicsItemProxy(QGraphicsItem* parent)
{
	m_Parent = parent;
	m_ItemMap.insert("line",new CGraphicsLineItem(parent));
	m_ItemMap.insert("text",new CGraphicsTextItem(parent));
	m_ItemMap.insert("rect",new CGraphicsRectItem(parent));
	m_ItemMap.insert("circle",new CGraphicsCircleItem(parent));
	m_ItemMap.insert("pin",new CGraphicsPinItem(parent));
	m_ItemMap.insert("ellipse",new CGraphicsEllipseItem(parent));
	m_ItemMap.insert("polygon",new CGraphicsPolygonItem(parent));
	m_ItemMap.insert("handgon",new CGraphicsHandgonItem(parent));
	m_ItemMap.insert("triangle",new CGraphicsTriangleItem(parent));
	m_ItemMap.insert("diamond",new CGraphicsDiamondItem(parent));
	m_ItemMap.insert("polyline",new CGraphicsPolylineItem(parent));
	m_ItemMap.insert("handline",new CGraphicsHandlineItem(parent));
	m_ItemMap.insert("circlearc",new CGraphicsCircleArcItem(parent));
	m_ItemMap.insert("ellipsearc",new CGraphicsEllipseArcItem(parent));
	m_ItemMap.insert("roundrect",new CGraphicsRoundRectItem(parent));
	m_ItemMap.insert("image",new CGraphicsPixmapItem(parent));
}

CGraphicsItemProxy::~CGraphicsItemProxy()
{
// 	QMapIterator<QString,CGraphicsItemBase*> iter(m_ItemMap);
// 	while (iter.hasNext())
// 	{
// 		iter.next();
// 		delete iter.value();
// 	}
// 	m_ItemMap.clear();
}

QGraphicsItem* CGraphicsItemProxy::createItem(const QString& strItem,const QMap<QString,QString>& attrMap)
{
	QString strLower = strItem.toLower();
	if (m_ItemMap.contains(strLower))
	{
		CGraphicsItemBase* pBase = m_ItemMap[strLower];
		QGraphicsItem* pCloneItem = pBase->clone();
		CGraphicsItemBase* pCloneBase = dynamic_cast<CGraphicsItemBase*>(pCloneItem);
		if (pCloneBase)
		{
			pCloneBase->setGraphAttrMap(attrMap);
			pCloneBase->draw();

			return pCloneItem;
		}
	}
	return NULL;
}

QGraphicsItem* CGraphicsItemProxy::clone()
{
	return NULL;
}

// text
CGraphicsTextItem::CGraphicsTextItem(QGraphicsItem* parent):CText_Auto(),QGraphicsTextItem(parent)
{
}

QGraphicsItem* CGraphicsTextItem::clone()
{
	CLONE_ITEM(CGraphicsTextItem);
}

void CGraphicsTextItem::draw()
{
	drawText(this);
}

// Line
CGraphicsLineItem::CGraphicsLineItem(QGraphicsItem* parent):CLine_Auto(),QGraphicsLineItem(parent)
{

}

void CGraphicsLineItem::draw()
{
	drawLine(this);
}

QGraphicsItem* CGraphicsLineItem::clone()
{
	CLONE_ITEM(CGraphicsLineItem);
}

// rect
CGraphicsRectItem::CGraphicsRectItem(QGraphicsItem* parent):CRect_Auto(),QGraphicsRectItem(parent)
{

}

void CGraphicsRectItem::draw()
{
	drawRect(this);
}

QGraphicsItem* CGraphicsRectItem::clone()
{
	CLONE_ITEM(CGraphicsRectItem);
}

// circle
CGraphicsCircleItem::CGraphicsCircleItem(QGraphicsItem* parent):CCircle_Auto(),QGraphicsEllipseItem(parent)
{

}

void CGraphicsCircleItem::draw()
{
	drawCircle(this);
}

QGraphicsItem* CGraphicsCircleItem::clone()
{
	CLONE_ITEM(CGraphicsCircleItem);
}

// pin
CGraphicsPinItem::CGraphicsPinItem(QGraphicsItem* parent):CGraphicsCircleItem(parent)
{

}

void CGraphicsPinItem::draw()
{
	return CGraphicsCircleItem::draw();
}

QGraphicsItem* CGraphicsPinItem::clone()
{
	CLONE_ITEM(CGraphicsPinItem);
}

// ellipse
CGraphicsEllipseItem::CGraphicsEllipseItem(QGraphicsItem* parent):CEllipse_Auto(),QGraphicsEllipseItem(parent)
{

}

void CGraphicsEllipseItem::draw()
{
	drawEllipse(this);
}

QGraphicsItem* CGraphicsEllipseItem::clone()
{
	CLONE_ITEM(CGraphicsEllipseItem);
}

// polygon
CGraphicsPolygonItem::CGraphicsPolygonItem(QGraphicsItem* parent):CPolygon_Auto(),QGraphicsPolygonItem(parent)
{

}

void CGraphicsPolygonItem::draw()
{
	drawPolygon(this);

}

QGraphicsItem* CGraphicsPolygonItem::clone()
{
	CLONE_ITEM(CGraphicsPolygonItem);
}

// triangle
CGraphicsTriangleItem::CGraphicsTriangleItem(QGraphicsItem* parent):CTriangle_Auto(),QGraphicsPolygonItem(parent)
{

}

void CGraphicsTriangleItem::draw()
{
	drawTriangle(this);
}

QGraphicsItem* CGraphicsTriangleItem::clone()
{
	CLONE_ITEM(CGraphicsTriangleItem);
}

// diamond
CGraphicsDiamondItem::CGraphicsDiamondItem(QGraphicsItem* parent):CDiamond_Auto(),QGraphicsPolygonItem(parent)
{
	
}

void CGraphicsDiamondItem::draw()
{
	drawDiamond(this);
}

QGraphicsItem* CGraphicsDiamondItem::clone()
{
	CLONE_ITEM(CGraphicsDiamondItem);
}

// polyline
CGraphicsPolylineItem::CGraphicsPolylineItem(QGraphicsItem* parent):CPolyline_Auto(),QGraphicsPathItem(parent)
{

}

void CGraphicsPolylineItem::draw()
{
	drawPolyline(this);
}

QGraphicsItem* CGraphicsPolylineItem::clone()
{
	CLONE_ITEM(CGraphicsPolylineItem);
}

// circlearc
CGraphicsCircleArcItem::CGraphicsCircleArcItem(QGraphicsItem* parent):CCirclearc_Auto(),QGraphicsPathItem(parent)
{

}

void CGraphicsCircleArcItem::draw()
{
	drawCircleArc(this);
}

QGraphicsItem* CGraphicsCircleArcItem::clone()
{
	CLONE_ITEM(CGraphicsCircleArcItem);
}

// ellipsearc
CGraphicsEllipseArcItem::CGraphicsEllipseArcItem(QGraphicsItem* parent):CGraphicsItemBase(),QGraphicsPathItem(parent)
{

}

void CGraphicsEllipseArcItem::draw()
{
	drawEllipseArc(this);
}

QGraphicsItem* CGraphicsEllipseArcItem::clone()
{
	//CLONE_ITEM(CGraphicsEllipseArcItem);
	return NULL;
}

// roundrect
CGraphicsRoundRectItem::CGraphicsRoundRectItem(QGraphicsItem* parent):CRoundrect_Auto(),QGraphicsPathItem(parent)
{

}

void CGraphicsRoundRectItem::draw()
{
	drawRoundRect(this);
}

QGraphicsItem* CGraphicsRoundRectItem::clone()
{
	CLONE_ITEM(CGraphicsRoundRectItem);
}

// pixmap
CGraphicsPixmapItem::CGraphicsPixmapItem(QGraphicsItem* parent):CImage_Auto(),QGraphicsPixmapItem(parent)
{
	setZValue(0);
}

void CGraphicsPixmapItem::draw()
{
	drawImage(this);
}

QGraphicsItem* CGraphicsPixmapItem::clone()
{
	CLONE_ITEM(CGraphicsPixmapItem);
}

// group

CGraphicsGroupItem::CGraphicsGroupItem(QGraphicsItem* parent):QGraphicsItemGroup(parent)
{

}

void CGraphicsGroupItem::loadItem(const QString& fileName,QString& strID)
{
	m_ItemFile = fileName;

	QFileInfo fInfo(fileName);
	strID = QString("#") + fInfo.fileName() + QString(":");
	
	QMap<QString,QVector<QMap<QString,QString> > > layerMap;
	QVector<QPair<QString,QMap<QString,QString> > > vecLayer;
	QSet<QString> devRefSet;
	readElement(m_ItemFile,layerMap,vecLayer,devRefSet);

	QVectorIterator<QPair<QString,QMap<QString,QString> > > iter(vecLayer);
	while(iter.hasNext())
	{
		QPair<QString,QMap<QString,QString> > pair = iter.next();

		QGraphicsItem* pSubItem = NULL;
		QString nodeName = pair.first;
		if (nodeName == "Layer" || nodeName == "svg")
		{
			if (nodeName == "svg")
			{
				strID += layerMap[QString("svg")][0]["id"];
			}
			continue;
		}
		else
		{
			pSubItem = CGraphicsItemProxy::instance()->createItem(nodeName,pair.second);
			if (pSubItem)
			{
				addToGroup(pSubItem);
			}
		}
	}
}

QGraphicsItemGroup* CGraphicsGroupItem::clone()
{
	QGraphicsItemGroup* pGroupItem = new QGraphicsItemGroup(NULL);
	QList<QGraphicsItem *> lstItem = childItems();
	foreach(QGraphicsItem* pItem,lstItem)
	{
		CGraphicsItemBase* pBase = dynamic_cast<CGraphicsItemBase*>(pItem);
		if (pBase)
		{
			QGraphicsItem* pCloneItem = pBase->clone();
			pBase->draw();
			pGroupItem->addToGroup(pCloneItem);
		}
	}
	return pGroupItem;
}

void CGraphicsGroupItem::copy(QGraphicsItemGroup* pGroupItem)
{
	QList<QGraphicsItem *> lstItem = pGroupItem->childItems();
	foreach(QGraphicsItem* pItem,lstItem)
	{
		CGraphicsItemBase* pBase = dynamic_cast<CGraphicsItemBase*>(pItem);
		if (pBase)
		{
			QGraphicsItem* pCloneItem = pBase->clone();
			CGraphicsItemBase* pCloneBase = dynamic_cast<CGraphicsItemBase*>(pCloneItem);
			if (pCloneBase)
			{
				pCloneBase->draw();
			}
			addToGroup(pCloneItem);
		}
	}
}

void CGraphicsGroupItem::paint()
{
	QGraphicsItem* pItem = CItemFactory::instance()->getItem(m_devref);
	QGraphicsItemGroup* pGroupItem = dynamic_cast<QGraphicsItemGroup*>(pItem);
	if (pGroupItem)
	{
		copy(pGroupItem);
	}
}

// 间隔图元

CGraphicsComponent::CGraphicsComponent(QGraphicsItem* parent):QGraphicsItem(parent)
{
	m_width = 300;
	m_height = 300;
}


QRectF CGraphicsComponent::boundingRect(void) const
{
	return QRectF(0,0,m_width,m_height);
}

void CGraphicsComponent::paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget  )
{
	// 可以绘制背景
}

//  如果通过内存复制，则要考虑是基本图元还是电力图元，并且要保留原有对象属性值，可以考虑递归方式实现
QGraphicsItem* CGraphicsComponent::clone()
{
	CGraphicsComponent* pItem = new CGraphicsComponent();
	QString strID;
	pItem->loadItem(m_ItemFile,strID);
	return pItem;
}

void CGraphicsComponent::loadItem(const QString& fileName,QString& strID)
{
	m_ItemFile = fileName;
	SLayerInfo layerInfo;
	CItemFactory::instance()->drawBay(this,fileName,strID,layerInfo);
	m_width = layerInfo.width;
	m_height = layerInfo.height;
}

QString CGraphicsComponent::getFileName()
{
	return m_ItemFile;
}

void CGraphicsComponent::setPen(const QPen& pen)
{
	QList<QGraphicsItem *> lstItem = childItems();
	foreach(QGraphicsItem* pItem,lstItem)
	{
		QAbstractGraphicsShapeItem* absItem = dynamic_cast<QAbstractGraphicsShapeItem*>(pItem);
		if (absItem)
		{
			absItem->setPen(pen);
		}

		QGraphicsLineItem* lineItem = dynamic_cast<QGraphicsLineItem*>(pItem);
		if (lineItem)
		{
			lineItem->setPen(pen);
		}
		
	}

	update();
}

void CGraphicsComponent::setBrush(const QBrush& brush)
{
	QList<QGraphicsItem *> lstItem = childItems();
	foreach(QGraphicsItem* pItem,lstItem)
	{
		QAbstractGraphicsShapeItem* absItem = dynamic_cast<QAbstractGraphicsShapeItem*>(pItem);
		if (absItem)
		{
			absItem->setBrush(brush);
		}
	}

	update();
}