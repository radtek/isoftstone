
#ifndef DBI_UI_WIDGET_H
#define DBI_UI_WIDGET_H

#include <QDialog>

#include "ui_fieldmodel.h"
#include "ui_tablemodel.h"

class CTableModelForm : public QDialog,public Ui_frmTableModel
{
public:

	CTableModelForm(QWidget* parent = 0):QDialog(parent)
	{
		setupUi(this);
	}
};

class CFieldModelForm : public QDialog,public Ui_frmFieldModel
{
public:

	CFieldModelForm(QWidget* parent = 0):QDialog(parent)
	{
		setupUi(this);
	}
};

#endif