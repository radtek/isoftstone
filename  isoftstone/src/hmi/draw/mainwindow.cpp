
#include <QtConcurrentMap>

#include "resource.h"

#include "mainwindow.h"
#include "diagramscene.h"
#include "ItemFactory.h"
#include "CreateItem.h"
#include "common.h"

MainWindow::MainWindow()
{
	CItemFactory::instance()->createItem("D:\\iSoftStone\\graph\\element");

	m_Scene->openGFile(QObject::tr("D:\\Vis\\data\\graph_client\\display\\scada\\ÌÒÏç.fac.pic.g"));
}



