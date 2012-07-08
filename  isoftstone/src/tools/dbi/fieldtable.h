
#ifndef FIELD_TABLE_H
#define FIELD_TABLE_H

#include <QString>
#include <QTableWidget>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

#include "uiwidget.h"

class CFieldTable : public QTableWidget
{
	Q_OBJECT
public:

	CFieldTable(QWidget* parent = 0);

public Q_SLOTS:

	void slot_table_changed(int tableid);

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

	FIELD_PARA_STRU toFieldParam(CFieldModelForm* frm);
	void fillForm(CFieldModelForm* frm,const FIELD_PARA_STRU& field);

	int	findIndexOfUserData(QComboBox* combo,int value);
	int	findIndexOfUserData(QComboBox* combo,QString value);
	
private:

	QMenu*	m_popMenu;

	int		m_tableID;
};

#endif