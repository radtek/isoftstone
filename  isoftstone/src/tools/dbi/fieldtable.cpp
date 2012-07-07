
#include <QHeaderView>

#include "fieldtable.h"
#include "rtdb_api.h"
#include "odb_api.h"
#include "uiwidget.h"

CFieldTable::CFieldTable(QWidget* parent ):QTableWidget(parent)
{
	setAlternatingRowColors(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(this,SIGNAL(itemDoubleClicked ( QTableWidgetItem * )),this,SLOT(slot_item_double_clicked(QTableWidgetItem *)));
	createPopMenu();
	init();
}

void CFieldTable::createPopMenu()
{
	m_popMenu = new QMenu(this);
	QAction* act = NULL;

	act = new QAction(QObject::tr("添加新域"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_add_field()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("修改当前域"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_modify_field()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("删除当前域"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_delete_field()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("类似克隆域"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_clone_field()));
	m_popMenu->addAction(act);
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

void CFieldTable::contextMenuEvent(QContextMenuEvent * event)
{
	m_popMenu->exec(event->globalPos());
}

void CFieldTable::slot_item_double_clicked(QTableWidgetItem * )
{
	slot_modify_field();
}

void CFieldTable::slot_add_field()
{
	CFieldModelForm frm;
	frm.exec();
}

void CFieldTable::slot_modify_field()
{
	CFieldModelForm frm;
	frm.exec();
}

void CFieldTable::slot_delete_field()
{
	QTableWidgetItem* citem = currentItem();
	if (citem)
	{
		int nrow = row(citem);
		int tableID = item(nrow,0)->text().toInt();
		int fieldID = item(nrow,1)->text().toInt();

		slot_delete_field(nrow,tableID,fieldID);
	}
}

void CFieldTable::slot_delete_field(int nrow,int tableID,int fieldID)
{
	// 从当前表删除
	removeRow(nrow);
	// 从数据库删除
	CODBTable::instance()->deleteField(tableID,fieldID);
}

void CFieldTable::slot_clone_field()
{
	CFieldModelForm frm;
	frm.exec();
}