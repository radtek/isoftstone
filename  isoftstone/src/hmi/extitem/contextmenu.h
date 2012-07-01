
#ifndef CONTEXT_MENU_H
#define CONTEXT_MENU_H

#include "menuitem.h"
#include "extitem.h"

enum EBerthPostion
{
	eScreenLeft,
	eScreenRight,
	eScreenTop,
	eScreenBottom
};

class EXPORT_EXTITEM CContextMenu : public QGraphicsObject
{
	Q_OBJECT
public:
	CContextMenu(const QString& strName,CContextMenu* parentMenu = NULL,QGraphicsItem* parent = NULL);

	void setParam(QMenu* pMenu,QGraphicsScene* scene);
	void fitInContextMenu();

	virtual void exec(const QPointF& pos);

	virtual void deleteContextItem();
	virtual void hideContextItem();
	void deleteAllItem();

	void setBerthPosition(EBerthPostion berthPos);
	void setScaleFactor(qreal xfactor,qreal yfactor);

protected:

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

public slots:

	void onActionClick(bool);
	void deleteChildMenu(bool bSub);

signals:
		void onHoverEntered(bool);
		void onHoverLeaved();

protected:

	void createContextItem(const QList<QAction*>& lstAction);
	void addContextItem();
	void createAnimationGroup();
	void updateItemFactor();

protected:

	QList<QGraphicsItem*>	m_ContextItems;
	CContextMenu*			m_SubContextMenu;
	CContextMenu*			m_ParentMenu;
	QString					m_MenuName;
	QMenu*					m_ContextMenu;
	QPointF					m_Pos;
	QGraphicsScene*			m_Scene;
	QGraphicsView*	m_view;

	QParallelAnimationGroup*m_AnimationGroup;

	EBerthPostion	m_berthPos;
	qreal			m_xFactor;
	qreal			m_yFactor;
};

#endif