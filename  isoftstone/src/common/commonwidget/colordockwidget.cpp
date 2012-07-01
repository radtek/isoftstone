
#include "colordockwidget.h"
#include "colorframe.h"

// colorbar

QSize ColorTitleBar::minimumSizeHint() const
{
	QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
	Q_ASSERT(dw != 0);
	QSize result(leftPm.width() + rightPm.width(), centerPm.height());
	if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
		result.transpose();
	return result;
}


ColorTitleBar::ColorTitleBar(QWidget *parent): QWidget(parent)
{
	leftPm = QPixmap(":/image/titlebarLeft.png");
	centerPm = QPixmap(":/image/titlebarCenter.png");
	rightPm = QPixmap(":/image/titlebarRight.png");
}

void ColorTitleBar::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	QRect rect = this->rect();

	QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
	Q_ASSERT(dw != 0);

	if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) 
	{
		QSize s = rect.size();
		s.transpose();
		rect.setSize(s);

		painter.translate(rect.left(), rect.top() + rect.width());
		painter.rotate(-90);
		painter.translate(-rect.left(), -rect.top());
	}

	QColor cl("#837BBC");
	cl.setAlpha(200);
	QBrush brush(cl);

	painter.fillRect(rect.left(),rect.top(), leftPm.width(),leftPm.height(),brush);
	painter.drawPixmap(rect.topRight() - QPoint(rightPm.width() - 1, 0), rightPm);

	painter.fillRect( rect.left() + leftPm.width(), rect.top(),
		rect.width() - leftPm.width() - rightPm.width(),
		centerPm.height(), brush);

	QPen pen(QColor::fromRgb(25,12,123));
	painter.setPen(pen);
	QFont font("Arial", 12);
	font.setBold(true);
	painter.setFont(font);
	painter.drawText(rect.left() + 10,rect.height()-5,dw->windowTitle());
}

void ColorTitleBar::contextMenuEvent(QContextMenuEvent *event)
{
	event->accept();
	CColorDockWidget *dockWid = qobject_cast<CColorDockWidget*>(parentWidget());
	if (dockWid)
	{
		dockWid->m_dockMenu->exec(event->globalPos());
	}
}

void ColorTitleBar::mousePressEvent(QMouseEvent *event)
{
	QPoint pos = event->pos();

	QRect rect = this->rect();

	QDockWidget *dw = qobject_cast<QDockWidget*>(parentWidget());
	Q_ASSERT(dw != 0);

	if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar)
	{
		QPoint p = pos;
		pos.setX(rect.left() + rect.bottom() - p.y());
		pos.setY(rect.top() + p.x() - rect.left());

		QSize s = rect.size();
		s.transpose();
		rect.setSize(s);
	}

	const int buttonRight = 7;
	const int buttonWidth = 20;
	int right = rect.right() - pos.x();
	int button = (right - buttonRight)/buttonWidth;
	switch (button) 
	{
	case 0: // 关闭
		event->accept();
		dw->close();
		break;
	case 1: // 浮动
		event->accept();
		dw->setFloating(!dw->isFloating());
		break;
	case 2: // 标题栏水平和垂直交互
		{
			event->accept();
			QDockWidget::DockWidgetFeatures features = dw->features();
			if (features & QDockWidget::DockWidgetVerticalTitleBar)
				features &= ~QDockWidget::DockWidgetVerticalTitleBar;
			else
				features |= QDockWidget::DockWidgetVerticalTitleBar;
			dw->setFeatures(features);
			break;
		}
	default:
		event->ignore();
		break;
	}
}

