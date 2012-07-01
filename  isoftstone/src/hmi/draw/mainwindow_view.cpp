
#include "mainwindow_view.h"

#include "resource.h"
#include "diagramitem.h"
#include "diagramscene.h"
#include "diagramtextitem.h"
#include "arrow.h"

const int InsertTextButton = 10;

MainWindow_View::MainWindow_View()
{
	createActions();
	createToolBox();
	createMenus();
	createToolbars();

	m_Scene = new DiagramScene(itemMenu, this);
	m_Scene->setSceneRect(QRectF(0, 0, 500, 500));
	connect(m_Scene, SIGNAL(itemInserted(DiagramItem*)),this, SLOT(itemInserted(DiagramItem*)));
	connect(m_Scene, SIGNAL(textInserted(QGraphicsTextItem*)),this, SLOT(textInserted(QGraphicsTextItem*)));
	connect(m_Scene, SIGNAL(itemSelected(QGraphicsItem*)),this, SLOT(itemSelected(QGraphicsItem*)));

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(toolBox);
	m_View = new QGraphicsView(m_Scene);
	layout->addWidget(m_View);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	fillButtonTriggered();
	setCentralWidget(widget);
	setWindowTitle(tr("Diagramscene"));
	setUnifiedTitleAndToolBarOnMac(true);
}

void MainWindow_View::backgroundButtonGroupClicked(QAbstractButton *button)
{
	QList<QAbstractButton *> buttons = backgroundButtonGroup->buttons();
	foreach (QAbstractButton *myButton, buttons) 
	{
		if (myButton != button)
			button->setChecked(false);
	}
	QString text = button->text();
	if (text == tr("Blue Grid"))
		m_Scene->setBackgroundBrush(QPixmap(":/images/background1.png"));
	else if (text == tr("White Grid"))
		m_Scene->setBackgroundBrush(QPixmap(":/images/background2.png"));
	else if (text == tr("Gray Grid"))
		m_Scene->setBackgroundBrush(QPixmap(":/images/background3.png"));
	else
		m_Scene->setBackgroundBrush(QPixmap(":/images/background4.png"));

	m_Scene->update();
	m_View->update();
}

void MainWindow_View::buttonGroupClicked(int id)
{
	QList<QAbstractButton *> buttons = buttonGroup->buttons();
	foreach (QAbstractButton *button, buttons) 
	{
		if (buttonGroup->button(id) != button)
			button->setChecked(false);
	}
	if (id == InsertTextButton)
	{
		m_Scene->setMode(DiagramScene::InsertText);
	} 
	else 
	{
		m_Scene->setItemType(DiagramItem::DiagramType(id));
		m_Scene->setMode(DiagramScene::InsertItem);
	}
}

void MainWindow_View::deleteItem()
{
	foreach (QGraphicsItem *item, m_Scene->selectedItems()) 
	{
		if (item->type() == Arrow::Type) 
		{
			m_Scene->removeItem(item);
			Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
			arrow->startItem()->removeArrow(arrow);
			arrow->endItem()->removeArrow(arrow);
			delete item;
		}
	}

	foreach (QGraphicsItem *item, m_Scene->selectedItems())
	{
		if (item->type() == DiagramItem::Type)
		{
			qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
		}
		m_Scene->removeItem(item);
		delete item;
	}
}

void MainWindow_View::pointerGroupClicked(int)
{
	m_Scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow_View::bringToFront()
{
	if (m_Scene->selectedItems().isEmpty())
		return;

	QGraphicsItem *selectedItem = m_Scene->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems)
	{
		if (item->zValue() >= zValue && item->type() == DiagramItem::Type)
		{
			zValue = item->zValue() + 0.1;
		}
	}
	selectedItem->setZValue(zValue);
}

void MainWindow_View::sendToBack()
{
	if (m_Scene->selectedItems().isEmpty())
		return;

	QGraphicsItem *selectedItem = m_Scene->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems) 
	{
		if (item->zValue() <= zValue && item->type() == DiagramItem::Type)
		{
			zValue = item->zValue() - 0.1;
		}
	}
	selectedItem->setZValue(zValue);
}

void MainWindow_View::itemInserted(DiagramItem *item)
{
	pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
	m_Scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
	buttonGroup->button(int(item->diagramType()))->setChecked(false);
}

