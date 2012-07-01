
#include "event.h"
#include "scene.h"
#include "resource.h"
#include "dcc-global.h"
#include "enum.h"
#include "ialgorithm.h"
#include "ItemFactory.h"
#include "CreateItem.h"

#include "mainwindow.h"
#include "view.h"

#include "logobutton.h"
#include "pipetimeitem.h"
#include "meter1.h"
#include "meter2.h"
#include "thermometer.h"
#include "progressbar1.h"
#include "scale1.h"
#include "scale2.h"
#include "lcdnumber.h"
#include "indicator.h"
#include "sounditem.h"
#include "lightitem.h"
#include "batteryitem.h"
#include "Curve.h"
#include "qtthumbwheel.h"


CGraphicsScene::CGraphicsScene(QObject *parent): QGraphicsScene(parent)
{
	m_updateTimer = new QTimer(this);
	connect(m_updateTimer, SIGNAL(timeout()), this, SLOT(updateValue()));

	m_menuManager = new CMenuManager(parent);
	m_menuManager->init();

	m_contextMenu = new CContextMenu(QObject::tr("右键菜单"));
	addContextMenu(m_contextMenu);
	m_itemBar = NULL;
	m_xFactor = 1.0;
	m_yFactor = 1.0;

	m_engine = new QDeclarativeEngine;

	//initScene();
}

CGraphicsScene::~CGraphicsScene()
{
	m_menuManager->destroy();
	delete m_menuManager;
}

void CGraphicsScene::initScene()
{
	QtThumbWheel *rotwheel = new QtThumbWheel(0, 359, 10, 0, Qt::Vertical, NULL);
	rotwheel->setWrapsAround(true);
	addWidget(rotwheel);

	CCurve* pCurveItem = new CCurve;
	pCurveItem->setPos(100,100);
	//addItem(pCurveItem);

	// 增加时间
	QGraphicsItem* timeItem = new CPipeTimeItem;
	timeItem->setPos(100,100);
	//addItem(timeItem);

	CSoundItem* sound = new CSoundItem;
	sound->setValue(50);
	sound->setPos(300,300);
	//addItem(sound);

	CBatteryItem* battery = new CBatteryItem;
	battery->setValue(50);
	battery->setPos(400,400);
	//addItem(battery);

	CMeterItem* meter1 = new CMeterItem;
	meter1->setValue(50);
	meter1->setPos(300,300);
	//addItem(meter1);

	CMeterItem2* meter2 = new CMeterItem2;
	meter2->setValue(50);
	meter2->setPos(300,500);
	//addItem(meter2);

	CThermoMeterItem* meter3 = new CThermoMeterItem;
	meter3->setValue(50);
	meter3->setPos(600,100);
	//addItem(meter3);

	CProgressBar1* bar1 = new CProgressBar1;
	bar1->setValue(60);
	bar1->setPos(200,400);
	//addItem(bar1);

	CScale1* scale1 = new CScale1;
	scale1->setValue(20);
	scale1->setPos(300,500);
	//addItem(scale1);
	
	CScale2* scale2 = new CScale2;
	scale2->setValue(20);
	scale2->setPos(300,600);
	//addItem(scale2);

	CLCDNumber* lcd1 = new CLCDNumber;
	lcd1->setValue(35);
	lcd1->setPos(800,100);
	//addItem(lcd1);

	CIndicator* indi1 = new CIndicator;
	indi1->setValue(35);
	indi1->setPos(800,300);
	//addItem(indi1);
}

void CGraphicsScene::setToolbar(CItemToolBar* pBar)
{
	if (m_itemBar)
	{
		m_itemBar = NULL;
	}

	m_itemBar = pBar;
}

void CGraphicsScene::hideItemBar()
{
	if (m_itemBar)
	{
		m_itemBar->hide();
	}
}

void CGraphicsScene::setScaleFactor(qreal xfactor,qreal yfactor)
{
	m_xFactor = xfactor;
	m_yFactor = yfactor;

	m_contextMenu->setScaleFactor(m_xFactor,m_yFactor);
	foreach(CContextMenu* cMenu,m_lstContextMenu)
	{
		cMenu->setScaleFactor(m_xFactor,m_yFactor);
	}
}

void CGraphicsScene::clearContextMenu()
{
	m_lstContextMenu.clear();
	m_contextMenu->deleteAllItem();
	m_lstContextMenu.append(m_contextMenu);

}

void CGraphicsScene::hideContextMenu()
{
	foreach(CContextMenu* pMenu,m_lstContextMenu)
	{
		pMenu->deleteAllItem();
		//pMenu->hideMenu();
	}
}

void CGraphicsScene::addContextMenu(CContextMenu* pMenu)
{
	m_lstContextMenu.append(pMenu);
}

void CGraphicsScene::drawBoundLine(bool bLine)
{
	QPen outline(Qt::black, 2, Qt::DashLine);
	outline.setCosmetic(true);
	m_outlineItem->setPen(outline);
	m_outlineItem->setBrush(Qt::NoBrush);
	m_outlineItem->setVisible(bLine);
	m_outlineItem->setZValue(1);
}

