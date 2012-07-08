
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "uiwidget.h"

CTableModelForm::CTableModelForm(QWidget* parent ):QDialog(parent)
{
	setupUi(this);

	connect(btn_ok,SIGNAL(clicked ()),this,SLOT(accept()));
	connect(btn_cancel,SIGNAL(clicked ()),this,SLOT(reject()));
}

CFieldModelForm::CFieldModelForm(QWidget* parent ):QDialog(parent)
{
	setupUi(this);
	initCombo();

	group_ref->setEnabled(false);

	connect(cb_foreign,SIGNAL(stateChanged ( int  )),this,SLOT(slot_foreign_changed(int)));
	connect(combo_ref_table,SIGNAL(currentIndexChanged ( int  )),this,SLOT(slot_table_changed(int)));
	connect(btn_ok,SIGNAL(clicked ()),this,SLOT(accept()));
	connect(btn_cancel,SIGNAL(clicked ()),this,SLOT(reject()));
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
void CFieldModelForm::slot_table_changed(int index)
{
	int tableID = combo_ref_table->itemData(index).toInt();
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

CRecordForm::CRecordForm(QTableWidget* datatable,QWidget* parent ):QDialog(parent)
{
	m_dataTable = datatable;
	m_recordTable = new QTableWidget(this);
	m_recordTable->setColumnCount(1);
	m_recordTable->horizontalHeader()->hide();
	
	resize(600,600);
	m_recordTable->setColumnWidth(0,540);

	QVBoxLayout *layout = new QVBoxLayout(this);

	QHBoxLayout * layout1 = new QHBoxLayout(this);
	btn_previous = new QPushButton(QObject::tr("上一记录"),this);
	btn_next = new QPushButton(QObject::tr("下一记录"),this);
	btn_first = new QPushButton(QObject::tr("首记录"),this);
	btn_last = new QPushButton(QObject::tr("末记录"),this);
	layout1->addWidget(btn_first);
	layout1->addWidget(btn_previous);
	layout1->addWidget(btn_next);
	layout1->addWidget(btn_last);

	layout->addLayout(layout1);


	layout->addWidget(m_recordTable);

	QHBoxLayout * layout2 = new QHBoxLayout(this);
	btn_ok = new QPushButton(QObject::tr("确认"),this);
	btn_cancel = new QPushButton(QObject::tr("取消"),this);
	layout2->addWidget(btn_ok);
	layout2->addWidget(btn_cancel);
	layout->addLayout(layout2);

	connect(btn_ok,SIGNAL(clicked ()),this,SLOT(accept()));
	connect(btn_cancel,SIGNAL(clicked ()),this,SLOT(reject()));

	setLayout(layout);
	setWindowTitle(QObject::tr("记录编辑器"));
}

void CRecordForm::slot_table_changed(int tableID)
{
	m_tableID = tableID;
	QStringList lstHeader = CODBTable::instance()->getHeaerList(tableID);
	m_recordTable->clear();
	m_recordTable->setRowCount(lstHeader.count());
	m_recordTable->setVerticalHeaderLabels(lstHeader);
}

void CRecordForm::slot_record_changed(int keyid)
{
	
}

QVariantList CRecordForm::getValueList()
{
	QVariantList lstValue;
	QTableWidgetItem* pItem = NULL;
	for (int i = 0; i < m_recordTable->rowCount();i++)
	{
		pItem = m_recordTable->item(i,0);
		if (pItem)
		{
			lstValue.append(pItem->text());
		}
	}
	return lstValue;
}