
#ifndef TOOLBAR_ITEM_H
#define TOOLBAR_ITEM_H

#include "menuitem.h"
#include "contextmenu.h"
#include "extitem.h"

#include <QGraphicsView>

class EXPORT_EXTITEM CItemToolBar : public QGraphicsObject
{
	Q_OBJECT
public:

	CItemToolBar(QGraphicsItem* parent = NULL);
	~CItemToolBar();

	void setRadius(int radius);
	void setActions(const QList<QAction*>& lstAction);

	void	show();
	void	hide();
	bool	isShow();

	EBerthPostion			getBerthPostion();
	QList<CContextMenu*>	getContextMenu();

	void setItemVisible(bool bShow);
	void setMenuLock(bool bLock);
	void setParam(QMenu* pMenu,QGraphicsView* pView);

	void fitItemBar();

	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	
Q_SIGNALS:

	void signalShow();
	void signalHide();

private slots:

	void onHideExit();
	void onClickedSlot(bool);
	void onHoverEnterSlot(bool);
	void onHoverLeaveSlot();
	void setBarLock(bool bLock);

protected:

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
	virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
	virtual QRectF boundingRect() const;

private:

	CMenuItem* createItem(QAction* pAction);
	void addToolItem();
	void exec();

protected:

	void createToolItem(const QList<QAction*>& lstAction);
	void resetAnimationGroup();

	void createStateGroup();
	void createScaleGroup();
	void createToolBarAnimation();
	void resetToolBarPos();
	void scaleGraphicsItem(QGraphicsObject* gObj,qreal scale);

private:

	QParallelAnimationGroup* m_mouseGroup;
	QParallelAnimationGroup* m_scaleGroup;
	QPropertyAnimation*		 m_toolbarAnimation;
	bool					 m_bToolShow;
	bool					 m_bHoverUsed;

	EBerthPostion	m_berthPos;
	QStateMachine	m_stateMachine;
	QState *		m_rootState;
	QState *		m_showState;
	QState *		m_hideState;
	QList<CContextMenu*>	m_lstMenus;		/* 菜单项对象 */
	QList<QAction*>			m_lstAction;	/* 菜单项*/
	QList<QGraphicsObject*>	m_lstObjects;	/* 所有工具项对象 */

	bool			m_bMenuLock;
	bool			m_bBarLock;
	bool			m_bShowed;
	QAction*		m_action_BarLock;
	int				m_radius;
	QGraphicsView*	m_view;

};

#endif