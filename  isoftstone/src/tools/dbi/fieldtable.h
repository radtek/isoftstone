
#ifndef FIELD_TABLE_H
#define FIELD_TABLE_H

#include <QString>
#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

class CFieldTable : public QTableWidget
{
	Q_OBJECT
public:

	CFieldTable(QWidget* parent = 0);

public Q_SLOTS:

	void slot_table_changed(int tableid,QString tableName);

	void slot_add_field();
	void slot_modify_field();
	void slot_delete_field();
	void slot_clone_field();

	void slot_item_double_clicked(QTableWidgetItem *);

protected:

	virtual void contextMenuEvent(QContextMenuEvent * event);

private:

	void init();
	void createPopMenu();

	void slot_delete_field(int row,int tableID,int fieldID);
	
private:

	QMenu*	m_popMenu;

	int		m_tableID;
};

#endif