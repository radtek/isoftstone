
#include "contextmenu.h"
#include <QGraphicsView>


CContextMenu::CContextMenu(const QString& strName,CContextMenu* parentMenu,QGraphicsItem* parent):QGraphicsObject(parent),m_ParentMenu(parentMenu),m_MenuName(strName)
{
	m_AnimationGroup = new QParallelAnimationGroup;
	m_SubContextMenu = NULL;
	m_berthPos = eScreenTop;
	m_xFactor = 1;
	m_yFactor = 1;
}

void CContextMenu::setParam(QMenu* pMenu,QGraphicsScene* scene)
{
	if (pMenu)
	{
		m_ContextMenu = pMenu;
	}
	m_Scene = scene;
	m_view = scene->views()[0];
	if (m_ParentMenu == NULL)
	{
		m_Scene->addItem(this);
	}
}

void CContextMenu::fitInContextMenu()
{
	//当scene缩放时，保持原来大小。
	QTransform  t2 = transform();
	t2.reset();
	t2.scale((qreal)1/m_xFactor,(qreal)1/m_yFactor);
	setTransform(t2);
	update();
}

void CContextMenu::setScaleFactor(qreal xfactor,qreal yfactor)
{
	m_xFactor = xfactor;
	m_yFactor = yfactor;
	fitInContextMenu();
}

void CContextMenu::updateItemFactor()
{
	foreach (QGraphicsItem* pItem,m_ContextItems)
	{
		CMenuItem* pMenuItem = dynamic_cast<CMenuItem*>(pItem);
		if (pMenuItem)
		{
			pMenuItem->setScaleFactor(m_xFactor,m_yFactor);
		}
	}
	if (m_SubContextMenu)
	{
		//m_SubContextMenu->setScaleFactor(m_factor);
	}
}

void CContextMenu::exec(const QPointF& pos)
{
	show();

	deleteContextItem();

	createContextItem(m_ContextMenu->actions());
	updateItemFactor();
	//addContextItem();
	createAnimationGroup();
	
	setPos(pos);

	m_AnimationGroup->start();
}


QRectF CContextMenu::boundingRect() const
{
	return QRectF(0,0,150,25*20);
}

void CContextMenu::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	painter->save();
	//painter->drawRect(boundingRect());
	painter->restore();
}

void CContextMenu::onActionClick(bool bSub)
{
	if (bSub)
	{
		QObject* pObj = sender();
		CMenuItem* pItem = dynamic_cast<CMenuItem*>(pObj);
		if (pItem)
		{
			QAction* pAction = pItem->getAction();
			QMenu* pMenu = pAction->menu();
			if (pMenu)
			{
				// 此处处理二级子菜单显示位置
				QPoint pos = pItem->pos().toPoint();
				pos += QPoint(pItem->boundingRect().width(),0);
				
				if (m_SubContextMenu == NULL)
				{
					m_SubContextMenu = new CContextMenu("",this,this);
					//m_SubContextMenu->setScaleFactor(m_factor);
				}
				
				m_SubContextMenu->setParam(pMenu,m_Scene);
				m_SubContextMenu->deleteContextItem();
				m_SubContextMenu->exec(pos);
			}
		}
	}
	else
	{
		deleteAllItem();
	}
}

void CContextMenu::hideContextItem()
{
	hide();
	foreach (QGraphicsItem* pItem,m_ContextItems)
	{
		pItem->hide();
	}

	if (m_SubContextMenu)
	{
		m_SubContextMenu->hide();
	}
}

void CContextMenu::deleteContextItem()
{
	foreach (QGraphicsItem* pItem,m_ContextItems)
	{
		m_Scene->removeItem(pItem);
	}
	m_ContextItems.clear();

	if (m_SubContextMenu)
	{
		m_SubContextMenu->deleteContextItem();
	}
}

void CContextMenu::deleteAllItem()
{
	deleteContextItem();

	if (m_ParentMenu)
	{
		m_ParentMenu->deleteContextItem();
	}
}

void CContextMenu::deleteChildMenu(bool bSub)
{
	if (!bSub && m_SubContextMenu)
	{
		m_SubContextMenu->deleteContextItem();
	}
}

