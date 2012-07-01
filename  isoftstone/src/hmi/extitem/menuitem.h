
#ifndef MENU_ITEM_H
#define MENU_ITEM_H


#include <QGraphicsTextItem>
#include <QGraphicsWidget>
#include <QParallelAnimationGroup>
#include <QStateMachine>
#include <QSettings>
#include <QPropertyAnimation>
#include <QPainter>
#include <QTimeLine>
#include <QStyleOption>
#include <QGraphicsScene>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QAbstractTransition>
#include <QSignalTransition>
#include <QAction>
#include <QMenu>
#include <QVBoxLayout>
#include <QKeyEvent>
#include <QMenuBar>
#include <QMap>

#define ITEM_WIDTH 50
#define ITEM_HEIGHT 50

#include "extitem.h"

class CContextMenu;
class EXPORT_EXTITEM CMenuItem : public QGraphicsObject
{
	Q_OBJECT
public:
	CMenuItem(const QPixmap &pixmap, QAction* pAction,QGraphicsObject *parent = 0);

	void setBackPixmap(QPixmap& bkPixmap);
	void setItemWidth(int w);
	void setStyle(bool bMenu = true);
	void setTransform2(qreal scale ,qreal rotate = 0);
	void setScaleFactor(qreal xfactor,qreal yfactor);

	QRectF boundingRect() const;
	QAction* getAction();

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

signals:
	void onClicked(bool bSub);
	void onHoverEntered(bool bSub);
	void onHoverLeaved();

protected:

	virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:


private:

	QObject*		m_parentMenu;
	QPixmap			m_pixmap;
	QPixmap			m_bkPixmap;
	QColor			m_bkColor;
	QColor			m_defaultColor;
	QString			m_text;
	QAction*		m_action;
	bool			m_bSubMenu;
	bool			m_bShowed;
	bool			m_bMenu;
	mutable QRectF	m_bkRect;
	qreal			m_factor;
};

#endif