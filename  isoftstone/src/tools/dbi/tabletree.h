
#ifndef TABLE_TREE_H
#define TABLE_TREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QMenu>
#include <QAction>

class CTableTree : public QTreeWidget
{
	Q_OBJECT

public:

	CTableTree(QWidget* parent = 0);

signals:

	void signal_table_changed(int tableid,QString tablename);

public	Q_SLOTS:

	void slot_item_changed();
	void slot_item_double_clicked();

	void slot_add_table();
	void slot_modify_table();
	void slot_delete_table();
	void slot_clone_table();
	void slot_save_to_file();


protected:

	virtual void contextMenuEvent(QContextMenuEvent * event);

private:

	void init();
	void createPopMenu();

private:

	QTreeWidgetItem* m_rootItem;
	QMenu*			 m_popMenu;
};

#endif