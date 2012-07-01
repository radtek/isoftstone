
#include <iterator>
#include <QFile>
#include <QTextOStream>
#include <QtCore>
#include <QtConcurrentMap>
#include <QElapsedTimer>

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

#include "ACLine.h"
#include "ACLineEnd.h"
#include "Bar.h"
#include "Bus.h"
#include "CBreaker.h"
#include "ConnectLine.h"
#include "DText.h"
#include "Poke.h"
#include "Sensitive.h"
#include "Text.h"
#include "Transformer.h"
#include "Disconnector.h"
#include "Reactor.h"
#include "Capacitor.h"
#include "Generator.h"
#include "GroundDisconnector.h"

#include "Bay.h"

#include "Clock.h"
#include "Image.h"

#include "common.h"
#include "CreateItem.h"
#include "ItemFactory.h"
#include "ialgorithm.h"
#include "config.h"

using namespace rapidxml;

CItemFactory* CItemFactory::instance()
{
	static CItemFactory* s_ItemFactory = NULL;
	if (s_ItemFactory == NULL)
	{
		s_ItemFactory = new CItemFactory();
	}
	return s_ItemFactory;
}

CItemFactory::CItemFactory()
{
	createBasicItem();
}

bool CItemFactory::draw(QGraphicsScene* pScene,const QString& strFile)
{
	if (!QFile::exists(strFile))
		return false;
	pScene->clear();
	xml_document<> doc;
	file<> content(strFile.toLocal8Bit().data());
	doc.parse<0>(content.data());
	xml_node<>* rootNode = doc.first_node();
	if (!rootNode)
	{
		return false;
	}
	for (xml_node<>* graphLayerNode = rootNode->first_node(); graphLayerNode; graphLayerNode = graphLayerNode->next_sibling())
	{
		SLayerInfo stLayer;
		for (xml_attribute<>* attr = graphLayerNode->first_attribute();attr;attr = attr->next_attribute())
		{
			QString name = QString(attr->name());
			QString value = QString(attr->value());
			if ( name == "x")
			{
				stLayer.x = value.toInt();
			}
			else if ( name == "y")
			{
				stLayer.y = value.toInt();
			}
			if ( name == "w")
			{
				stLayer.width = value.toInt();
			}
			else if ( name == "h")
			{
				stLayer.height = value.toInt();
			}
			else if ( name == "BackPixmapFlag")
			{
				stLayer.backPixmapFlag = value.toInt();
			}
			else if ( name == "BackPixmapName")
			{
				stLayer.backPixmapName = value;
			}
			else if ( name == "bgc")
			{
				QStringList lstLc = value.split(',');
				QColor color = QColor::fromRgb(lstLc[0].toInt(),lstLc[1].toInt(),lstLc[2].toInt());
				stLayer.backColor = color;
			}
			else if ( name == "show")
			{
				stLayer.show = value.toInt();
			}
		}
		
		// 设置图层
		pScene->setSceneRect(QRectF(stLayer.x,stLayer.y,stLayer.width,stLayer.height));

		if (stLayer.backPixmapFlag)
		{
			pScene->setBackgroundBrush(QBrush(QImage(stLayer.backPixmapName)));
		}
		else
		{
			pScene->setBackgroundBrush(QBrush(stLayer.backColor));
		}
		
		// 通过xml节点去串行化文件，也可以通过一次性读入内存，然后在内存中去创建图元
		// 后者的的好处在于将创建和读取分离，两者没有必然的联系
		for (xml_node<>* itemNode = graphLayerNode->first_node(); itemNode; itemNode = itemNode->next_sibling())
		{
			QString strItemName = itemNode->name();
			{
				// 此处可以获得基本类型元对象
				QGraphicsItem* pTempItem = getItem(strItemName);
				CGraphicsItemBase* pTempBase = dynamic_cast<CGraphicsItemBase*>(pTempItem);
				if (pTempBase)
				{
					QGraphicsItem* pCloneItem = pTempBase->clone();
					CGraphicsItemBase* pCloneBase = dynamic_cast<CGraphicsItemBase*>(pCloneItem);
					if (pCloneBase)
					{
						GSerialize* pSerial = dynamic_cast<GSerialize*>(pCloneItem);
						pSerial->deserialize(itemNode);
						pCloneBase->init();
						pCloneBase->draw();
						pScene->addItem(pCloneItem);
					}
				}
			}		
		}
	}
	return true;
}


