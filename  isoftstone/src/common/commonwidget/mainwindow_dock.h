
#ifndef MAINWINDOW_DOCK_H
#define MAINWINDOW_DOCK_H

#include "customdef.h"

class EXPORT_WIDGET QMainWindow_Dock : public QMainWindow
{
    Q_OBJECT

public:
    QMainWindow_Dock(QWidget *parent = 0);

public slots:
    void saveLayout();
    void loadLayout();
    void setCorner(int id);

    void createDockWidget();
	void showDockWidget();
	void addWidgetToDock(QWidget* wid,Qt::DockWidgetArea area);
    void destroyDockWidget(QAction *action);
	void destroyAllDock();

protected:

	 void setupMenuBar();
private:
   
    void setupDockMenus();
	void createDockWidgets(const QString& strFile);
	void saveDockWidgets(const QString& strFile);
	Qt::DockWidgetArea getDockArea(QString strDock);

private:

	QMenu *			m_destroyDockMenu;
	QSignalMapper *	m_actionMapper;
	QList<QDockWidget*> m_lstDockWidgets;
	bool			m_bShowDock;
	QAction*		m_showDockAction;
};


#endif
