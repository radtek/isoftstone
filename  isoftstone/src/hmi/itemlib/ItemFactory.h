#ifndef CLASS_FACTORY_H
#define CLASS_FACTORY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QString>

#include <map>
#include <QMutex>
#include <QMutexLocker>

#include "itemlib.h"
#include "struct.h"


struct SElecItemInfo
{
	QString m_fileName;
	QString m_ID;
	QGraphicsItem* m_Item;
};

class EXPORT_ITEMLIB CItemFactory
{
public:

	static CItemFactory* instance();

	CItemFactory();

	bool draw(QGraphicsScene* pScene,const QString& strFile);

	bool drawBay(QGraphicsItem* parentItem,const QString& strFile,QString& strID,SLayerInfo& stLayer);

	QList<SElecItemInfo> loadElement(const QString& strDir);

	void loadBay(const QString& strDir);

	void readData(const QString& strFile,QVector<SData_Struct>& vecDatas);

	QGraphicsItem* getItem(const QString& itemName);
	
	void addItems(QString strID,QGraphicsItem* pItem);

	void addItems(std::map<QString,QGraphicsItem*> itemMap);

	void removeItems(std::map<QString,QGraphicsItem*> itemMap);

	void modifyItems(std::map<QString,QGraphicsItem*> itemMap);

	void destroy();

protected:

	void createBasicItem() ;

private:

	QMutex						 m_ItemMutex;

	std::map<QString,QGraphicsItem*> m_ItemMap;

};

#endif
