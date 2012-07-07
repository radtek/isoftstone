
#include "uiwidget.h"

CTableModelForm::CTableModelForm(QWidget* parent ):QDialog(parent)
{
	setupUi(this);

	connect(btn_ok,SIGNAL(clicked ()),this,SLOT(slot_ok()));
	connect(btn_cancel,SIGNAL(clicked ()),this,SLOT(slot_cancel()));
}

void CTableModelForm::slot_ok()
{
	accept();
}

void CTableModelForm::slot_cancel()
{
	reject();
}

CFieldModelForm::CFieldModelForm(QWidget* parent ):QDialog(parent)
{
	setupUi(this);
	initCombo();

	group_ref->setEnabled(false);

	connect(cb_foreign,SIGNAL(stateChanged ( int  )),this,SLOT(slot_foreign_changed(int)));
	connect(combo_ref_table,SIGNAL(currentIndexChanged ( int  )),this,SLOT(slot_table_changed(int)));
	connect(btn_ok,SIGNAL(clicked ()),this,SLOT(slot_ok()));
	connect(btn_cancel,SIGNAL(clicked ()),this,SLOT(slot_cancel()));
}

void CFieldModelForm::initCombo()
{
	combo_datatype->addItem("INTEGER",C_INT_TYPE);
	combo_datatype->addItem("VARCHAR",C_STRING_TYPE);
	combo_datatype->addItem("BOOLEAN",C_BOOLEAN_TYPE);
	combo_datatype->addItem("FLOAT",C_FLOAT_TYPE);
	combo_datatype->addItem("REAL",C_DOUBLE_TYPE);

	combo_display_datatype->addItem("STRING",C_STRING_TYPE);

	const QMap<int,TABLE_PARA_STRU>& tableMap = CODBTable::instance()->getTableMap();
	QMapIterator<int,TABLE_PARA_STRU> iter(tableMap);
	while(iter.hasNext())
	{
		iter.next();

		const TABLE_PARA_STRU& stTable = iter.value();
		combo_ref_table->addItem(stTable.table_name_eng,stTable.table_id);
	}

}

void CFieldModelForm::slot_foreign_changed(int)
{
	if (cb_foreign->isChecked())
	{
		group_ref->setEnabled(true);
	}
	else
	{
		group_ref->setEnabled(false);
	}
}
void CFieldModelForm::slot_table_changed(int tableID)
{
	QMap<int,FIELD_PARA_STRU> fieldMap = CODBTable::instance()->getFieldMap(tableID);
	combo_ref_field->clear();
	combo_display_column->clear();

	QMapIterator<int,FIELD_PARA_STRU > iter(fieldMap);
	while(iter.hasNext())
	{
		iter.next();

		int fieldID = iter.key();
		const FIELD_PARA_STRU& field = iter.value();
		combo_ref_field->addItem(field.field_name_eng,field.field_id);
		combo_display_column->addItem(field.field_name_eng,field.field_id);
	}
}

void CFieldModelForm::slot_ok()
{
	accept();
}

void CFieldModelForm::slot_cancel()
{
	reject();
}