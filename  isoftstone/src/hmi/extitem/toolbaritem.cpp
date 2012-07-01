
#include "toolbaritem.h"
#include "logobutton.h"


// 工具栏设置
CItemToolBar::CItemToolBar(QGraphicsItem* parent): QGraphicsObject(parent)
{
	setAcceptsHoverEvents(true);
	setAcceptHoverEvents(true);
	setFlag(QGraphicsItem::ItemIsFocusable);

	m_berthPos = eScreenTop;
	m_bToolShow = false;
	m_bHoverUsed = true;
	m_bMenuLock = false;
	m_bBarLock = false;
	m_bShowed = false;

	m_radius = 10;

	m_mouseGroup = new QParallelAnimationGroup;
	m_scaleGroup = new QParallelAnimationGroup;
	connect(m_mouseGroup,SIGNAL(finished()),this,SLOT(onHideExit()));

	m_rootState = new QState;
	m_showState = new QState(m_rootState);
	m_hideState = new QState(m_rootState);
	m_stateMachine.addState(m_rootState);
	m_stateMachine.setInitialState(m_rootState);
	m_rootState->setInitialState(m_hideState);
	m_stateMachine.start();
	setItemVisible(false);

	bool bret = connect(m_hideState,SIGNAL(finished()),this,SLOT(onHideExit()));
	bret = connect(m_hideState,SIGNAL(exited()),this,SLOT(onHideExit()));

	m_action_BarLock = new QAction(QIcon(":images/dingzi.png"),QObject::tr("固定工具栏"),this);
	QObject::connect(m_action_BarLock,SIGNAL(triggered(bool)),this,SLOT(setBarLock(bool)));
	
}

CItemToolBar::~CItemToolBar()
{
	m_mouseGroup->stop();
	m_mouseGroup->clear();
	m_stateMachine.removeDefaultAnimation(m_mouseGroup);
	m_stateMachine.removeState(m_rootState);
	m_stateMachine.stop();
}

void CItemToolBar::setRadius(int radius)
{ 
	m_radius = radius ;
}

void CItemToolBar::setParam(QMenu* pMenu,QGraphicsView* pView)
{
	m_view = pView;
	setActions(pMenu->actions());
}

void CItemToolBar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	painter->save();
	QColor color(4802889);
	color.setAlpha(200);
	QBrush brush(color);
	painter->setBrush(brush);

	painter->drawRoundedRect(boundingRect(),m_radius,m_radius);
	painter->restore();
}

QRectF CItemToolBar::boundingRect() const
{
	return QRectF(0,0,m_lstAction.count()*(ITEM_WIDTH + 5) + 10,ITEM_HEIGHT + 10);
}

void CItemToolBar::onHideExit()
{
	//setItemVisible(m_bToolShow);
	QGraphicsItem::hide();
	m_bHoverUsed = m_bToolShow;
}

void CItemToolBar::setActions(const QList<QAction*>& lstAction)
{
	m_lstAction = lstAction;
	m_lstAction.append(m_action_BarLock);

	createToolItem(m_lstAction);
	addToolItem();
	createToolBarAnimation();

	//createScaleGroup();
	//createStateGroup();

	//setItemVisible(false);
}

void CItemToolBar::addToolItem()
{
	int i = 0;
	foreach(QGraphicsItem* item,m_lstObjects)
	{
		item->setPos(5 + (ITEM_WIDTH + 5 )*i ,5);
		i++;
	}
}

void CItemToolBar::fitItemBar()
{
	QTransform t = m_view->transform();
	qreal m11 = t.m11();
	qreal m22 = t.m22();

	// 居中设置
	int viewWidth = m_view->viewport()->width();
	int width = boundingRect().width();
	int x = (viewWidth - width)/2;
	int y = 0;
	QPoint barPos(x,y);
	//当scene缩放时，保持位置不变。
	QPointF pos = m_view->mapToScene(barPos);
	setPos(pos);
	if (!m_bToolShow)
	{
		QGraphicsItem::hide();
	}
	//当scene缩放时，保持原来大小。
	QTransform  t2 = transform();
	t2.reset();
	t2.scale((qreal)1/m11,(qreal)1/m22);
	setTransform(t2);

	resetToolBarPos();

	update();
}

QList<CContextMenu*> CItemToolBar::getContextMenu()
{
	return m_lstMenus;
}

void CItemToolBar::mousePressEvent(QGraphicsSceneMouseEvent *)
{
	m_bShowed = !m_bShowed;
	setItemVisible(m_bShowed);
	//exec();
}

void CItemToolBar::exec()
{
// 	m_Pos = QPoint(scenePos().x() + boundingRect().width() + 10,scenePos().y() );
// 	resetAnimationGroup();
// 
// 	m_AnimationGroup->start();
}