void CContextMenu::addContextItem()
{
	foreach(QGraphicsItem* item,m_ContextItems)
	{
		m_Scene->addItem(item);
	}
}

void CContextMenu::createContextItem(const QList<QAction*>& lstAction)
{
	int i = 0;
	int maxLength = 100;
	foreach(QAction* act,lstAction)
	{
		int nlength = act->text().length()*19;
		if (maxLength < nlength)
		{
			maxLength = nlength;
		}
	}
	foreach(QAction* act,lstAction)
	{
		if (act->isSeparator())
		{
			continue;
		}
		QPixmap pixmap(":/image/pushbutton_pressed.png");

		if (act->isVisible() && act->text() != "")
		{
			CMenuItem* item = new CMenuItem(pixmap,act,this);
			item->setItemWidth(maxLength);
			QObject::connect(item,SIGNAL(onClicked(bool)),this,SLOT(onActionClick(bool)));
			QObject::connect(item,SIGNAL(onHoverEntered(bool)),this,SLOT(deleteChildMenu(bool)));
			m_ContextItems.append(item);
		}
	}
}

void CContextMenu::createAnimationGroup()
{
	m_AnimationGroup->clear();
	
	m_Pos.setX(0);
	m_Pos.setY(0);
	if (m_berthPos != eScreenBottom)
	{
//     开始考虑菜单不能越界，后来发现不越界会重叠，所以暂时越界。
// 		if (m_ContextItems.count() > 0 )
// 		{
// 			QRectF boundRect = m_ContextItems[0]->boundingRect();
// 			if (m_Pos.y() + m_ContextItems.count()*boundRect.height() > m_Scene->height())
// 			{
// 				m_Pos.setY(m_Scene->height() - (m_ContextMenu->count() -1)*(boundRect.height() ));
// 			}
// 			if (m_Pos.x() + boundRect.width() > m_Scene->width())
// 			{
// 				m_Pos.setX(m_Scene->width() - (boundRect.width() + 5));
// 			}
// 		}
	}

	for (int i = 0; i < m_ContextItems.count(); i++) 
	{
		QObject* pItem = dynamic_cast<QObject*>(m_ContextItems[i]);
		QRectF boundRect = m_ContextItems[i]->boundingRect();
		
		QPropertyAnimation *anim = new QPropertyAnimation(pItem, "pos");
		if (m_ParentMenu == NULL) // 对于顶层菜单，根据类型设置动画
		{
			anim->setDuration(200 + i * 25);
			anim->setEasingCurve(QEasingCurve::InOutBack);
			anim->setStartValue(QPoint(m_Pos.x(),m_Pos.y()));
			QPoint finalPoint;
			if (m_berthPos == eScreenBottom)
			{
				anim->setStartValue(QPoint(m_Pos.x(),m_Pos.y()) - QPoint(0,2*boundingRect().height()));
				finalPoint = QPoint(m_Pos.x(),m_Pos.y() - (m_ContextItems.count() - i)*(boundRect.height()) - boundingRect().height());
			}
			else if (m_berthPos == eScreenTop)
			{
				finalPoint = QPoint(m_Pos.x(),m_Pos.y() + i*(boundRect.height()));
			}
			else if (m_berthPos == eScreenLeft)
			{
				finalPoint = QPoint(m_Pos.x() + boundRect.width(),m_Pos.y() + i*(boundRect.height()));
			}
			else if (m_berthPos == eScreenRight)
			{
				finalPoint = QPoint(m_Pos.x() - boundRect.width(),m_Pos.y() + i*(boundRect.height()));
			}
			
			anim->setEndValue(finalPoint);
		}
		else // 对于子菜单，从上往下显示
		{
			anim->setDuration(200 + i * 25);
			anim->setEasingCurve(QEasingCurve::InOutBack);
			anim->setStartValue(QPoint(m_Pos.x(),m_Pos.y()));
			QPoint finalPoint = QPoint(m_Pos.x(),m_Pos.y() + i*(boundRect.height()));
			anim->setEndValue(finalPoint);
		}
		m_AnimationGroup->addAnimation(anim);
	}
}

void CContextMenu::setBerthPosition(EBerthPostion berthPos)
{
	m_berthPos = berthPos;
}
