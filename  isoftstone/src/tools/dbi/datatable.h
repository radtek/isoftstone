
#ifndef DATA_TABLE_H
#define DATA_TABLE_H

#include <QTableWidget>

class CDataTable : public QTableWidget
{
	Q_OBJECT
public:

	CDataTable(QWidget* parent = 0);

public Q_SLOTS:

	void slot_table_changed(int tableid);
};

#endif