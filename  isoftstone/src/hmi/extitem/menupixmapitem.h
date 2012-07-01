#ifndef MENUITEM_H
#define MENUITEM_H

#include "extitem.h"

class EXPORT_EXTITEM CMenuPixmapItem : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    enum {DEFAULT_SIZE = 80};

    CMenuPixmapItem( QObject *parent = 0);

protected:

    virtual void hoverEnterEvent ( QGraphicsSceneHoverEvent * event );
    virtual void hoverLeaveEvent ( QGraphicsSceneHoverEvent * event );
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QPixmap m_Pixmap;
    QStateMachine   *m_pStateMachine;
    QState          *m_pNormalScale;
    QState          *m_pLargeScale;
    QParallelAnimationGroup *m_pAniGroup;
    QPropertyAnimation *m_pAniScale;
    QPropertyAnimation *m_pAniDisappear;
    QPropertyAnimation *m_pAniShow;
    bool                m_bPressedUp;
	int					m_iOrderCount;
signals:

    void pressedUp();
    void pressedDown();
    void orderCountChanged(int);
};

#endif // MENUITEM_H