void ColorTitleBar::updateMask()
{
	QDockWidget *dw = qobject_cast<QDockWidget*>(parent());
	Q_ASSERT(dw != 0);

	QRect rect = dw->rect();
	QPixmap bitmap(dw->size());
	{
		QPainter painter(&bitmap);

		painter.fillRect(rect, Qt::color0);

		QRect contents = rect;
		contents.setTopLeft(geometry().bottomLeft());
		contents.setRight(geometry().right());
		contents.setBottom(contents.bottom()-y());
		painter.fillRect(contents, Qt::color1);

		QRect titleRect = this->geometry();

		if (dw->features() & QDockWidget::DockWidgetVerticalTitleBar) 
		{
			QSize s = rect.size();
			s.transpose();
			rect.setSize(s);

			QSize s2 = size();
			s2.transpose();
			titleRect.setSize(s2);

			painter.translate(rect.left(), rect.top() + rect.width());
			painter.rotate(-90);
			painter.translate(-rect.left(), -rect.top());
		}

		contents.setTopLeft(titleRect.bottomLeft());
		contents.setRight(titleRect.right());
		contents.setBottom(rect.bottom()-y());

		QRect rect = titleRect;


		painter.drawPixmap(rect.topLeft(), leftPm.mask());
		painter.fillRect(rect.left() + leftPm.width(), rect.top(),
			rect.width() - leftPm.width() - rightPm.width(),
			centerPm.height(), Qt::color1);
		painter.drawPixmap(rect.topRight() - QPoint(rightPm.width() - 1, 0), rightPm.mask());

		painter.fillRect(contents, Qt::color1);
	}

	dw->setMask(bitmap);
}


// dockwidget

CColorDockWidget::CColorDockWidget(QWidget *parent): QDockWidget(parent)
{
	setupTitleBarMenu();

	ColorTitleBar *titlebar = new ColorTitleBar(this);
	setTitleBarWidget(titlebar);
	connect(this, SIGNAL(topLevelChanged(bool)), titlebar, SLOT(updateMask()));
	connect(this, SIGNAL(featuresChanged(QDockWidget::DockWidgetFeatures)), titlebar, SLOT(updateMask()), Qt::QueuedConnection);
}

// 根据窗体设置DOCK标题
void CColorDockWidget::setWidget(QWidget *widget)
{
	QDockWidget::setWidget(widget);
	setObjectName( widget->objectName() + tr("停靠窗"));
	setWindowTitle( widget->windowTitle());
	setWindowIcon(widget->windowIcon());
}

