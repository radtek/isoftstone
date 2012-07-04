
#include "ItemFactory.h"
#include "CreateItem.h"
#include "common.h"
#include "mainwindow.h"
#include "config.h"
#include "setting.h"
#include "edcc-global.h"
#include "qttoolbardialog.h"

#include "server.h"

CMainWindow::CMainWindow(CService* pServer): QMainWindow()
{
	setWindowTitle(WINDOW_TITLE);
	QIcon icon;
	icon.addFile(QString::fromUtf8(":/images/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
	setWindowIcon(icon);

	m_Server = pServer;
	m_Server->start();

	CGraphicsItemProxy::instance();
	CItemFactory::instance();
	m_bFullScreen = true;

	m_view = new CView(this);
	m_scene = new CGraphicsScene(this);
	m_view->setScene(m_scene);
	
	createMenus();
	createToolBars();
	createToolBarManager();
	readSettings();
	menuBar()->setVisible(false);
	setToolbarVisible(false);

	m_pluginWindow.setParentWindow(this);
	m_pluginWindow.setMenuBar(menuBar());

//  	CItemFactory::instance()->loadElement(CConfig::instance()->getElementDir());
//  	CItemFactory::instance()->loadBay(CConfig::instance()->getBayDir());
// 
// 	openHomePage();

	setCentralWidget(m_view);
}

void CMainWindow::createMenus()
{

	QMenu *fileMenu = new QMenu(tr("&�ļ�"), this);

	QAction *openAction = fileMenu->addAction(tr("&��"));
	openAction->setShortcut(QKeySequence(tr("Ctrl+O")));

	QAction *openElementAction = fileMenu->addAction(tr("&��ͼԪ"));
	connect(openElementAction, SIGNAL(triggered()), this, SLOT(openElementFile()));

	QAction *openBayAction = fileMenu->addAction(tr("&�򿪼��"));
	connect(openBayAction, SIGNAL(triggered()), this, SLOT(openBayFile()));

	QAction *exportAction = fileMenu->addAction(tr("&����ͼƬ"));
	exportAction->setShortcut(QKeySequence(tr("Ctrl+E")));

	actionHomePage = fileMenu->addAction(tr("&��ҳ"));
	actionHomePage->setIcon(QIcon(":/images/home.png"));
	connect(actionHomePage, SIGNAL(triggered(bool)), this, SLOT(openHomePage()));

	quitAction = fileMenu->addAction(tr("�˳�"));
	quitAction->setIcon(QIcon(":/images/exit2.png"));
	quitAction->setShortcuts(QKeySequence::Quit);


	menuBar()->addMenu(fileMenu);

	QMenu *viewMenu = new QMenu(tr("&��ͼ"), this);

	QAction* sourceAction = viewMenu->addAction(tr("&Դ�ļ�"));
	connect(sourceAction, SIGNAL(triggered(bool)), this, SLOT(openSourceFile()));

	QAction* backgroundAction = viewMenu->addAction(tr("&����"));
	backgroundAction->setEnabled(false);
	backgroundAction->setCheckable(true);
	backgroundAction->setChecked(false);
	connect(backgroundAction, SIGNAL(toggled(bool)), m_view, SLOT(setViewBackground(bool)));

	QAction* outlineAction = viewMenu->addAction(tr("&�߿�"));
	outlineAction->setEnabled(false);
	outlineAction->setCheckable(true);
	outlineAction->setChecked(true);
	connect(outlineAction, SIGNAL(toggled(bool)), m_view, SLOT(setViewOutline(bool)));

	QAction* telnetAction = viewMenu->addAction(tr("&Զ�̿���"));
	telnetAction->setEnabled(true);
	telnetAction->setCheckable(true);
	telnetAction->setChecked(true);
	connect(telnetAction, SIGNAL(toggled(bool)), this, SLOT(telnetControl()));

	menuBar()->addMenu(viewMenu);

	QMenu *rendererMenu = new QMenu(tr("&��Ⱦ"), this);
	rendererMenu->setObjectName("Renderer");
	QAction* nativeAction = rendererMenu->addAction(tr("&����"));
	nativeAction->setCheckable(true);
	nativeAction->setChecked(true);
	QAction* imageAction = rendererMenu->addAction(tr("&ͼ��"));
	imageAction->setCheckable(true);


	QActionGroup *rendererGroup = new QActionGroup(this);
	rendererGroup->addAction(nativeAction);
	rendererGroup->addAction(imageAction);

	menuBar()->addMenu(rendererMenu);

	QAction* configureToolBarsAct = new QAction(tr("����������"), this);
	configureToolBarsAct->setObjectName(QString::fromUtf8("configureToolBarsAct"));
	configureToolBarsAct->setStatusTip(tr("����������"));
	QObject::connect(configureToolBarsAct, SIGNAL(triggered()),this, SLOT(configureToolBars()));

	QAction* saveToolBarsAct = new QAction(tr("���湤����"), this);
	saveToolBarsAct->setObjectName(QString::fromUtf8("saveToolBarsAct"));
	saveToolBarsAct->setStatusTip(tr("���湤����"));
	QObject::connect(saveToolBarsAct, SIGNAL(triggered()),this, SLOT(saveToolBars()));

	QAction* restoreToolBarsAct = new QAction(tr("&�ָ�������"), this);
	restoreToolBarsAct->setObjectName(QString::fromUtf8("restoreToolBarsAct"));
	restoreToolBarsAct->setStatusTip(tr("�ָ�������"));
	QObject::connect(restoreToolBarsAct, SIGNAL(triggered()),this, SLOT(restoreToolBars()));

	QMenu* settingsMenu = menuBar()->addMenu(tr("&����"));
	settingsMenu->addAction(configureToolBarsAct);
	settingsMenu->addAction(saveToolBarsAct);
	settingsMenu->addAction(restoreToolBarsAct);

	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
	connect(exportAction, SIGNAL(triggered()), this, SLOT(exportImage()));
	connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void CMainWindow::createToolBars()
{
	fileToolBar = addToolBar(tr("�ļ�"));
	fileToolBar->setObjectName(QString::fromUtf8("fileToolBar"));

	editToolBar = addToolBar(tr("�༭"));
	editToolBar->setObjectName(QString::fromUtf8("editToolBar"));
	editToolBar->addAction(actionHomePage);
	editToolBar->addAction(quitAction);
}

void CMainWindow::setToolbarVisible(bool bHide)
{
	fileToolBar->setVisible(bHide);
	editToolBar->setVisible(bHide);
}

void CMainWindow::createToolBarManager()
{
	toolBarManager = new QtToolBarManager(this);
	toolBarManager->setMainWindow(this);

	QString fileStr = tr("�ļ�");
	QString editStr = tr("�༭");

	toolBarManager->addToolBar(fileToolBar, fileStr);
	toolBarManager->addToolBar(editToolBar, editStr);

	QList<QAction*> lstMenu = menuBar()->actions();
	foreach(QAction* act,lstMenu)
	{
		if (act->menu())
		{
			QMenu* menu = act->menu();
			foreach (QAction* subAct,menu->actions())
			{
				toolBarManager->addAction(subAct,menu->title());
			}
		}
	}

}

void CMainWindow::iniMenuAndTool(CView* pView,CGraphicsScene* pScene)
{
	pScene->clearContextMenu();

	QMenu* barMenu = new QMenu(this);
	barMenu->setIcon(QIcon(":images/mainmenu.png"));
	barMenu->setToolTip(QObject::tr("���˵�"));
	barMenu->addActions(menuBar()->actions());

	// ����sceneÿ�������ɾ��ͼԪ������ÿ���½�
	CItemToolBar* itemToolbar = new CItemToolBar;

	QMenu* toolMenu = new QMenu;
	QList<QAction*> lstAction;
	lstAction.append(barMenu->menuAction());
	lstAction.append(actionHomePage);
	lstAction.append(quitAction);
	toolMenu->addActions(lstAction);

	itemToolbar->setParam(toolMenu,m_view);
	itemToolbar->fitItemBar();
	pScene->addItem(itemToolbar);
	foreach(CContextMenu* pMenu,itemToolbar->getContextMenu())
	{
		pScene->addContextMenu(pMenu);
	}

	pScene->setToolbar(itemToolbar);
	pView->setToolbar(itemToolbar);
}

void CMainWindow::openHomePage()
{
	QString strHome = CConfig::instance()->getConfigValue("dcc.ini","HOMEPAGE","HOMEPAGE");
	strHome = CConfig::instance()->getFilePath(strHome);
	m_view->openFile(strHome);
}

void CMainWindow::setFullScreen()
{
	m_bFullScreen = !m_bFullScreen;

	QList<QToolBar *> allbar = findChildren<QToolBar *>();
	if (m_bFullScreen)
	{
		setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);
		showFullScreen();

		menuBar()->setHidden(true);
		foreach (QToolBar* bar,allbar)
		{
			bar->setHidden(true);
		}
		statusBar()->setHidden(true);
	}
	else
	{
		menuBar()->setHidden(false);
		foreach (QToolBar* bar,allbar)
		{
			bar->setHidden(false);
		}
		statusBar()->setHidden(false);
		m_scene->hideItemBar();
		m_scene->hideContextMenu();

		setWindowFlags(Qt::Widget|Qt::WindowMinMaxButtonsHint|Qt::WindowCloseButtonHint|Qt::WindowTitleHint	);
		showMaximized();
	}
}

void CMainWindow::openSourceFile()
{
	QProcess* openFile = new QProcess(this);
	QString szContent;
	QString strValue = CConfig::instance()->getConfigValue("dcc.ini","TOOL","TEXTEDIT");
	if (strValue.isEmpty())
	{
		strValue = "notepad";
	}
	szContent = strValue + " " + m_view->currentFile();
	openFile->start(szContent);
}

void CMainWindow::openFile(const QString &path)
{
	QString fileName;
	if (path.isNull())
	{	
		fileName = QFileDialog::getOpenFileName(this, tr("�� G �ļ�"),CConfig::instance()->getDisplayDir(),tr("G �ļ� (*.g)"));
	}
	else
	{
		fileName = path;
	}

	if (!fileName.isEmpty()) 
	{
		QFile file(fileName);
		if (!file.exists()) 
		{
			QMessageBox::critical(this, tr("�� G �ļ�"),tr("���ļ�ʧ�� '%1'.").arg(fileName));
			return;
		}

		m_view->openFile(fileName);
	}
}

void CMainWindow::openElementFile()
{
	m_scene->setToolbar(NULL);
	m_view->setToolbar(NULL);

	QString fileName;
	fileName = QFileDialog::getOpenFileName(this, tr("�� G ͼԪ�ļ�"),CConfig::instance()->getElementDir() ,tr("G �ļ� (*.g)"));

	if (!fileName.isEmpty()) 
	{
		m_scene->drawElement(fileName);	
	}
}

void CMainWindow::openBayFile()
{
	m_scene->setToolbar(NULL);
	m_view->setToolbar(NULL);

	QString fileName;
	fileName = QFileDialog::getOpenFileName(this, tr("�� G ����ļ�"),CConfig::instance()->getBayDir() ,tr("G �ļ� (*.g)"));

	if (!fileName.isEmpty()) 
	{
		m_scene->drawBay(fileName);	
	}
}

void CMainWindow::exportImage()
{
	QString fileName = m_view->currentFile();
	fileName = fileName.replace(".g",".png",Qt::CaseInsensitive);
	fileName = QFileDialog::getSaveFileName(this, tr("�����ļ�"), fileName, tr("Images (*.png *.jpg)")) ;

	if ( !fileName.isEmpty() )
	{
		if(!( fileName.endsWith( ".png" ) || fileName.endsWith( ".jpg" )))
		{
			fileName.append( ".png" );
		}

		QFile file( fileName );
		if ( file.open( QIODevice::WriteOnly ) )
		{
			QPixmap buffer( this->width(),this->height() );
			buffer = QPixmap::grabWidget(m_view);
			buffer.toImage().save( fileName );
		}
	}
}

void CMainWindow::readSettings()
{
	QSettings settings("Qt Software", "Application Example");
	QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
	QSize size = settings.value("size", QSize(400, 400)).toSize();
	QByteArray toolBarsState = settings.value("toolBarsState").toByteArray();
	QByteArray docksState = settings.value("docksState").toByteArray();
	resize(size);
	move(pos);
	toolBarManager->restoreState(toolBarsState);
	restoreState(docksState);
}

void CMainWindow::writeSettings()
{
	QSettings settings("Qt Software", "Application Example");
	settings.setValue("pos", pos());
	settings.setValue("size", size());
	settings.setValue("toolBarsState", toolBarManager->saveState());
	settings.setValue("docksState", saveState());
}

void CMainWindow::configureToolBars()
{
	QtToolBarDialog dlg(this);
	dlg.setToolBarManager(toolBarManager);
	dlg.exec();
}

void CMainWindow::saveToolBars()
{
	QString fileName = QFileDialog::getSaveFileName(this,tr("���湤����"), QString(), "*.state");
	if (fileName.isEmpty())
		return;
	QFileInfo fi(fileName);
	if (fi.suffix() != QString("state"))
		fileName += QString(".state");

	QFile file(fileName);
	if (file.open(QFile::WriteOnly)) 
	{
		QByteArray array = toolBarManager->saveState();
		file.write(array);
		file.close();
	}
}

void CMainWindow::restoreToolBars()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("�ָ�������״̬"), QString(), "*.state");
	if (fileName.isEmpty())
		return;

	QFile file(fileName);
	if (file.open(QFile::ReadOnly)) 
	{
		QByteArray array = file.readAll();
		file.close();
		toolBarManager->restoreState(array);
	}
}