bool CGraphicsScene::draw(const QString& fileName)
{
	if (!QFile::exists(fileName) || QFileInfo(fileName).suffix() != "g")
	{
		QMessageBox::warning(dynamic_cast<QWidget*>(parent()),QObject::tr("没有打开图形文件！"),QObject::tr("没有打开图形文件!") + fileName);
		return false;
	}
	m_updateTimer->stop();
	bool bret = CItemFactory::instance()->draw(this,fileName);
	m_updateTimer->start(1000);
	if (bret)
	{
		m_currentFile = fileName;
		collectItemInfo();

		CMainWindow* window = dynamic_cast<CMainWindow*>(parent());
		if (window)
		{
			m_contextMenu = new CContextMenu(QObject::tr("右键菜单"));

			window->setWindowTitle(WINDOW_TITLE + " - " + QFileInfo(fileName).baseName());
			window->iniMenuAndTool(dynamic_cast<CView*>(views()[0]),this);
		}
	}
	else
	{
		QMessageBox::warning(dynamic_cast<QWidget*>(parent()),QObject::tr("文件打开失败！"),QObject::tr("文件打开失败!")+ fileName);
	}
	return bret;
}

bool CGraphicsScene::drawElement(const QString& fileName)
{
	m_updateTimer->stop();
	clear();
	setSceneRect(0,0,600,600);

	CGraphicsGroupItem* pItem = new CGraphicsGroupItem(NULL);
	QString strID;
	pItem->loadItem(fileName,strID);

	pItem->setPos(sceneRect().width()/2,sceneRect().height()/2);
	addItem(pItem);

	return true;
}

bool CGraphicsScene::drawBay(const QString& fileName)
{
	m_updateTimer->stop();
	clear();
	setSceneRect(0,0,600,600);

	CGraphicsComponent* pItem = new CGraphicsComponent(NULL);
	QString strID;
	SLayerInfo info;
	pItem->loadItem(fileName,strID);

	pItem->setPos(sceneRect().width()/2,sceneRect().height()/2);
	addItem(pItem);

	return true;
}

bool CGraphicsScene::drawQML(const QString& fileName)
{
	m_updateTimer->stop();
	clear();
	setSceneRect(0,0,600,600);

	m_itemBar = NULL;

	QDeclarativeComponent component(m_engine, QUrl::fromLocalFile(fileName));
	QGraphicsObject *pItem = qobject_cast<QGraphicsObject *>(component.create());
	pItem->setPos(0,0);
	addItem(pItem);
	return true;
}

QString CGraphicsScene::currentFile()
{
	return m_currentFile;
}

void CGraphicsScene::collectItemInfo()
{
	m_itemMap.clear();
	m_dynamicMap.clear();
	CResource::instance()->clear();
	foreach(QGraphicsItem* pItem,items())
	{
		IElementBase* pbase = dynamic_cast<IElementBase*>(pItem);
		if (pbase)
		{
			if (pbase->getItemInfo().bDynamic)
			{
				CDynamicItemBase* pdBase = dynamic_cast<CDynamicItemBase*>(pbase);
				if (pdBase)
				{
					QVector<quint64> vecKeys = pdBase->getKeyIDs();
					foreach (quint64 keyid,vecKeys)
					{
						m_dynamicMap.insert(keyid,pdBase);

						CResource::instance()->setValue(keyid,0);
					}
				}
			}
			m_itemMap.insert(pItem->type(),pItem);
		}
	}
}

void CGraphicsScene::updateValue()
{
	QMap<quint64,QVariant> valueMap = CResource::instance()->getValues(m_dynamicMap.keys());
	
	QMapIterator<quint64,QVariant> iter(valueMap);
	while(iter.hasNext())
	{
		iter.next();
		quint64 keyID = iter.key();
		QVariant value = iter.value();
		QList<CDynamicItemBase*> lstItem = m_dynamicMap.values(keyID);
		foreach(CDynamicItemBase* pItem,lstItem)
		{
			pItem->setValue(value);
		}
	}
}

void CGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if (!m_itemBar)
	{
		QGraphicsScene::mousePressEvent(event);
		return;
	}
	
	bool bRemove = true;
	QList<QGraphicsItem*> lstItem = items(event->scenePos(),Qt::IntersectsItemBoundingRect,Qt::AscendingOrder);
	foreach(QGraphicsItem* cItem,lstItem)
	{
		CMenuItem* mItem = dynamic_cast<CMenuItem*>(cItem);
		QGraphicsPixmapItem* pixmapItem = dynamic_cast<QGraphicsPixmapItem*>(cItem);

		if (mItem || pixmapItem)
		{
			bRemove = false;
			break;
		}

		CLogoButton* pLogo = dynamic_cast<CLogoButton*>(cItem);
		if (pLogo)
		{
			if (m_itemBar)
			{
				m_itemBar->setMenuLock(true);
			}
			break;
		}
		else
		{
			if (m_itemBar)
			{
				m_itemBar->setMenuLock(false);
			}
		}
	}

	if (bRemove)
	{
		foreach(CContextMenu* pMenu,m_lstContextMenu)
		{
			pMenu->deleteAllItem();
			//pMenu->hideMenu();
		}
	}

	QGraphicsScene::mousePressEvent(event);
}