bool CItemFactory::drawBay(QGraphicsItem* parentItem,const QString& strFile,QString& strID,SLayerInfo& stLayer)
{
	if (!QFile::exists(strFile))
		return false;
	xml_document<> doc;
	file<> content(strFile.toLocal8Bit().data());
	doc.parse<0>(content.data());
	xml_node<>* rootNode = doc.first_node();
	if (!rootNode)
	{
		return false;
	}
	for (xml_node<>* bayNode = rootNode->first_node(); bayNode; bayNode = bayNode->next_sibling())
	{
		QFileInfo fInfo(strFile);
		strID = QString("#") + fInfo.fileName() + QString(":") ;
		for (xml_attribute<>* attr = bayNode->first_attribute();attr;attr = attr->next_attribute())
		{
			if (QString(attr->name()) == QString("id"))
			{
				strID = strID + QString(attr->value());
				break;
			}
		}

		for (xml_node<>* graphLayerNode = bayNode->first_node(); graphLayerNode; graphLayerNode = graphLayerNode->next_sibling())
		{
			for (xml_attribute<>* attr = graphLayerNode->first_attribute();attr;attr = attr->next_attribute())
			{
				QString name = QString(attr->name());
				QString value = QString(attr->value());
				if ( name == "x")
				{
					stLayer.x = value.toInt();
				}
				else if ( name == "y")
				{
					stLayer.y = value.toInt();
				}
				if ( name == "w")
				{
					stLayer.width = value.toInt();
				}
				else if ( name == "h")
				{
					stLayer.height = value.toInt();
				}
				else if ( name == "BackPixmapFlag")
				{
					stLayer.backPixmapFlag = value.toInt();
				}
				else if ( name == "BackPixmapName")
				{
					stLayer.backPixmapName = value;
				}
				else if ( name == "bgc")
				{
					QStringList lstLc = value.split(',');
					QColor color = QColor::fromRgb(lstLc[0].toInt(),lstLc[1].toInt(),lstLc[2].toInt());
					stLayer.backColor = color;
				}
				else if ( name == "show")
				{
					stLayer.show = value.toInt();
				}
			}

			// 通过xml节点去串行化文件，也可以通过一次性读入内存，然后在内存中去创建图元
			// 后者的的好处在于将创建和读取分离，两者没有必然的联系
			for (xml_node<>* itemNode = graphLayerNode->first_node(); itemNode; itemNode = itemNode->next_sibling())
			{
				QString strItemName = itemNode->name();
				{
					// 此处可以获得基本类型元对象
					QGraphicsItem* pTempItem = getItem(strItemName);
					CGraphicsItemBase* pTempBase = dynamic_cast<CGraphicsItemBase*>(pTempItem);
					if (pTempBase)
					{
						QGraphicsItem* pCloneItem = pTempBase->clone();
						pCloneItem->setParentItem(parentItem);
						CGraphicsItemBase* pCloneBase = dynamic_cast<CGraphicsItemBase*>(pCloneItem);
						if (pCloneBase)
						{
							GSerialize* pSerial = dynamic_cast<GSerialize*>(pCloneItem);
							pSerial->deserialize(itemNode);
							pCloneBase->init();
							pCloneBase->draw();
						}
					}
				}		
			}
		}
	}
	
	return true;
}


QString createItemByFile(const QString& strFile)
{
	CGraphicsGroupItem* pItem = new CGraphicsGroupItem;
	QString strID;
	pItem->loadItem(strFile,strID);
	CItemFactory::instance()->addItems(strID,pItem);

	return strFile;
}

void itemReduce(QString& result,const QString& str)
{
}