// 设置标题栏菜单
void CColorDockWidget::setupTitleBarMenu()
{
	changeSizeHintsAction = new QAction(tr("改变尺寸"), this);
	connect(changeSizeHintsAction, SIGNAL(triggered()), this, SLOT(changeSizeHints()));

	closableAction = new QAction(tr("可关闭"), this);
	closableAction->setCheckable(true);
	connect(closableAction, SIGNAL(triggered(bool)), SLOT(changeClosable(bool)));

	movableAction = new QAction(tr("可移动"), this);
	movableAction->setCheckable(true);
	connect(movableAction, SIGNAL(triggered(bool)), SLOT(changeMovable(bool)));

	floatableAction = new QAction(tr("可浮动"), this);
	floatableAction->setCheckable(true);
	connect(floatableAction, SIGNAL(triggered(bool)), SLOT(changeFloatable(bool)));

	verticalTitleBarAction = new QAction(tr("菜单栏垂直"), this);
	verticalTitleBarAction->setCheckable(true);
	connect(verticalTitleBarAction, SIGNAL(triggered(bool)),SLOT(changeVerticalTitleBar(bool)));

	floatingAction = new QAction(tr("浮动"), this);
	floatingAction->setCheckable(true);
	connect(floatingAction, SIGNAL(triggered(bool)), SLOT(changeFloating(bool)));

	allowedAreasActions = new QActionGroup(this);
	allowedAreasActions->setExclusive(false);

	allowLeftAction = new QAction(tr("允许靠左"), this);
	allowLeftAction->setCheckable(true);
	connect(allowLeftAction, SIGNAL(triggered(bool)), SLOT(allowLeft(bool)));

	allowRightAction = new QAction(tr("允许靠右"), this);
	allowRightAction->setCheckable(true);
	connect(allowRightAction, SIGNAL(triggered(bool)), SLOT(allowRight(bool)));

	allowTopAction = new QAction(tr("允许置顶"), this);
	allowTopAction->setCheckable(true);
	connect(allowTopAction, SIGNAL(triggered(bool)), SLOT(allowTop(bool)));

	allowBottomAction = new QAction(tr("允许置底"), this);
	allowBottomAction->setCheckable(true);
	connect(allowBottomAction, SIGNAL(triggered(bool)), SLOT(allowBottom(bool)));

	allowedAreasActions->addAction(allowLeftAction);
	allowedAreasActions->addAction(allowRightAction);
	allowedAreasActions->addAction(allowTopAction);
	allowedAreasActions->addAction(allowBottomAction);

	areaActions = new QActionGroup(this);
	areaActions->setExclusive(true);

	leftAction = new QAction(tr("左边停放") , this);
	leftAction->setCheckable(true);
	connect(leftAction, SIGNAL(triggered(bool)), SLOT(placeLeft(bool)));

	rightAction = new QAction(tr("右边停放") , this);
	rightAction->setCheckable(true);
	connect(rightAction, SIGNAL(triggered(bool)), SLOT(placeRight(bool)));

	topAction = new QAction(tr("顶部停放") , this);
	topAction->setCheckable(true);
	connect(topAction, SIGNAL(triggered(bool)), SLOT(placeTop(bool)));

	bottomAction = new QAction(tr("底部停放") , this);
	bottomAction->setCheckable(true);
	connect(bottomAction, SIGNAL(triggered(bool)), SLOT(placeBottom(bool)));

	areaActions->addAction(leftAction);
	areaActions->addAction(rightAction);
	areaActions->addAction(topAction);
	areaActions->addAction(bottomAction);

	connect(movableAction, SIGNAL(triggered(bool)), areaActions, SLOT(setEnabled(bool)));
	connect(movableAction, SIGNAL(triggered(bool)), allowedAreasActions, SLOT(setEnabled(bool)));
	connect(floatableAction, SIGNAL(triggered(bool)), floatingAction, SLOT(setEnabled(bool)));
	connect(floatingAction, SIGNAL(triggered(bool)), floatableAction, SLOT(setDisabled(bool)));
	connect(movableAction, SIGNAL(triggered(bool)), floatableAction, SLOT(setEnabled(bool)));

	tabMenu = new QMenu(this);
	tabMenu->setTitle(tr("嵌到TAB页"));
	connect(tabMenu, SIGNAL(triggered(QAction*)), this, SLOT(tabInto(QAction*)));

	splitHMenu = new QMenu(this);
	splitHMenu->setTitle(tr("水平拆分到"));
	connect(splitHMenu, SIGNAL(triggered(QAction*)), this, SLOT(splitInto(QAction*)));

	splitVMenu = new QMenu(this);
	splitVMenu->setTitle(tr("垂直拆分到"));
	connect(splitVMenu, SIGNAL(triggered(QAction*)), this, SLOT(splitInto(QAction*)));

	m_dockMenu = new QMenu("DockMenu", this);
	m_dockMenu->addAction(changeSizeHintsAction);
	m_dockMenu->addAction(closableAction);
	m_dockMenu->addAction(movableAction);
	m_dockMenu->addAction(floatableAction);
	m_dockMenu->addAction(floatingAction);
	m_dockMenu->addAction(verticalTitleBarAction);
	m_dockMenu->addSeparator();
	m_dockMenu->addActions(allowedAreasActions->actions());
	m_dockMenu->addSeparator();
	m_dockMenu->addActions(areaActions->actions());
	m_dockMenu->addSeparator();
	m_dockMenu->addMenu(splitHMenu);
	m_dockMenu->addMenu(splitVMenu);
	m_dockMenu->addMenu(tabMenu);

	connect(m_dockMenu, SIGNAL(aboutToShow()), this, SLOT(updateContextMenu()));
}

