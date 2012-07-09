
#ifndef TABLE_LIST_H
#define TABLE_LIST_H

#include <QTreeWidget>
#include <QTreeWidgetItem>

#include "odb_public.h"
#include "uiwidget.h"

class CTableList : public QTreeWidget
{
	Q_OBJECT

public:

	CTableList(QWidget* parent = 0);

	void reload();

signals:
	void signal_table_changed(int tableid);

protected:

	void init();
	QTreeWidgetItem* toItem(const TABLE_PARA_STRU& table);
	void updateItem(QTreeWidgetItem* item,const TABLE_PARA_STRU& stTable);
	TABLE_PARA_STRU toTableParam(CTableModelForm* frm);

protected:

	QTreeWidgetItem* m_rootItem;
};

class CRtTableView :public CTableList
{
	Q_OBJECT
public:

	CRtTableView(QWidget* parent = 0);

public	Q_SLOTS:

	void slot_item_double_clicked();

};
#endif