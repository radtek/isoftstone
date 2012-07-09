
#ifndef DBI_UI_WIDGET_H
#define DBI_UI_WIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QTableWidget>
#include <QVariantList>

#include "ui_fieldmodel.h"
#include "ui_tablemodel.h"

#include "odb_api.h"
#include "rtdb_api.h"

class CTableModelForm : public QDialog,public Ui_frmTableModel
{
	Q_OBJECT

public:

	CTableModelForm(QWidget* parent = 0);

};

class CFieldModelForm : public QDialog,public Ui_frmFieldModel
{
	Q_OBJECT
public:

	CFieldModelForm(QWidget* parent = 0);

	void initCombo();

private Q_SLOTS:

	void slot_foreign_changed(int);
	void slot_table_changed(int);
};

class CRecordForm : public QDialog
{
	Q_OBJECT
public:

	CRecordForm(CRtTable* rtTable,QTableWidget* datatable,QWidget* parent = 0);

	QVariantList getValueList();

	void table_changed(int tableID);

public Q_SLOTS:

	void slot_record_changed(int keyid);
	void slot_update_keyid();
private:

	QTableWidget* m_recordTable;
	QTableWidget* m_dataTable;

	QPushButton*  btn_ok;
	QPushButton*  btn_cancel;

	QPushButton*  btn_previous;
	QPushButton*  btn_next;
	QPushButton*  btn_first;
	QPushButton*  btn_last;

	int		m_tableID;
	int		m_keyID;

	CRtTable*	m_rtTable;
};

#endif