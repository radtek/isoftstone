
#include "mainwindow_dock.h"

#include "createdockdialog.h"
#include "colordockwidget.h"
#include "colorframe.h"

Q_DECLARE_METATYPE(QDockWidget::DockWidgetFeatures)

QMainWindow_Dock::QMainWindow_Dock(QWidget *parent): QMainWindow(parent)
{
}


void QMainWindow_Dock::setupMenuBar()
{
	m_bShowDock = false;

    QMenu *menu = menuBar()->addMenu(tr("&布局"));

    QAction *action = menu->addAction(tr("保存布局"));
    connect(action, SIGNAL(triggered()), this, SLOT(saveLayout()));

    action = menu->addAction(tr("打开布局"));
    connect(action, SIGNAL(triggered()), this, SLOT(loadLayout()));

	setupDockMenus();
}

void QMainWindow_Dock::saveDockWidgets(const QString& strFile)
{
	if (QFile::exists(strFile))
	{
		QFile::remove(strFile);
	}
	QSettings settings(strFile, QSettings::IniFormat);
	settings.beginGroup("DOCK");
	// 搜索所有DOCK，然后保存布局

	QList<CColorDockWidget*> dock_list = qFindChildren<CColorDockWidget*>(this);
	int i = 0;
	foreach (CColorDockWidget *dock, dock_list) 
	{
		QStringList lstValue ;
		lstValue << "w";
		lstValue << dock->widget()->objectName();
		QString key = QString::number(++i);
		settings.setValue(key,lstValue);
	}
	settings.sync();
	settings.endGroup();
}

void QMainWindow_Dock::saveLayout()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存布局文件"));
    if (fileName.isEmpty())
        return;
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) 
	{
        QString msg = tr("打开布局文件失败 %1\n%2").arg(fileName).arg(file.errorString());
        QMessageBox::warning(this, tr("错误"), msg);
        return;
    }

    QByteArray geo_data = saveGeometry();
    QByteArray layout_data = saveState();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();
    if (ok)
        ok = file.write(layout_data) == layout_data.size();

    if (!ok) 
	{
        QString msg = tr("写入布局文件失败 %1\n%2").arg(fileName).arg(file.errorString());
        QMessageBox::warning(this, tr("错误"), msg);
        return;
    }

	saveDockWidgets(fileName + ".ini");
}

void QMainWindow_Dock::loadLayout()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("加载布局文件"));
    if (fileName.isEmpty())
        return;

	destroyAllDock();
	createDockWidgets(fileName);
	
    QFile file(fileName.remove(".ini"));
    if (!file.open(QFile::ReadOnly)) 
	{
        QString msg = tr("打开布局文件失败 %1\n%2").arg(fileName).arg(file.errorString());
        QMessageBox::warning(this, tr("错误"), msg);
        return;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok)
	{
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok)
	{
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok) ok = restoreGeometry(geo_data);
    if (ok) ok = restoreState(layout_data);

    if (!ok) 
	{
        QString msg = tr("读取布局信息失败 %1").arg(fileName);
        QMessageBox::warning(this, tr("错误"), msg);
        return;
    }
}


QAction *addAction(QMenu *menu, const QString &text, QActionGroup *group, QSignalMapper *m_actionMapper,
                    int id)
{
    bool first = group->actions().isEmpty();
    QAction *result = menu->addAction(text);
    result->setCheckable(true);
    result->setChecked(first);
    group->addAction(result);
    QObject::connect(result, SIGNAL(triggered()), m_actionMapper, SLOT(map()));
    m_actionMapper->setMapping(result, id);
    return result;
}

