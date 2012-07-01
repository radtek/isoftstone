
#ifndef  LOGO_BUTTON_H
#define  LOGO_BUTTON_H

#include "contextmenu.h"
#include "extitem.h"
#include <QGraphicsView>

class EXPORT_EXTITEM CLogoButton :  public QGraphicsObject
{
	Q_OBJECT
public:

	CLogoButton(const QPixmap &pix,const QString& txt,QGraphicsItem* parent = NULL);
	~CLogoButton();

	void setParam(QMenu* pMenu,QGraphicsView* pView);
	virtual void exec(const QPointF& pos);
	void setTransform2(qreal scale,qreal rotate);
	void hideMenu();
	CContextMenu* getContextMenu();
	void setIndex(int width,int index);

signals:
	void onHoverEntered(bool);
	void onHoverLeaved();

protected:

	QRectF boundingRect() const;
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

	void mousePressEvent(QGraphicsSceneMouseEvent *);

	virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:

	QPixmap					m_logoPixmap;
	bool					m_bShowed;
	bool					m_bViewShowed;
	int						m_index;
	QGraphicsView*			m_view;
	int						m_toolWidth;

	CContextMenu*			m_logoMenu;

};



#endif