
#pragma once

#include <QString>
#include <QMap>
#include <QList>
#include <QTextStream>

class CProjectNode
{
public:

	CProjectNode(CProjectNode* parent = NULL);

	CProjectNode* getParent();
	void setFolderGuid(QString folderguid);
	void setItemName(QString itemname);
	QString getItemName();
	void setItemGuid(QString itemguid);
	QString getItemGuid();
	void addItem(QString key,QString value);
	void addChild(CProjectNode* child);
	QList<CProjectNode*> getChildList();
	void write2File(QTextStream& stream);

private:

	CProjectNode* m_parentNode;
	QString m_folderGuid;
	QString m_itemName;
	QString m_itemGuid;
	QList<CProjectNode*> m_childList;
	QMap<QString,QString> m_itemMap;
};