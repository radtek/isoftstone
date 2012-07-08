
#ifndef TABLE_TREE_H
#define TABLE_TREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QAction>

#include "odb_public.h"
#include "uiwidget.h"

#include "tablelist.h"

class CTableTree : public CTableList
{
	Q_OBJECT

public:

	CTableTree(QWidget* parent = 0);

public	Q_SLOTS:

	void slot_item_changed();
	void slot_item_double_clicked();

	void slot_add_table();
	void slot_modify_table();
	void slot_delete_table();
	void slot_clone_table();
	void slot_save_create_to_file();
	void slot_save_insert_to_file();
	void slot_import_from_file();

protected:

	virtual void contextMenuEvent(QContextMenuEvent * event);

private:

	void createPopMenu();

private:

	QMenu*			 m_popMenu;
};

#endif