
#ifndef DBI_UI_WIDGET_H
#define DBI_UI_WIDGET_H

#include <QWidget>

#include "ui_fieldmodel.h"
#include "ui_tablemodel.h"

class CTableModelForm : public QWidget,public Ui_frmTableModel
{
public:

	CTableModelForm(QWidget* parent = 0):QWidget(parent)
	{
		setupUi(this);
	}
};

class CFieldModelForm : public QWidget,public Ui_frmFieldModel
{
public:

	CFieldModelForm(QWidget* parent = 0):QWidget(parent)
	{
		setupUi(this);
	}
};

#endif