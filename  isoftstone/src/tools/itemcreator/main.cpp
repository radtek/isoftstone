
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
#include <QtXml>
#include <QStringList>
#include <QDebug>
#include <QtCore>
#include <QtGui>

#include <iostream>

#include "common.h"
#include "createitem.h"
#include "itemfactory.h"
#include "CBreaker.h"
#include "config.h"

#define WIDTH 300

int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif
	

	QApplication app(argc, argv);

	

	QGraphicsScene scene;
	scene.setSceneRect(0, 0, WIDTH, WIDTH);
	scene.setBackgroundBrush(QBrush(QColor("black")));
	scene.setItemIndexMethod(QGraphicsScene::NoIndex);
	
	QGraphicsView view(&scene);
	view.resize(WIDTH, WIDTH);

	//view.fitInView(scene.sceneRect());

	if (1)
	{
		CGraphicsGroupItem item(NULL);
		QString strID;
		item.loadItem(CConfig::instance()->getDataDir() + QString("\\element\\capacitor\\gd_dr1.dr.icn.g"),strID);

		CCBreaker copyItem;
		copyItem.copy(&item);

		QGraphicsItem* pItem = &copyItem;
 		scene.addItem(pItem);
		pItem->setPos(scene.sceneRect().width()/2,scene.sceneRect().height()/2);

// 		pItem = &item;
// 		scene.addItem(pItem);
// 		pItem->setPos(scene.sceneRect().width()/3,scene.sceneRect().height()/3);

		view.show();
		app.exec();
	}
	else
	{
		QList<SElecItemInfo> lstItems = CItemFactory::instance()->loadElement("D:\\iSoftStone\\graph\\element");
		foreach(SElecItemInfo info,lstItems)
		{
			scene.clear();

			CGraphicsGroupItem item(NULL);
			QString strID;
			item.loadItem(info.m_fileName,strID);
			item.setPos(0,0);
			scene.addItem(&item);

			//QThread::currentThread()->wait(500);
			QPixmap pix = QPixmap::grabWidget(&view,QRect(0,0,300,300));
			pix.save(info.m_fileName + ".cp.png","png");
		}
	}

	return 0;

}