// 更新右键菜单
void CColorDockWidget::updateContextMenu()
{
    QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parentWidget());
    const Qt::DockWidgetArea area = mainWindow->dockWidgetArea(this);
    const Qt::DockWidgetAreas areas = allowedAreas();

    closableAction->setChecked(features() & QDockWidget::DockWidgetClosable);
    if (windowType() == Qt::Drawer) 
	{
        floatableAction->setEnabled(false);
        floatingAction->setEnabled(false);
        movableAction->setEnabled(false);
        verticalTitleBarAction->setChecked(false);
    } 
	else 
	{
        floatableAction->setChecked(features() & QDockWidget::DockWidgetFloatable);
        floatingAction->setChecked(isWindow());
        movableAction->setChecked(features() & QDockWidget::DockWidgetMovable);
        verticalTitleBarAction->setChecked(features() & QDockWidget::DockWidgetVerticalTitleBar);
    }

    allowLeftAction->setChecked(isAreaAllowed(Qt::LeftDockWidgetArea));
    allowRightAction->setChecked(isAreaAllowed(Qt::RightDockWidgetArea));
    allowTopAction->setChecked(isAreaAllowed(Qt::TopDockWidgetArea));
    allowBottomAction->setChecked(isAreaAllowed(Qt::BottomDockWidgetArea));

    if (allowedAreasActions->isEnabled()) 
	{
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }

    leftAction->blockSignals(true);
    rightAction->blockSignals(true);
    topAction->blockSignals(true);
    bottomAction->blockSignals(true);

    leftAction->setChecked(area == Qt::LeftDockWidgetArea);
    rightAction->setChecked(area == Qt::RightDockWidgetArea);
    topAction->setChecked(area == Qt::TopDockWidgetArea);
    bottomAction->setChecked(area == Qt::BottomDockWidgetArea);

    leftAction->blockSignals(false);
    rightAction->blockSignals(false);
    topAction->blockSignals(false);
    bottomAction->blockSignals(false);

    if (areaActions->isEnabled()) 
	{
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }

    tabMenu->clear();
    splitHMenu->clear();
    splitVMenu->clear();
    QList<CColorDockWidget*> dock_list = qFindChildren<CColorDockWidget*>(mainWindow);
    foreach (CColorDockWidget *dock, dock_list) 
	{
        tabMenu->addAction(dock->objectName());
        splitHMenu->addAction(dock->objectName());
        splitVMenu->addAction(dock->objectName());
    }
}

// 拆分到某个DOCK
void CColorDockWidget::splitInto(QAction *action)
{
    QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parentWidget());
    QList<CColorDockWidget*> dock_list = qFindChildren<CColorDockWidget*>(mainWindow);
    CColorDockWidget *target = 0;
    foreach (CColorDockWidget *dock, dock_list) 
	{
        if (action->text() == dock->objectName()) 
		{
            target = dock;
            break;
        }
    }
    if (target == 0)
        return;

    Qt::Orientation o = action->parent() == splitHMenu? Qt::Horizontal : Qt::Vertical;
    mainWindow->splitDockWidget(target, this, o);
}

// 表格化到DOCK
void CColorDockWidget::tabInto(QAction *action)
{
    QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parentWidget());
    QList<CColorDockWidget*> dock_list = qFindChildren<CColorDockWidget*>(mainWindow);
    CColorDockWidget *target = 0;
    foreach (CColorDockWidget *dock, dock_list) 
	{
        if (action->text() == dock->objectName()) 
		{
            target = dock;
            break;
        }
    }
    if (target == 0)
        return;

    mainWindow->tabifyDockWidget(target, this);
}

void CColorDockWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	exchangeWindow();
	QDockWidget::mouseDoubleClickEvent(event);
}

// 交换窗体
void CColorDockWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::MidButton)
	{
		exchangeWindow();	
	}
	QDockWidget::mousePressEvent(event);
}

void CColorDockWidget::exchangeWindow()
{
	QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parentWidget());
	QWidget* mdiWid = mainWindow->centralWidget();
	QMdiArea* mdiArea = dynamic_cast<QMdiArea*>(mdiWid);
	if (mdiArea)
	{
		QMdiSubWindow* subWindow = mdiArea->activeSubWindow();
		if (subWindow)
		{
			QWidget* oldWid = subWindow->widget();
			QWidget* newWid = widget();
			oldWid->setParent(NULL);
			newWid->setParent(NULL);

			QRect newRect = newWid->geometry();
			QRect oldRect = oldWid->geometry();

			/*  说明：如果是centerwidget，则后者放到前面，否则放到后面，有区别，否则有错误 */
			newWid->setMinimumSize(oldRect.size());
			subWindow->setWidget(newWid);

			oldWid->setMinimumSize(newRect.size());
			setWidget(oldWid);

 			updateGeometry();
 			update();
		}
	}

}

void CColorDockWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QDockWidget::contextMenuEvent(event);
}

void CColorDockWidget::resizeEvent(QResizeEvent *e)
{
    if (ColorTitleBar *btb = qobject_cast<ColorTitleBar*>(titleBarWidget()))
        btb->updateMask();

    QDockWidget::resizeEvent(e);
}


void CColorDockWidget::allow(Qt::DockWidgetArea area, bool a)
{
    Qt::DockWidgetAreas areas = allowedAreas();
    areas = a ? areas | area : areas & ~area;
    setAllowedAreas(areas);

    if (areaActions->isEnabled()) 
	{
        leftAction->setEnabled(areas & Qt::LeftDockWidgetArea);
        rightAction->setEnabled(areas & Qt::RightDockWidgetArea);
        topAction->setEnabled(areas & Qt::TopDockWidgetArea);
        bottomAction->setEnabled(areas & Qt::BottomDockWidgetArea);
    }
}

void CColorDockWidget::place(Qt::DockWidgetArea area, bool p)
{
    if (!p) return;

    QMainWindow *mainWindow = qobject_cast<QMainWindow *>(parentWidget());
    mainWindow->addDockWidget(area, this);

    if (allowedAreasActions->isEnabled()) 
	{
        allowLeftAction->setEnabled(area != Qt::LeftDockWidgetArea);
        allowRightAction->setEnabled(area != Qt::RightDockWidgetArea);
        allowTopAction->setEnabled(area != Qt::TopDockWidgetArea);
        allowBottomAction->setEnabled(area != Qt::BottomDockWidgetArea);
    }
}

void CColorDockWidget::setCustomSizeHint(const QSize &size)
{
	QWidget* pWid = widget();
	pWid->setMinimumSize(size);
	pWid->updateGeometry();
	pWid->update();
}

void CColorDockWidget::changeSizeHints()
{
 	ChangeDialog dialog(widget(),this);
	if (!dialog.exec())
		return;

 	setCustomSizeHint(dialog.getSize());
}

void CColorDockWidget::changeClosable(bool on)
{ 
	setFeatures(on ? features() | DockWidgetClosable : features() & ~DockWidgetClosable); 
}

void CColorDockWidget::changeMovable(bool on)
{ 
	setFeatures(on ? features() | DockWidgetMovable : features() & ~DockWidgetMovable); 
}

void CColorDockWidget::changeFloatable(bool on)
{ 
	setFeatures(on ? features() | DockWidgetFloatable : features() & ~DockWidgetFloatable); 
}

void CColorDockWidget::changeFloating(bool floating)
{ 
	setFloating(floating); 
}

void CColorDockWidget::allowLeft(bool a)
{ 
	allow(Qt::LeftDockWidgetArea, a);
}

void CColorDockWidget::allowRight(bool a)
{ 
	allow(Qt::RightDockWidgetArea, a); 
}

void CColorDockWidget::allowTop(bool a)
{ 
	allow(Qt::TopDockWidgetArea, a); 
}

void CColorDockWidget::allowBottom(bool a)
{
	allow(Qt::BottomDockWidgetArea, a); 
}

void CColorDockWidget::placeLeft(bool p)
{ 
	place(Qt::LeftDockWidgetArea, p); 
}

void CColorDockWidget::placeRight(bool p)
{ 
	place(Qt::RightDockWidgetArea, p); 
}

void CColorDockWidget::placeTop(bool p)
{ 
	place(Qt::TopDockWidgetArea, p); 
}

void CColorDockWidget::placeBottom(bool p)
{ 
	place(Qt::BottomDockWidgetArea, p); 
}

void CColorDockWidget::changeVerticalTitleBar(bool on)
{
    setFeatures(on ? features() | DockWidgetVerticalTitleBar: features() & ~DockWidgetVerticalTitleBar);
}

