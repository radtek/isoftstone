#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QApplication>
#include <QHeaderView>
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QTableView>
#include <QTreeView>
#include <QTreeWidget>
#include <QTextCodec>
#include <QtGui>
#include <QFile>
#include <QVariant>
#include <QPalette>
#include <QMessageBox>
#include <QSortFilterProxyModel>
#include <QDir>

#include "ui_menumgr.h"
#include "commandview.h"
#include "treewidget.h"
#include "treeview.h"

class CMenuMgrWindow : public QWidget
{
    Q_OBJECT

public:
    CMenuMgrWindow();
    ~CMenuMgrWindow();
	void initCommandList();//�����б�
	void initItemList();//ͼԪ�б�
	void initMenuList();//�˵��б�

private slots:
		void onTreeItemChanged(QStandardItem * item);
		//void onTableItemChanged(QStandardItem * item);

private:
	void setupUi();

	CCommandView *tableViewCommand;
	CTreeWidget *treeViewMenu;
	CTreeView *treeViewItem;

	QLabel *labelMenu;
	QLabel *labelItem;
	QLabel *labelCommand;

	QPushButton *buttonOK;
	QPushButton *buttonCancel;

};

#endif // MAINWINDOW_H
