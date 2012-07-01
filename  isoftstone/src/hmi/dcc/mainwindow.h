#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

#include "toolbar.h"
#include "pluginwindow.h"
#include "view.h"
#include "scene.h"

class QtToolBarManager;

class CMainWindow : public QMainWindow
{
	Q_OBJECT

public:
	CMainWindow();

	void iniMenuAndTool(CView* pView,CGraphicsScene* pScene);

private:
	
	void	createMenus();
	void	createToolBars();
	void	createToolBarManager();
	void	readSettings();
	void	writeSettings();
	
public slots:
	void	openFile(const QString &path = QString());
	void	openElementFile();
	void	openBayFile();
	void	openHomePage();
	void	exportImage();
	void	openSourceFile();
	void	setFullScreen();
	void	telnetControl();
	void	setToolbarVisible(bool bHide);

	void	configureToolBars();
	void	saveToolBars();
	void	restoreToolBars();

private:

	QAction* actionHomePage;
	QAction* quitAction;
	QToolBar *fileToolBar;
	QToolBar *editToolBar;

private:
	
	bool		m_bFullScreen;
	CView *		m_view;
	CGraphicsScene*	m_scene;
	QString		m_currentPath;

	CPluginWindow m_pluginWindow;

	QtToolBarManager *toolBarManager;
};

#endif