void CItemToolBar::createToolItem(const QList<QAction*>& lstAction)
{
	int index = 0;
	foreach(QAction* act,lstAction)
	{
		if (!act || act->isSeparator())
		{
			continue;
		}
		if (act->menu())
		{
			QPixmap pix = act->icon().pixmap(ITEM_WIDTH,ITEM_HEIGHT);
			pix = pix.scaledToHeight(ITEM_HEIGHT,Qt::SmoothTransformation);
			pix = pix.scaledToWidth(ITEM_WIDTH,Qt::SmoothTransformation);

			CLogoButton* logoItem = new CLogoButton(pix,act->toolTip(),this);
			logoItem->setParam(act->menu(),m_view);
			logoItem->setIndex(boundingRect().width(),index);

			/* 将综合菜单项单独处理，为了在屏幕点击时自动消失 */
			m_lstMenus.append(logoItem->getContextMenu());
			m_lstObjects.append(logoItem);

			connect(logoItem,SIGNAL(onHoverEntered(bool)),this,SLOT(onHoverEnterSlot(bool)));
			connect(logoItem,SIGNAL(onHoverLeaved()),this,SLOT(onHoverLeaveSlot()));
		}
		else
		{
			CMenuItem* item = createItem(act);
			item->setZValue(1000);
			m_lstObjects.append(item);

			connect(item,SIGNAL(onClicked(bool)),this,SLOT(onClickedSlot(bool)));
			connect(item,SIGNAL(onHoverEntered(bool)),this,SLOT(onHoverEnterSlot(bool)));
			connect(item,SIGNAL(onHoverLeaved()),this,SLOT(onHoverLeaveSlot()));
		}
		index++;
	}
}

void CItemToolBar::scaleGraphicsItem(QGraphicsObject* gObj,qreal scale)
{
	QTransform transform;
	transform.translate(gObj->boundingRect().width()/2,gObj->boundingRect().height()/2);
	qreal qs = scale;
	transform.scale(qs,qs);
	transform.translate(-1*gObj->boundingRect().width()/2,-1*gObj->boundingRect().height()/2);
	gObj->setTransform(transform);
}


void CItemToolBar::onClickedSlot(bool)
{
	for (int i = 0 ; i < m_lstMenus.count() ; i++)
	{
		m_lstMenus[i]->deleteAllItem();
	}
}

void CItemToolBar::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	return QGraphicsItem::hoverEnterEvent(event);
}

void CItemToolBar::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
	return QGraphicsItem::hoverLeaveEvent(event);
}

void CItemToolBar::onHoverEnterSlot(bool)
{
	QObject* obj = sender();
	int u = m_lstObjects.indexOf(dynamic_cast<QGraphicsObject*>(obj));
	QPointF pos(0,0);
	if (u > -1)
	{
		pos = m_lstObjects[u]->pos();

		// 缩放倍数
		scaleGraphicsItem(m_lstObjects[u],1.25);
	}
}

void CItemToolBar::onHoverLeaveSlot()
{
	QObject* obj = sender();
	int u = m_lstObjects.indexOf(dynamic_cast<QGraphicsObject*>(obj));
	if (u > -1)
	{
		scaleGraphicsItem(m_lstObjects[u],1);
	}
}

void CItemToolBar::setItemVisible(bool bShow)
{
	QGraphicsItem::setVisible(bShow);
	foreach (QGraphicsItem* pItem,m_lstObjects)
	{
		pItem->setVisible(bShow);	
	}
}

CMenuItem* CItemToolBar::createItem(QAction* pAction)
{
	QIcon icon = pAction->icon();
	int height = ITEM_WIDTH;
	int width = ITEM_HEIGHT;
	QPixmap pix = icon.pixmap(width,height);
	pix = pix.scaledToHeight(height,Qt::SmoothTransformation);
	pix = pix.scaledToWidth(width,Qt::SmoothTransformation);

	CMenuItem* item = new CMenuItem(pix,pAction,this);
	item->setStyle(false);

	return item;
}

void CItemToolBar::setMenuLock(bool bLock)
{
	m_bMenuLock = bLock;
}

void CItemToolBar::setBarLock(bool bLock)
{
	m_bBarLock = !m_bBarLock;
}

void CItemToolBar::show()
{
	if (m_bBarLock)
	{
		return;
	}
	QGraphicsObject::show();
	if (!m_bToolShow)
	{
		emit signalShow();
		m_bToolShow = true;
	}
}

void CItemToolBar::hide()
{
	if (!m_bBarLock)
	{
		if (!m_bMenuLock)
		{
			if (m_bToolShow)
			{
				m_bToolShow = false;
				emit signalHide();
			}
		}
	}
}

bool CItemToolBar::isShow()
{
	return m_bToolShow;
}

EBerthPostion CItemToolBar::getBerthPostion()
{
	return m_berthPos;
}

