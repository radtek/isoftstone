#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H

#include <QtGui>

#include "menumanager.h"
#include "interface.h"
#include "toolbaritem.h"
#include "contextmenu.h"

class CGraphicsScene : public QGraphicsScene
{
	Q_OBJECT
public:

	CGraphicsScene(QObject *parent = 0);
	~CGraphicsScene();

	void drawBoundLine(bool bLine);
	bool draw(const QString& fileName);
	bool drawElement(const QString& fileName);
	bool drawBay(const QString& fileName);
	QString currentFile();

	// 工具栏相关操作
	void setToolbar(CItemToolBar* pBar);
	void addContextMenu(CContextMenu* pMenu);
	void clearContextMenu();
	void hideContextMenu();
	void hideItemBar();
	void setScaleFactor(qreal xfactor,qreal yfactor);

protected:

	virtual void customEvent(QEvent* event);
	virtual void timerEvent(QTimerEvent* event);
	virtual void keyPressEvent ( QKeyEvent * keyEvent );
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
	virtual void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	virtual void contextMenuEvent( QGraphicsSceneContextMenuEvent * event  );

private slots:

	void updateValue();

private:

	void initScene();
	void showPage(const int &iPage);
	
	void collectItemInfo();

private:
	QPixmap*						m_pbkPixmap;
	QGraphicsRectItem *				m_outlineItem;
	QString							m_currentFile;
	QTimer*							m_updateTimer;

	QMultiHash<quint64,CDynamicItemBase*>	m_dynamicMap;	/* 动态数据更新列表 */
	QMultiHash<quint64,QGraphicsItem*>	m_itemMap;			/* 类型对应列表 */

	CMenuManager*					m_menuManager;

	CContextMenu*	m_contextMenu;
	CItemToolBar*	m_itemBar;
	QList<CContextMenu*>	m_lstContextMenu;
	qreal			m_xFactor;
	qreal			m_yFactor;
};

#endif // MYGRAPHICSSCENE_H