void CGraphicsScene::contextMenuEvent( QGraphicsSceneContextMenuEvent *  event )
{
	EItemType eType = CIMGCommon;

	QGraphicsItem* pItem = NULL;

	QList<QGraphicsItem*> lstItem = items(event->scenePos());
	if (lstItem.count() >0 )
	{
		CAlgorithm::filteMetaType(lstItem,pItem,eType);
	}

	QMenu* pMenu = m_menuManager->getContextActions(eType,100000);
	if (pMenu)
	{		
 		if (true && m_itemBar)
 		{
 			m_contextMenu->setParam(pMenu,this);
 			m_contextMenu->exec(event->scenePos());
 		} 		else		{
			pMenu->exec(event->screenPos());
		}
	}

	QGraphicsScene::contextMenuEvent(event);
}

void CGraphicsScene::timerEvent(QTimerEvent * event)
{
	// 定时刷新数据，只刷新本场景中数据
}

void CGraphicsScene::customEvent(QEvent * event)
{
	if (event->type() == eEventSceneFileChange)
	{
		CSceneFileChangeEvent* ce = dynamic_cast<CSceneFileChangeEvent*>(event);
		if (ce)
		{
			draw(ce->getFileName());
		}
		foreach (QGraphicsView* pView,views())
		{
			pView->fitInView(sceneRect());
			CView* cView = dynamic_cast<CView*>(pView);
			if (cView)
			{
				cView->adjustScene();
			}
		}
	}
	QGraphicsScene::customEvent(event);
}

void CGraphicsScene::keyPressEvent ( QKeyEvent * event )
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_itemBar)
		{
			foreach(CContextMenu* pMenu,m_lstContextMenu)
			{
				pMenu->deleteAllItem();
			}
			m_itemBar->setMenuLock(false);
		}
	}
	else if (event->key() == Qt::Key_F11)
	{
		
	}
	else if (event->key() == Qt::Key_Space)
	{
		foreach (QGraphicsView* view,this->views())
		{
			
		}
	}
	else if (event->key() == Qt::Key_PageUp ||
		event->key() == Qt::Key_Backspace ||
		(event->key() == Qt::Key_Left && event->modifiers() == Qt::AltModifier) )
	{
		
	}
	else if (event->key() == Qt::Key_PageDown ||
		(event->key() == Qt::Key_Right && event->modifiers() == Qt::AltModifier) )
	{
		
	}
	else if (event->key() == Qt::Key_O && event->modifiers() == Qt::ControlModifier)
	{
		
	}
	else if (event->key() == Qt::Key_Minus )
	{
		
	}
	else if (event->key() == Qt::Key_Plus)
	{
		
	}
	else if (event->key() == Qt::Key_Home)
	{
		
	}

	QGraphicsScene::keyPressEvent(event);
}

void CGraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent )
{
	if (true)
	{
		if (!m_itemBar)
		{
			QGraphicsScene::mouseMoveEvent(mouseEvent);
			return;
		}
		
		EBerthPostion berthPos = m_itemBar->getBerthPostion();

		QRect screen = QApplication::desktop()->screenGeometry();
		QPoint screenPos = mouseEvent->screenPos();
		if (berthPos == eScreenBottom)
		{
			if ((screenPos.x() < screen.width()-100 && screenPos.x() > 100)&&
				(screenPos.y() < screen.height() && screenPos.y() > screen.height()- 80 ))
			{
				m_itemBar->show();
			}
			else
			{
				m_itemBar->hide();
			}
		}
		else if (berthPos == eScreenLeft)
		{
			if ((screenPos.x() < 80 && screenPos.x() > 0)&&
				(screenPos.y() > 100 && screenPos.y() < screen.height()-100 ))
			{
				m_itemBar->show();
			}
			else
			{
				m_itemBar->hide();
			}
		}
		else if (berthPos == eScreenTop)
		{
			if ((screenPos.x() < screen.width()-100 && screenPos.x() > 100)&&
				(screenPos.y() < 80 && screenPos.y() > 0 ))
			{
				m_itemBar->show();
			}
			else
			{
				m_itemBar->hide();
			}
		}
		else if (berthPos == eScreenRight)
		{
			if ((screenPos.x() < screen.width() && screenPos.x() > screen.width() - 80)&&
				(screenPos.y() > 100 && screenPos.y() < screen.height()-100 ))
			{
				m_itemBar->show();
			}
			else
			{
				m_itemBar->hide();
			}
		}
	}

	QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void CGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
}