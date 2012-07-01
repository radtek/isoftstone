
#ifndef MAINWINDOW_VIEW_H
#define MAINWINDOW_VIEW_H

#include <QtGui>

#include "diagramitem.h"
#include "window.h"

class DiagramScene;

class MainWindow_View : public QMainWindow ,public CWindow
{
	Q_OBJECT

public:

	MainWindow_View();

protected:

	DiagramScene*		m_Scene;
	QGraphicsView*		m_View;

private slots:

	void backgroundButtonGroupClicked(QAbstractButton *button);
	void buttonGroupClicked(int id);
	void deleteItem();
	void pointerGroupClicked(int id);
	void bringToFront();
	void sendToBack();
	void itemInserted(DiagramItem *item);
	void textInserted(QGraphicsTextItem *item);
	void currentFontChanged(const QFont &font);
	void fontSizeChanged(const QString &size);
	void sceneScaleChanged(const QString &scale);
	void textColorChanged();
	void itemColorChanged();
	void backColorChanged();
	void lineColorChanged();
	void textButtonTriggered();
	void fillButtonTriggered();
	void backButtonTriggered();
	void lineButtonTriggered();
	void handleFontChange();
	void itemSelected(QGraphicsItem *item);
	void saveFile();
	void openFile();

protected:

	void createToolBox();
	void createActions();
	void createMenus();
	void createToolbars();

	QWidget *createElement(const QString &text, DiagramItem::DiagramType type);

	QAction *exitAction;
	QAction *openAction;
	QAction *saveAction;

	QAction *addAction;
	QAction *deleteAction;

	QAction *toFrontAction;
	QAction *sendBackAction;

	QMenu *fileMenu;
	QMenu *itemMenu;

	QToolBar *textToolBar;
	QToolBar *editToolBar;
	QToolBar *colorToolBar;
	QToolBar *pointerToolbar;

	QComboBox *sceneScaleCombo;
	QComboBox *itemColorCombo;
	QComboBox *textColorCombo;
	QComboBox *fontSizeCombo;
	QFontComboBox *fontCombo;

	QToolBox *toolBox;
	QButtonGroup *buttonGroup;
	QButtonGroup *pointerTypeGroup;
	QButtonGroup *backgroundButtonGroup;
	QToolButton *fontColorToolButton;
	QToolButton *fillColorToolButton;
	QToolButton *backColorToolButton;
	QToolButton *lineColorToolButton;
	QAction *boldAction;
	QAction *underlineAction;
	QAction *italicAction;
	QAction *textAction;
	QAction *fillAction;
	QAction *backAction;
	QAction *lineAction;

	QString path;

};

#endif