
#ifndef PLUGIN_BASE_H
#define PLUGIN_BASE_H

#include <QString>
#include <QIcon>
#include <QObject>

#include "macro.h"

enum EPluginType
{
	eApplicationPlugin,
	eContextMenuPlugin,
	eToolTipPlugin,
	eActionPlugin,
	eProtocalPlugin
};

struct SPluginInfo
{
	QString		pluginName;
	QString		menuName;
	QString		description;
	QIcon		icon;
	QObject*	object;
	EPluginType eType;
};

class IDataConfig
{
public:

	virtual void setParentWindow(QWidget* pParentWindow) 
	{
		m_Parent = pParentWindow;
	}

	virtual void setDataPointer(const QMap<int,void*>& pointerMap)
	{
		QMapIterator<int,void*> iter(pointerMap);
		while (iter.hasNext())
		{
			iter.next();
			m_DataPointer[iter.key()] = iter.value();
		}
	}	

protected:

	QWidget*		m_Parent;

	QMap<int,void*>	m_DataPointer;

};

class IPluginBase : public IDataConfig
{
public:

	virtual SPluginInfo getPluginInfo() = 0;

	virtual void init() = 0;

	virtual void destroy() = 0;

};

#endif