void MainWindow_View::textInserted(QGraphicsTextItem *)
{
	buttonGroup->button(InsertTextButton)->setChecked(false);
	m_Scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow_View::currentFontChanged(const QFont &)
{
	handleFontChange();
}

void MainWindow_View::fontSizeChanged(const QString &)
{
	handleFontChange();
}

void MainWindow_View::sceneScaleChanged(const QString &scale)
{
	double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
	QMatrix oldMatrix = m_View->matrix();
	m_View->resetMatrix();
	m_View->translate(oldMatrix.dx(), oldMatrix.dy());
	m_View->scale(newScale, newScale);
}

void MainWindow_View::textColorChanged()
{
	textAction = qobject_cast<QAction *>(sender());
	fontColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/textpointer.png",
								qVariantValue<QColor>(textAction->data())));
	textButtonTriggered();
}

void MainWindow_View::itemColorChanged()
{
	fillAction = qobject_cast<QAction *>(sender());
	fillColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/floodfill.png",
								qVariantValue<QColor>(fillAction->data())));
	fillButtonTriggered();
}

void MainWindow_View::backColorChanged()
{
	fillAction = qobject_cast<QAction *>(sender());
	fillColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/floodfill.png",
		qVariantValue<QColor>(fillAction->data())));
	backButtonTriggered();
}

void MainWindow_View::lineColorChanged()
{
	lineAction = qobject_cast<QAction *>(sender());
	lineColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/linecolor.png",
								qVariantValue<QColor>(lineAction->data())));
	lineButtonTriggered();
}

void MainWindow_View::textButtonTriggered()
{
	m_Scene->setTextColor(qVariantValue<QColor>(textAction->data()));
}

void MainWindow_View::fillButtonTriggered()
{
	m_Scene->setItemColor(qVariantValue<QColor>(fillAction->data()));
}

void MainWindow_View::backButtonTriggered()
{
	QColor color = qVariantValue<QColor>(fillAction->data());
	m_Scene->setBackgroundBrush(QBrush(color,Qt::Dense1Pattern));
}

void MainWindow_View::lineButtonTriggered()
{
	m_Scene->setLineColor(qVariantValue<QColor>(lineAction->data()));
}

void MainWindow_View::openFile()
{
	QString fileName;
	if (path.isNull())
		fileName = QFileDialog::getOpenFileName(this, tr("打开文件"),path, "G files(*.g);;DAT files(*.dat);;SVG files (*.svg )");
	else
		fileName = path;

	if (!fileName.isEmpty()) 
	{
		QFile file(fileName);
		if (!file.exists())
		{
			QMessageBox::critical(this, tr("打开文件错误"),tr("不能打开 '%1'.").arg(fileName));
			return;
		}
	}
	if (QFileInfo(fileName).suffix() == "g")
	{
		m_Scene->openGFile(fileName);
	}
	if (QFileInfo(fileName).suffix() == "svg")
	{
		m_View->resetTransform();
		m_Scene->openSvg(fileName);
	}
	else if (QFileInfo(fileName).suffix() == "dat")
	{
		m_Scene->openFile(fileName);
	}

}

void MainWindow_View::saveFile()
{
	QString newPath = QFileDialog::getSaveFileName(this, tr("Save File"),path, tr("DAT files(*.dat);;SVG files (*.svg);;Png files (*.png)"));

	if (newPath.isEmpty())
	{
		QMessageBox::information(this,"error","file is null");
	}

	if (QFileInfo(newPath).suffix() == "svg")
	{
		m_Scene->saveSvg(newPath);
	}
	else if (QFileInfo(newPath).suffix() == "dat")
	{
		m_Scene->saveFile(newPath);
	}
	else if (QFileInfo(newPath).suffix() == "png")
	{
		m_Scene->saveImage(newPath);
	}

}

void MainWindow_View::handleFontChange()
{
	QFont font = fontCombo->currentFont();
	font.setPointSize(fontSizeCombo->currentText().toInt());
	font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
	font.setItalic(italicAction->isChecked());
	font.setUnderline(underlineAction->isChecked());

	m_Scene->setFont(font);
}

void MainWindow_View::itemSelected(QGraphicsItem *item)
{
	DiagramTextItem *textItem = qgraphicsitem_cast<DiagramTextItem *>(item);

	QFont font = textItem->font();
	QColor color = textItem->defaultTextColor();
	fontCombo->setCurrentFont(font);
	fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
	boldAction->setChecked(font.weight() == QFont::Bold);
	italicAction->setChecked(font.italic());
	underlineAction->setChecked(font.underline());
}


