
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
	EContextMenuType eMenuType; // �˵�����
	QString strCode;			// ��ʾ��
	QString strText;			// ��ʾ�ı�
	int		nCommand;			// �����
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

	// ��һ��key ΪӦ�úţ��ڶ���keyΪͼԪ���ͣ�ֵΪ���õĲ˵�
	QMap<quint64,QMap<int,QString> >	m_RelationMap;

	// Ӧ�������������Ӳ˵�
	QMap<quint64,QMap<QString,QVector<SMenuInfo> > >	m_PopupMenuMap;	

	QMap<quint64,QMap<int,QMenu*> >		m_MenuMap;

	QMap<QString,quint64>	m_AppMap;

	QObject* m_Receiver;
};

#endif