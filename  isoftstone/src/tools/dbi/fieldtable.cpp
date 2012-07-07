
#include <QHeaderView>

#include "fieldtable.h"
#include "rtdb_api.h"
#include "odb_api.h"

CFieldTable::CFieldTable(QWidget* parent ):QTableWidget(parent)
{
	setAlternatingRowColors(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	init();
	horizontalHeader()->setVisible(true);
}

void CFieldTable::init()
{
	setColumnCount(14);
	setHorizontalHeaderLabels (QStringList() << QObject::tr("表号")<< QObject::tr("域号")<< QObject::tr("域名")
											 << QObject::tr("域中文名")<< QObject::tr("数据类型")<< QObject::tr("数据长度")
											 << QObject::tr("是否主见")<< QObject::tr("是否为空")<< QObject::tr("显示类型")
											 << QObject::tr("是否外键")<< QObject::tr("引用模式")
											 << QObject::tr("外表名")<< QObject::tr("外域名")<< QObject::tr("引用类型") );

}

void CFieldTable::slot_table_changed(int tableid,QString tableName)
{
	QMap<int,FIELD_PARA_STRU> fieldMap = CODBTable::instance()->getFieldMap(tableid);
	int nRow = fieldMap.count();

	clearContents();
	setRowCount(nRow);
	int i = 0;
	QMapIterator<int,FIELD_PARA_STRU > iter(fieldMap);
	while(iter.hasNext())
	{
		iter.next();
		
		int j = 0;
		int fieldID = iter.key();
		const FIELD_PARA_STRU& field = iter.value();
		
		QTableWidgetItem* item  = NULL;

		item = new QTableWidgetItem();
		item->setText(QString::number(field.table_id));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.field_id));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(field.field_name_eng);
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(field.field_name_chn);
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.data_type));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.data_length));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.is_keyword));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.allow_null));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.display_type));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.ref_flag));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.ref_mode));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.ref_tableno));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.ref_fieldno));
		setItem(i,j++,item);

		item = new QTableWidgetItem();
		item->setText(QString::number(field.ref_display));
		setItem(i,j++,item);

		i++;
	}
}