void MainWindow_View::createToolBox()
{
	buttonGroup = new QButtonGroup(this);
	buttonGroup->setExclusive(false);
	connect(buttonGroup, SIGNAL(buttonClicked(int)),this, SLOT(buttonGroupClicked(int)));
	QGridLayout *layout = new QGridLayout;
	layout->addWidget(createElement(tr("Conditional"),DiagramItem::Conditional), 0, 0);
	layout->addWidget(createElement(tr("Process"),DiagramItem::Step),0, 1);
	layout->addWidget(createElement(tr("Input/Output"),DiagramItem::Io), 1, 0);

	QToolButton *textButton = new QToolButton;
	textButton->setCheckable(true);
	buttonGroup->addButton(textButton, InsertTextButton);
	textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png").scaled(30, 30)));
	textButton->setIconSize(QSize(50, 50));
	QGridLayout *textLayout = new QGridLayout;
	textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
	textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
	QWidget *textWidget = new QWidget;
	textWidget->setLayout(textLayout);
	layout->addWidget(textWidget, 1, 1);

	layout->setRowStretch(3, 10);
	layout->setColumnStretch(2, 10);

	QWidget *itemWidget = new QWidget;
	itemWidget->setLayout(layout);

	backgroundButtonGroup = new QButtonGroup(this);
	connect(backgroundButtonGroup, SIGNAL(buttonClicked(QAbstractButton*)),this, SLOT(backgroundButtonGroupClicked(QAbstractButton*)));

	QGridLayout *backgroundLayout = new QGridLayout;
	backgroundLayout->addWidget(CResource::createCellWidget(backgroundButtonGroup,tr("Blue Grid"),
		":/images/background1.png"), 0, 0);
	backgroundLayout->addWidget(CResource::createCellWidget(backgroundButtonGroup,tr("White Grid"),
		":/images/background2.png"), 0, 1);
	backgroundLayout->addWidget(CResource::createCellWidget(backgroundButtonGroup,tr("Gray Grid"),
		":/images/background3.png"), 1, 0);
	backgroundLayout->addWidget(CResource::createCellWidget(backgroundButtonGroup,tr("No Grid"),
		":/images/background4.png"), 1, 1);

	backgroundLayout->setRowStretch(2, 10);
	backgroundLayout->setColumnStretch(2, 10);

	QWidget *backgroundWidget = new QWidget;
	backgroundWidget->setLayout(backgroundLayout);


	toolBox = new QToolBox;
	toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
	toolBox->setMinimumWidth(itemWidget->sizeHint().width());
	toolBox->addItem(itemWidget, tr("Basic Flowchart Shapes"));
	toolBox->addItem(backgroundWidget, tr("Backgrounds"));
}

