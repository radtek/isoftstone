
#ifndef MENU_LOADER_H
#define MENU_LOADER_H

#include <QMap>
#include <QObject>
#include <QMenu>
#include <QAction>
#include <QList>

enum EContextMenuType
{
	eLabelName,
	eSeparator,
	eNormalMenu,
	eSubMenu,
	eOtherMenu
};

struct SMenuInfo
{
	EContextMenuType eMenuType; // 菜单类型
	QString strCode;			// 标示符
	QString strText;			// 显示文本
	int		nCommand;			// 命令号
};

class CMenuLoader
{
public:

	CMenuLoader(QObject* receiver);

	QMenu* getMenu(quint64 appID,int itemType);
	int stringToType(const QString& str);
	void destory();

private:

	void loadMenu();
	void initAppMap();

	void loadMenu(const QString& strFile,const QString& strApp,QMap<QString,QVector<SMenuInfo> >& menuMap);
	QMenu* createMenu(quint64 appID,const QString& group);

private:

	// 第一个key 为应用号，第二个key为图元类型，值为所用的菜单
	QMap<quint64,QMap<int,QString> >	m_RelationMap;

	// 应用中所包含的子菜单
	QMap<quint64,QMap<QString,QVector<SMenuInfo> > >	m_PopupMenuMap;	

	QMap<quint64,QMap<int,QMenu*> >		m_MenuMap;

	QMap<QString,quint64>	m_AppMap;

	QObject* m_Receiver;
};

#endif