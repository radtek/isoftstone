
#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

#include "rtdb_api.h"

class CRecordForm;

class CDataTable : public QTableWidget
{
	Q_OBJECT
public:

	CDataTable(QWidget* parent = 0);

public Q_SLOTS:

	void slot_table_changed(int tableid);

	void slot_item_double_clicked(QTableWidgetItem * );

	void slot_add_record();
	void slot_modify_record();
	void slot_delete_record();
	void slot_clone_record();

protected:

	virtual void contextMenuEvent(QContextMenuEvent * event);
	void createPopMenu();

private:

	void updateRow(int row,const QVariantList& lstRec);

private:

	QMenu*	m_popMenu;

	int		m_tableID;

	CRtTable* m_rtTable;

	CRecordForm* m_recordForm;
};

#endif