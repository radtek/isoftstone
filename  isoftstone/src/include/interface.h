#ifndef INTERFACE_H
#define INTERFACE_H

#include <QDataStream>
#include <QVariant>
#include <vector>

#include "rapidxml.hpp"
#include "struct.h"
#include "enum.h"

using namespace rapidxml;

class QGraphicsItem;
class QPixmap;


class ISerialize
{
public:

	virtual void serialize(QDataStream& out) const =0;
	virtual void deserialize( QDataStream& out) = 0;
};


class GSerialize
{
public:

	virtual void serialize(xml_node<char>* node) const =0;
	virtual void deserialize(xml_node<char>* node) = 0;
};

class IElementBase
{
public:

	virtual SItemInfo getItemInfo() {return m_itemInfo; };

protected:

	SItemInfo	m_itemInfo;
};

// 动态数据
class CDynamicItemBase : public IElementBase
{
public:

	CDynamicItemBase()
	{
		m_itemInfo.bDynamic = true;
		m_itemInfo.bSingle = true;
	}

	virtual quint64 keyID() { return 0;};

	virtual QVector<quint64> getKeyIDs()
	{
		QVector<quint64> vecKeys;
		vecKeys.push_back(keyID()); 
		return vecKeys; 
	};

	virtual void setValues(const std::vector<quint64>& vecIds,const std::vector<QVariant>& vecValues) 
	{
		Q_UNUSED(vecIds);
		Q_UNUSED(vecValues);
	};

	virtual void setValue(const QVariant& varValue,quint64 keyid)
	{
		Q_UNUSED(varValue);
		Q_UNUSED(keyid);
	};

	virtual void setValue(const QVariant& varValue)
	{
		Q_UNUSED(varValue);
	};

protected:

	std::vector<quint64> m_vecKeyIDs;
};

// 静态数据
class CStaticItemBase : public IElementBase
{
public:

	CStaticItemBase()
	{
		m_itemInfo.bDynamic = false;
	}
};

#endif