QList<SElecItemInfo> CItemFactory::loadElement(const QString& strDir)
{
	QList<SElecItemInfo> lstItems;

	QStringList lstFiles = getFileRecusive(strDir,QStringList() <<"g");
	if (0)
	{
		foreach(QString fileName,lstFiles)
		{
			createItemByFile(fileName);
		}
	}
	else
	{
		QFuture<void> future = QtConcurrent::mappedReduced(lstFiles.begin(),lstFiles.end(),createItemByFile,itemReduce);
		future.waitForFinished();
	}
	
	return lstItems;
}

void CItemFactory::loadBay(const QString& strDir)
{
	QStringList lstFiles = getFileRecusive(strDir,QStringList() <<"g");
	
	foreach(QString fileName,lstFiles)
	{
		CGraphicsComponent* pItem = new CGraphicsComponent(NULL);
		QString strID;
		SLayerInfo info;
		pItem->loadItem(fileName,strID);
		CItemFactory::instance()->addItems(strID,pItem);
	}
}

//QVector<SData_Struct> vecDatas;
//readData(strFile,vecDatas);
void CItemFactory::readData(const QString& strFile1,QVector<SData_Struct>& vecDatas)
{
	QString strFile = strFile1;
	strFile.append(".data");
	QFile file(strFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return ;
	
	vecDatas.clear();
	QString line;
	bool bStart = false;
	QTextStream dataContent(&file);
	while(!dataContent.atEnd())
	{
		line = dataContent.readLine().simplified();

		if (bStart)
		{
			QStringList strList = line.split(QRegExp("\\s+"));
			if (strList.size() >= 5)
			{
				SData_Struct data;
				data.appID = strList[0].toULongLong();
				data.keyID = strList[1].toULongLong();
				data.terminalID = strList[2].toInt();
				data.nodeID = strList[3].toInt();
				data.objID = strList[4].toULongLong();
				
				vecDatas.append(data);
			}
			continue;
		}
		
		if (line.contains(QObject::tr("应用号")))
		{
			bStart = true;
		}
	}
	file.close();
}

QGraphicsItem* CItemFactory::getItem(const QString& itemName)
{
	QMutexLocker locker(&m_ItemMutex);
	std::map<QString,QGraphicsItem*>::iterator iter = m_ItemMap.find(itemName.toLower());
	if(iter != m_ItemMap.end())
	{
		return iter->second;
	}
	return NULL;
}

void CItemFactory::addItems(QString strID,QGraphicsItem* pItem)
{
	QMutexLocker locker(&m_ItemMutex);
	m_ItemMap.insert(std::make_pair(strID.toLower(),pItem));
}

void CItemFactory::addItems(std::map<QString,QGraphicsItem*> itemMap)
{
	QMutexLocker locker(&m_ItemMutex);
	m_ItemMap.insert(itemMap.begin(),itemMap.end());
}

void CItemFactory::removeItems(std::map<QString,QGraphicsItem*> itemMap)
{
	QMutexLocker locker(&m_ItemMutex);
	std::map<QString,QGraphicsItem*>::iterator iter = itemMap.begin();
	for (;iter != itemMap.end() ;iter++)
	{
		std::map<QString,QGraphicsItem*>::iterator it = m_ItemMap.find(iter->first.toLower());
		if (it != m_ItemMap.end())
		{
			delete it->second;
			m_ItemMap.erase(it);
		}
	}
}

void CItemFactory::modifyItems(std::map<QString,QGraphicsItem*> itemMap)
{
	QMutexLocker locker(&m_ItemMutex);
	std::map<QString,QGraphicsItem*>::iterator iter = itemMap.begin();
	for (;iter != itemMap.end() ;iter++)
	{
		std::map<QString,QGraphicsItem*>::iterator it = m_ItemMap.find(iter->first.toLower());
		if (it != m_ItemMap.end())
		{
			delete it->second;
			it->second = iter->second;
		}
	}
}

void CItemFactory::destroy()
{
	QMutexLocker locker(&m_ItemMutex);
	std::map<QString,QGraphicsItem*>::iterator iter = m_ItemMap.begin();
	while(iter != m_ItemMap.end())
	{
		delete iter->second;
		iter++;
	}
	m_ItemMap.clear();
}

void CItemFactory::createBasicItem() 
{
	// 基础图元
	m_ItemMap.insert(std::make_pair(QString("Image").toLower(),			new CImage));
	m_ItemMap.insert(std::make_pair(QString("line").toLower(),			new CGraphicsLineItem));
	m_ItemMap.insert(std::make_pair(QString("rect").toLower(),			new CGraphicsRectItem));
	m_ItemMap.insert(std::make_pair(QString("circle").toLower(),		new CGraphicsCircleItem));
	m_ItemMap.insert(std::make_pair(QString("pin").toLower(),			new CGraphicsPinItem));
	m_ItemMap.insert(std::make_pair(QString("ellipse").toLower(),		new CGraphicsEllipseItem));
	m_ItemMap.insert(std::make_pair(QString("polygon").toLower(),		new CGraphicsPolygonItem));
	m_ItemMap.insert(std::make_pair(QString("handgon").toLower(),		new CGraphicsHandgonItem));
	m_ItemMap.insert(std::make_pair(QString("triangle").toLower(),		new CGraphicsTriangleItem));
	m_ItemMap.insert(std::make_pair(QString("diamond").toLower(),		new CGraphicsDiamondItem));
	m_ItemMap.insert(std::make_pair(QString("polyline").toLower(),		new CGraphicsPolylineItem));
	m_ItemMap.insert(std::make_pair(QString("handline").toLower(),		new CGraphicsHandlineItem));
	m_ItemMap.insert(std::make_pair(QString("circlearc").toLower(),		new CGraphicsCircleArcItem));
	m_ItemMap.insert(std::make_pair(QString("ellipsearc").toLower(),	new CGraphicsEllipseArcItem));
	m_ItemMap.insert(std::make_pair(QString("roundrect").toLower(),		new CGraphicsRoundRectItem));

	// 电力图元
	m_ItemMap.insert(std::make_pair(QString("ACLine").toLower(),		 new CACLine()));
	m_ItemMap.insert(std::make_pair(QString("ACLineEnd").toLower(),		 new CACLineEnd));
	m_ItemMap.insert(std::make_pair(QString("Bar").toLower(),			 new CBar));
	m_ItemMap.insert(std::make_pair(QString("Bus").toLower(),			 new CBus));
	m_ItemMap.insert(std::make_pair(QString("CBreaker").toLower(),		 new CCBreaker));
	m_ItemMap.insert(std::make_pair(QString("ConnectLine").toLower(),	 new CConnectLine));
	m_ItemMap.insert(std::make_pair(QString("DText").toLower(),			 new CDText));
	m_ItemMap.insert(std::make_pair(QString("Poke").toLower(),			 new CPoke));
	m_ItemMap.insert(std::make_pair(QString("Sensitive").toLower(),		 new CSensitive));
	m_ItemMap.insert(std::make_pair(QString("Text").toLower(),			 new CText));
	m_ItemMap.insert(std::make_pair(QString("Transformer2").toLower(),	 new CTransformer2));
	m_ItemMap.insert(std::make_pair(QString("Transformer3").toLower(),	 new CTransformer3));
	m_ItemMap.insert(std::make_pair(QString("Disconnector").toLower(),	 new CDisconnector));
	m_ItemMap.insert(std::make_pair(QString("Reactor_P").toLower(),		 new CReactor_P));
	m_ItemMap.insert(std::make_pair(QString("Capacitor_P").toLower(),	 new CCapacitor_P));
	m_ItemMap.insert(std::make_pair(QString("Generator").toLower(),		 new CGenerator));
	m_ItemMap.insert(std::make_pair(QString("GroundDisconnector").toLower(),new CGroundDisconnector));

	// 间隔
	m_ItemMap.insert(std::make_pair(QString("Bay").toLower(),new CBay));

	// 综合图元
	m_ItemMap.insert(std::make_pair(QString("Clock").toLower(),			 new CClock));
}

