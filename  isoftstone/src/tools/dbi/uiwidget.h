
#ifndef DBI_UI_WIDGET_H
#define DBI_UI_WIDGET_H

#include <QDialog>

#include "ui_fieldmodel.h"
#include "ui_tablemodel.h"

#include "odb_api.h"

class CTableModelForm : public QDialog,public Ui_frmTableModel
{
	Q_OBJECT

public:

	CTableModelForm(QWidget* parent = 0);

private Q_SLOTS:

		void slot_ok();
		void slot_cancel();
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
	void slot_ok();
	void slot_cancel();
};

#endif