
#include <QtGui>

#include "menupixmapitem.h"


const int INT_DURATION_TIME = 50;
const qreal QREAL_SMALL_SCALE = 1.0;
const qreal QREAL_LARGE_SCALE = 1.5;
int g_iZValue = 0;


CMenuPixmapItem::CMenuPixmapItem(QObject *parent) :QObject(parent),m_bPressedUp(false)
{
    setCacheMode(DeviceCoordinateCache);
    m_Pixmap = QPixmap("").scaled(DEFAULT_SIZE, DEFAULT_SIZE);
    if(m_Pixmap.isNull())
    {
        QMessageBox box;
        box.setText("");
        box.exec();
    }
    setPixmap(m_Pixmap);
    this->setAcceptsHoverEvents(true);
    QString strToolTip = "";
    setToolTip(strToolTip);
    m_iOrderCount = 0;


    m_pStateMachine = new QStateMachine(this);


    m_pLargeScale = new QState(QState::ParallelStates);
    m_pNormalScale = new QState(QState::ParallelStates);
    m_pStateMachine->addState(m_pLargeScale);
    m_pStateMachine->addState(m_pNormalScale);
    m_pNormalScale->assignProperty(this, "scale", 1.0);
    m_pLargeScale->assignProperty(this, "scale", 1.5);

    m_pAniScale = new QPropertyAnimation(this, "scale");
    m_pAniScale->setDuration(INT_DURATION_TIME);
    m_pAniGroup = new QParallelAnimationGroup;
    m_pAniGroup->addAnimation(m_pAniScale);


    QAbstractTransition *pTrans = m_pNormalScale->addTransition(
                this, SIGNAL(pressedUp()), m_pLargeScale);
    pTrans->addAnimation(m_pAniGroup);
    pTrans = m_pLargeScale->addTransition(
                this, SIGNAL(pressedDown()), m_pNormalScale);
    pTrans->addAnimation(m_pAniGroup);

    m_pStateMachine->setInitialState(m_pNormalScale);
    m_pStateMachine->start();
    setTransformOriginPoint(DEFAULT_SIZE/2, DEFAULT_SIZE/2);

}


void CMenuPixmapItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    g_iZValue = this->zValue();
    qDebug() << g_iZValue;
    setZValue(1000);
}

void CMenuPixmapItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    this->setZValue(g_iZValue);
    emit pressedDown();
    m_bPressedUp = false;
}

void CMenuPixmapItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget *)
{
    painter->drawPixmap(0, 0, m_Pixmap);
    QLinearGradient gradient(-3, 0, m_Pixmap.width(), m_Pixmap.height());
    if(option->state & QStyle::State_Sunken)
    {
        gradient.setColorAt(0, Qt::red);
        gradient.setColorAt(1, Qt::darkRed);

    }
    else if(option->state & QStyle::State_MouseOver)
    {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    QPen pen;
    pen.setBrush(gradient);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawRect(0, 0, m_Pixmap.width(), m_Pixmap.height());
    painter->save();
    QFont font(qApp->font());
    font.setPointSize(20);
    painter->setFont(font);
    if(m_iOrderCount != 0)
    {
        pen.setBrush(Qt::red);
        pen.setWidth(2);

        painter->setPen(pen);

    }
    painter->drawText(m_Pixmap.rect(), Qt::AlignBottom | Qt::AlignRight,
                      tr("%1").arg(m_iOrderCount));
    painter->restore();

}

void CMenuPixmapItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	emit orderCountChanged(1);
	update();
	QGraphicsPixmapItem::mouseDoubleClickEvent(event);
}

void CMenuPixmapItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
    {
        if(m_iOrderCount - 1 >= 0)
        {
            m_iOrderCount = m_iOrderCount - 1;
            emit orderCountChanged(-1);
        }
        else
            m_iOrderCount = 0;
        update();
    }
    if(m_bPressedUp == false)
        emit pressedUp();
}