void CItemToolBar::createStateGroup()
{
	m_mouseGroup->clear();
	for (int i = 0; i < m_lstObjects.count(); i++) 
	{
		QGraphicsObject* pItem = dynamic_cast<QGraphicsObject*>(m_lstObjects[i]);
		QPropertyAnimation *anim = new QPropertyAnimation(pItem, "pos");
		anim->setDuration(200);
		anim->setEasingCurve(QEasingCurve::Linear);
		m_mouseGroup->addAnimation(anim);
	}

	QRectF sceneRect /*= m_Scene->sceneRect()*/;
	for (int i = 0; i < m_lstObjects.count(); i++) 
	{
		QGraphicsObject* pItem = dynamic_cast<QGraphicsObject*>(m_lstObjects[i]);


		// 间隔 75-60 = 15
		int rw = 75;
		switch(m_berthPos)
		{
		case eScreenLeft:
			{
				m_hideState->assignProperty(pItem,"pos",QPoint(-65  ,sceneRect.height()/3 + i*rw));
				m_showState->assignProperty(pItem,"pos",QPoint(0,sceneRect.height()/3 + i*rw));
			}
			break;
		case eScreenRight:
			{
				m_hideState->assignProperty(pItem,"pos",QPoint(sceneRect.width() ,sceneRect.height()/3+ i*rw));
				m_showState->assignProperty(pItem,"pos",QPoint(sceneRect.width() - 60,sceneRect.height()/3 + i*rw));
			}
			break;
		case eScreenTop:
			{
				// 左上角
				m_hideState->assignProperty(pItem,"pos",QPoint(sceneRect.width()/3 - 100 + i*rw,-65));
				m_showState->assignProperty(pItem,"pos",QPoint(sceneRect.width()/3 - 100 + i*rw, 5));
			}
			break;
		case eScreenBottom:
		default:
			{
				// 修改工具栏图标的开始和结束位置
				m_hideState->assignProperty(pItem,"pos",QPoint(sceneRect.width()/3 + i*rw,sceneRect.height()));
				m_showState->assignProperty(pItem,"pos",QPoint(sceneRect.width()/3 + i*rw,sceneRect.height() - 60));
			}
			break;
		}
	}

	QSignalTransition *trans = m_rootState->addTransition(this, SIGNAL(signalShow()), m_showState);
	trans->addAnimation(m_mouseGroup);

	trans = m_rootState->addTransition(this, SIGNAL(signalHide()), m_hideState);
	trans->addAnimation(m_mouseGroup);
}


void CItemToolBar::createScaleGroup()
{
	m_scaleGroup->clear();
	QRectF sceneRect ; /*m_Scene->sceneRect()*/;
	for (int i = 0; i < m_lstObjects.count(); i++) 
	{
		QObject* pItem = m_lstObjects[i];
		QPropertyAnimation *anim = new QPropertyAnimation(pItem, "pos");
		anim->setDuration(200 + i * 25);
		anim->setEasingCurve(QEasingCurve::Linear);

		switch(m_berthPos)
		{
		case eScreenTop:
			{
				anim->setStartValue(QPoint(sceneRect.width()/3 + i*75, 0));
			}
			break;
		case eScreenBottom:
		default:
			{
				// 修改工具栏图标的开始和结束位置
				anim->setStartValue(QPoint(sceneRect.width()/3 + i*75,sceneRect.height() - 60));
			}
		}
		m_scaleGroup->addAnimation(anim);
	}
}

void CItemToolBar::createToolBarAnimation()
{
	QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
	anim->setDuration(200);
	anim->setEasingCurve(QEasingCurve::Linear);

	QSignalTransition *trans = m_rootState->addTransition(this, SIGNAL(signalShow()), m_showState);
	trans->addAnimation(anim);

	trans = m_rootState->addTransition(this, SIGNAL(signalHide()), m_hideState);
	trans->addAnimation(anim);
}

void CItemToolBar::resetToolBarPos()
{
	QTransform t = m_view->transform();
	qreal m11 = t.m11();
	qreal m22 = t.m22();

	// 居中设置
	int viewWidth = m_view->viewport()->width();
	int width = boundingRect().width();
	int height = boundingRect().height();
	//当scene缩放时，保持位置不变。
	QPointF startPos = m_view->mapToScene((viewWidth - width)/2,-1*height);
	QPointF endPos = m_view->mapToScene((viewWidth - width)/2,0);

	m_hideState->assignProperty(this,"pos",startPos);
	m_showState->assignProperty(this,"pos",endPos);
}

void CItemToolBar::resetAnimationGroup()
{
// 	QAnimationGroup* group = m_AnimationGroup;
// 	for (int i = 0 ; i < group->animationCount() ; i++)
// 	{
// 		QAbstractAnimation* anim1 = group->animationAt(i);
// 		QPropertyAnimation* anim = dynamic_cast<QPropertyAnimation*>(anim1);
// 		if (anim)
// 		{
// 			anim->setStartValue(QPoint(m_Pos.x(),m_Pos.y()));
// 			QPoint finalPoint = QPoint(m_Pos.x() + i*65 ,m_Pos.y() );
// 			anim->setEndValue(finalPoint);
// 		}
// 	}
}
