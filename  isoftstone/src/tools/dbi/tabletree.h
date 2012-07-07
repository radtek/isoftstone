
#ifndef TABLE_TREE_H
#define TABLE_TREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

class CTableTree : public QTreeWidget
{
	Q_OBJECT

public:

	CTableTree(QWidget* parent = 0);

signals:

	void signal_table_changed(int tableid,QString tablename);

protected:

	virtual void contextMenuEvent(QContextMenuEvent * event);

private:

	void init();

private:

	QTreeWidgetItem* m_rootItem;
};

#endif