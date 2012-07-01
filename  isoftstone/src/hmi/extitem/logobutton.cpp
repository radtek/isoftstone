
#include "logobutton.h"


CLogoButton::CLogoButton(const QPixmap &pix,const QString& txt,QGraphicsItem* parent): QGraphicsObject(parent),m_logoPixmap(pix)
{
	setCacheMode(DeviceCoordinateCache);
	setAcceptHoverEvents(true);

	setZValue(1000);

	setToolTip(txt);
	m_bShowed = false;
	m_bViewShowed = false;
	m_index = 0;

	m_logoMenu = new CContextMenu(tr("工具栏菜单"));
}

CLogoButton::~CLogoButton()
{
	//delete m_logoMenu;
}

CContextMenu* CLogoButton::getContextMenu()
{
	return m_logoMenu;
}

QRectF CLogoButton::boundingRect() const
{
	return QRectF(0,0,ITEM_WIDTH ,ITEM_WIDTH );
}

void CLogoButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	painter->save();
	bool down = option->state & QStyle::State_Sunken;
	QRectF r = boundingRect();
	painter->setPen(QColor(2471412));
	QColor bkcolor = QColor(4802889);
	bkcolor.setAlpha(200);

	painter->drawPixmap(boundingRect().toRect(), m_logoPixmap);
	painter->restore();
}

void CLogoButton::hideMenu()
{
	m_bViewShowed = false;
	m_bShowed = false;
}

void CLogoButton::setIndex(int width,int index)
{
	m_toolWidth = width;
	m_index = index;
}

void CLogoButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
	m_bViewShowed = !m_bViewShowed;
	m_bShowed = !m_bShowed;

	if (m_bShowed && m_bViewShowed)
	{
		exec(event->screenPos());
	}
	else
	{
		m_logoMenu->deleteAllItem();
	}
}

void CLogoButton::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	emit onHoverEntered(true);
}

void CLogoButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	emit onHoverLeaved();
}

void CLogoButton::setTransform2(qreal scale,qreal rotate)
{
	QTransform transform;
	transform.translate(boundingRect().width()/2,boundingRect().height()/2);
	//transform.scale(scale,scale);
	transform.rotate(rotate,Qt::XAxis);
	transform.translate(-boundingRect().width()/2,-boundingRect().height()/2);
	setTransform(transform);
	update();
}


void CLogoButton::setParam(QMenu* pMenu,QGraphicsView* pView)
{
	m_view = pView;
	m_logoMenu->setParam(pMenu,m_view->scene());
}

void CLogoButton::exec(const QPointF& pos)
{
	// 修改logo菜单弹出位置
	//m_Pos = QPoint(pos().x() - 20,pos().y() + boundingRect().height() + 20);

	QTransform t = m_view->transform();
	qreal m11 = t.m11();
	qreal m22 = t.m22();

	// 居中设置
	int viewWidth = m_view->viewport()->width();
	int width = boundingRect().width();
	int height = boundingRect().height();
	int x = (viewWidth - m_toolWidth)/2 + m_index*(width+5);
	int y = height + 10;
	QPoint barPos(x,y);
	//当scene缩放时，保持位置不变。
	QPointF cpos = m_view->mapToScene(barPos);
	m_logoMenu->exec(cpos);
}

