
#ifndef FIELD_TABLE_H
#define FIELD_TABLE_H

#include <QString>
#include <QTableWidget>

class CFieldTable : public QTableWidget
{
	Q_OBJECT
public:

	CFieldTable(QWidget* parent = 0);

public Q_SLOTS:

	void slot_table_changed(int tableid,QString tableName);

private:

	void init();
	
};

#endif