void MainWindow_View::createActions()
{
	SAction stAction;
	stAction.image = ":/images/bringtofront.png";
	stAction.text = tr("Bring to &Front");
	stAction.shortCut = "Ctrl+F";
	stAction.tip = tr("Bring item to front");
	stAction.parent = this;
	stAction.receiver = this;
	stAction.slot = SLOT(bringToFront());
	toFrontAction = createAction(stAction);

	stAction.image = ":/images/sendtoback.png";
	stAction.text = tr("Bring to &Back");
	stAction.shortCut = "Ctrl+B";
	stAction.tip = tr("Bring item to back");
	stAction.parent = this;
	stAction.receiver = this;
	stAction.slot = SLOT(sendToBack());
	sendBackAction = createAction(stAction);

	stAction.image = ":/images/delete.png";
	stAction.text = tr("&Delete");
	stAction.shortCut = "Delete";
	stAction.tip = tr("Delete item from diagram");
	stAction.parent = this;
	stAction.receiver = this;
	stAction.slot = SLOT(deleteItem());
	deleteAction = createAction(stAction);

	exitAction = new QAction(tr("E&xit"), this);
	exitAction->setShortcuts(QKeySequence::Quit);
	exitAction->setStatusTip(tr("Quit Scenediagram example"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

	openAction = new QAction(tr("O&pen"), this);
	openAction->setShortcuts(QKeySequence::Open);
	openAction->setStatusTip(tr("open"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));

	saveAction = new QAction(tr("S&ave"), this);
	saveAction->setShortcuts(QKeySequence::Save);
	saveAction->setStatusTip(tr("save"));
	connect(saveAction, SIGNAL(triggered()), this, SLOT(saveFile()));

	boldAction = new QAction(tr("Bold"), this);
	boldAction->setCheckable(true);
	QPixmap pixmap(":/images/bold.png");
	boldAction->setIcon(QIcon(pixmap));
	boldAction->setShortcut(tr("Ctrl+B"));
	connect(boldAction, SIGNAL(triggered()),this, SLOT(handleFontChange()));

	italicAction = new QAction(QIcon(":/images/italic.png"),tr("Italic"), this);
	italicAction->setCheckable(true);
	italicAction->setShortcut(tr("Ctrl+I"));
	connect(italicAction, SIGNAL(triggered()),this, SLOT(handleFontChange()));

	underlineAction = new QAction(QIcon(":/images/underline.png"),tr("Underline"), this);
	underlineAction->setCheckable(true);
	underlineAction->setShortcut(tr("Ctrl+U"));
	connect(underlineAction, SIGNAL(triggered()),this, SLOT(handleFontChange()));

}

void MainWindow_View::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addAction(exitAction);
	

	itemMenu = menuBar()->addMenu(tr("&Item"));
	itemMenu->addAction(deleteAction);
	itemMenu->addSeparator();
	itemMenu->addAction(toFrontAction);
	itemMenu->addAction(sendBackAction);
}

void MainWindow_View::createToolbars()
{
	editToolBar = addToolBar(tr("Edit"));
	editToolBar->addAction(deleteAction);
	editToolBar->addAction(toFrontAction);
	editToolBar->addAction(sendBackAction);

	fontCombo = new QFontComboBox();
	connect(fontCombo, SIGNAL(currentFontChanged(QFont)),this, SLOT(currentFontChanged(QFont)));

	fontSizeCombo = new QComboBox;
	fontSizeCombo->setEditable(true);
	for (int i = 8; i < 30; i = i + 2)
	{
		fontSizeCombo->addItem(QString().setNum(i));
	}
	QIntValidator *validator = new QIntValidator(2, 64, this);
	fontSizeCombo->setValidator(validator);
	connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),this, SLOT(fontSizeChanged(QString)));

	fontColorToolButton = new QToolButton;
	fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	fontColorToolButton->setMenu(CResource::createColorMenu(this,SLOT(textColorChanged()), Qt::black));
	textAction = fontColorToolButton->menu()->defaultAction();
	fontColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
	fontColorToolButton->setAutoFillBackground(true);
	connect(fontColorToolButton, SIGNAL(clicked()),this, SLOT(textButtonTriggered()));

	fillColorToolButton = new QToolButton;
	fillColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	fillColorToolButton->setMenu(CResource::createColorMenu(this,SLOT(itemColorChanged()),Qt::white));
	fillAction = fillColorToolButton->menu()->defaultAction();
	fillColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/floodfill.png", Qt::white));
	connect(fillColorToolButton, SIGNAL(clicked()),this, SLOT(fillButtonTriggered()));

	lineColorToolButton = new QToolButton;
	lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	lineColorToolButton->setMenu(CResource::createColorMenu(this,SLOT(lineColorChanged()),Qt::black));
	lineAction = lineColorToolButton->menu()->defaultAction();
	lineColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/linecolor.png", Qt::black));
	connect(lineColorToolButton, SIGNAL(clicked()),this, SLOT(lineButtonTriggered()));

	backColorToolButton = new QToolButton;
	backColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
	backColorToolButton->setMenu(CResource::createColorMenu(this,SLOT(backColorChanged()),Qt::black));
	backAction = backColorToolButton->menu()->defaultAction();
	backColorToolButton->setIcon(CResource::createColorToolButtonIcon(":/images/floodfill.png", Qt::black));
	connect(backColorToolButton, SIGNAL(clicked()),this, SLOT(backButtonTriggered()));

	textToolBar = addToolBar(tr("Font"));
	textToolBar->addWidget(fontCombo);
	textToolBar->addWidget(fontSizeCombo);
	textToolBar->addAction(boldAction);
	textToolBar->addAction(italicAction);
	textToolBar->addAction(underlineAction);

	colorToolBar = addToolBar(tr("Color"));
	colorToolBar->addWidget(fontColorToolButton);
	colorToolBar->addWidget(fillColorToolButton);
	colorToolBar->addWidget(lineColorToolButton);
	colorToolBar->addWidget(backColorToolButton);

	QToolButton *pointerButton = new QToolButton;
	pointerButton->setCheckable(true);
	pointerButton->setChecked(true);
	pointerButton->setIcon(QIcon(":/images/pointer.png"));
	QToolButton *linePointerButton = new QToolButton;
	linePointerButton->setCheckable(true);
	linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

	pointerTypeGroup = new QButtonGroup(this);
	pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
	pointerTypeGroup->addButton(linePointerButton,
		int(DiagramScene::InsertLine));
	connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),this, SLOT(pointerGroupClicked(int)));

	sceneScaleCombo = new QComboBox;
	QStringList scales;
	scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
	sceneScaleCombo->addItems(scales);
	sceneScaleCombo->setCurrentIndex(2);
	connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),this, SLOT(sceneScaleChanged(QString)));

	pointerToolbar = addToolBar(tr("Pointer type"));
	pointerToolbar->addWidget(pointerButton);
	pointerToolbar->addWidget(linePointerButton);
	pointerToolbar->addWidget(sceneScaleCombo);
}


QWidget *MainWindow_View::createElement(const QString &text, DiagramItem::DiagramType type)
{
	DiagramItem item(type, itemMenu);
	return CResource::createCellWidget(buttonGroup,text,item.image(),int(type));
}