void QMainWindow_Dock::setupDockMenus()
{
    qRegisterMetaType<QDockWidget::DockWidgetFeatures>();

	QMenu* dockWidgetMenu = menuBar()->addMenu(tr("&停靠窗管理"));

	QAction* createDockWidgetAction = new QAction(tr("增加Dock"), this);
	connect(createDockWidgetAction, SIGNAL(triggered()), this, SLOT(createDockWidget()));
	m_destroyDockMenu = new QMenu(tr("销毁Dock"), this);
	m_destroyDockMenu->setEnabled(false);
	connect(m_destroyDockMenu, SIGNAL(triggered(QAction*)), this, SLOT(destroyDockWidget(QAction*)));

	m_showDockAction = new QAction(tr("显示停靠窗"), this);
	connect(m_showDockAction, SIGNAL(triggered()), this, SLOT(showDockWidget()));

	dockWidgetMenu->addSeparator();
	dockWidgetMenu->addAction(m_showDockAction);
	dockWidgetMenu->addAction(createDockWidgetAction);
	dockWidgetMenu->addMenu(m_destroyDockMenu);

    m_actionMapper = new QSignalMapper(this);
    connect(m_actionMapper, SIGNAL(mapped(int)), this, SLOT(setCorner(int)));

    QMenu *corner_menu = dockWidgetMenu->addMenu(tr("左上角"));
    QActionGroup *group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("顶部靠左"), group, m_actionMapper, 0);
    ::addAction(corner_menu, tr("左部靠上"), group, m_actionMapper, 1);

    corner_menu = dockWidgetMenu->addMenu(tr("右上角"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("顶部靠右"), group, m_actionMapper, 2);
    ::addAction(corner_menu, tr("右部靠上"), group, m_actionMapper, 3);

    corner_menu = dockWidgetMenu->addMenu(tr("左下角"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("底部靠左"), group, m_actionMapper, 4);
    ::addAction(corner_menu, tr("底部靠下"), group, m_actionMapper, 5);

    corner_menu = dockWidgetMenu->addMenu(tr("右下角"));
    group = new QActionGroup(this);
    group->setExclusive(true);
    ::addAction(corner_menu, tr("底部靠右"), group, m_actionMapper, 6);
    ::addAction(corner_menu, tr("右部靠下"), group, m_actionMapper, 7);

}

Qt::DockWidgetArea QMainWindow_Dock::getDockArea(QString strDock)
{
	if (strDock.toUpper() == "TOP")
	{
		return Qt::TopDockWidgetArea;
	}
	else if (strDock.toUpper() == "RIGHT")
	{
		return Qt::RightDockWidgetArea;
	}
	else if (strDock.toUpper() == "LEFT")
	{
		return Qt::LeftDockWidgetArea;
	}
	else
	{
		return Qt::BottomDockWidgetArea;
	}
}

void QMainWindow_Dock::createDockWidgets(const QString& strFile)
{
	QSettings settings(strFile, QSettings::IniFormat);
	settings.beginGroup("DOCK");

	QStringList lstKeys = settings.childKeys();
	foreach (QString strKey,lstKeys) 
	{	
		QStringList strList = settings.value(strKey).toStringList();
		QString name = strList[1];
		Qt::DockWidgetArea dockArea = getDockArea("bottom");
		QFrame *frm = new ColorFrame(name);
		frm->setFrameStyle(QFrame::Box | QFrame::Sunken);
		frm->setObjectName(name);
		frm->setWindowTitle(frm->objectName());

		addWidgetToDock(frm, dockArea);
	}
	settings.endGroup();
}

void QMainWindow_Dock::showDockWidget()
{
	m_bShowDock = !m_bShowDock;
	QList<CColorDockWidget*> dock_list = qFindChildren<CColorDockWidget*>(this);
	foreach (CColorDockWidget *dock, dock_list) 
	{
		dock->setVisible(m_bShowDock);
	}
	m_showDockAction->setText(( m_bShowDock ? tr("隐藏"):tr("显示")) + tr("停靠窗"));
}

void QMainWindow_Dock::setCorner(int id)
{
    switch (id) 
	{
        case 0:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::TopDockWidgetArea);
            break;
        case 1:
            QMainWindow::setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 2:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::TopDockWidgetArea);
            break;
        case 3:
            QMainWindow::setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
            break;
        case 4:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::BottomDockWidgetArea);
            break;
        case 5:
            QMainWindow::setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
            break;
        case 6:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::BottomDockWidgetArea);
            break;
        case 7:
            QMainWindow::setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);
            break;
    }
}


void QMainWindow_Dock::addWidgetToDock(QWidget* wid,Qt::DockWidgetArea area)
{
	CColorDockWidget *dw = new CColorDockWidget(this);;
	dw->setWidget(wid);

	switch (area) 
	{
	case Qt::LeftDockWidgetArea:
	case Qt::RightDockWidgetArea:
	case Qt::TopDockWidgetArea:
	case Qt::BottomDockWidgetArea:
		addDockWidget(area, dw);
		break;
	default:
		if (!restoreDockWidget(dw))
		{
			QMessageBox::warning(this, QString(), tr("存储失败"));
			delete dw;
			return;
		}
		break;
	}

	m_lstDockWidgets.append(dw);
	m_destroyDockMenu->setEnabled(true);
	m_destroyDockMenu->addAction(new QAction(dw->windowTitle(), this));
}

void QMainWindow_Dock::createDockWidget()
{
    CreateDockWidgetDialog dialog(this);
    int ret = dialog.exec();
    if (ret == QDialog::Rejected)
        return;

	QWidget* wid = new QTextEdit;
	wid->setObjectName(tr("测试WIDGET"));
	wid->setWindowTitle(tr("测试标题"));

	addWidgetToDock(wid,dialog.location());
}

void QMainWindow_Dock::destroyDockWidget(QAction *action)
{
    int index = m_destroyDockMenu->actions().indexOf(action);
    delete m_lstDockWidgets.takeAt(index);
    m_destroyDockMenu->removeAction(action);
    action->deleteLater();

    if (m_destroyDockMenu->isEmpty())
        m_destroyDockMenu->setEnabled(false);
}

void QMainWindow_Dock::destroyAllDock()
{
	foreach(QAction* act,m_destroyDockMenu->actions())
	{
		destroyDockWidget(act);
	}
}