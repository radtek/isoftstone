
#include "datatable.h"
#include "rtdb_api.h"
#include "odb_api.h"
#include "uiwidget.h"

CDataTable::CDataTable(QWidget* parent ):QTableWidget(parent)
{
	m_tableID = 0;
	setAlternatingRowColors(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

	connect(this,SIGNAL(itemDoubleClicked ( QTableWidgetItem * )),this,SLOT(slot_item_double_clicked(QTableWidgetItem *)));
	createPopMenu();

	m_rtTable = new CRtTable;
	m_recordForm = new CRecordForm(m_rtTable,this,this);
}

void CDataTable::createPopMenu()
{
	m_popMenu = new QMenu(this);
	QAction* act = NULL;

	act = new QAction(QObject::tr("添加新记录"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_add_record()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("修改当前记录"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_modify_record()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("删除当前记录"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_delete_record()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("类似克隆记录"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_clone_record()));
	m_popMenu->addAction(act);
}

void CDataTable::slot_table_changed(int tableID)
{
	// 清理表结构，包括表头和数据
	m_tableID = tableID;
	if (m_rtTable->isTableOpen())
	{
		m_rtTable->closeTable();
	}
	m_rtTable->openTableByID(m_tableID);
	clear();

	// 添加表头
	TABLE_PARA_STRU stTable = CODBTable::instance()->getTableParam(tableID);

	QStringList lstHeader;
	QMap<int,FIELD_PARA_STRU> fieldMap = CODBTable::instance()->getFieldMap(tableID);
	QMapIterator<int,FIELD_PARA_STRU > iter(fieldMap);
	int i = 0;
	QVector<FIELD_PARA_STRU> vecFields;
	while(iter.hasNext())
	{
		i++;
		iter.next();
		int fieldID = iter.key();
		const FIELD_PARA_STRU& field = iter.value();
		vecFields.append(field);
		lstHeader.append(field.field_name_chn);
	}
	setColumnCount(lstHeader.count());
	setHorizontalHeaderLabels(lstHeader);

	// 添加数据
	CRtTable table(tableID);
	QVector< QVariantList > vecRows;
	table.getTableRecs(vecRows);
	setRowCount(vecRows.count());
	
	QTableWidgetItem* item  = NULL;
	i = 0;
	foreach (const QVariantList& lstRec,vecRows)
	{
		if (lstRec.count() == fieldMap.count())
		{
			updateRow(i,lstRec);
			i++;
		}
	}

	// 修改记录表单
	m_recordForm->table_changed(tableID);
}

void CDataTable::updateRow(int row,const QVariantList& lstRec)
{
	int j = 0;
	QTableWidgetItem* item  = NULL;
	foreach(const QVariant& rec,lstRec)
	{
		item = new QTableWidgetItem();
		item->setText(rec.toString());
		setItem(row,j++,item);
	}
}

void CDataTable::contextMenuEvent(QContextMenuEvent * event)
{
	if (m_tableID > 2)
	{
		m_popMenu->exec(event->globalPos());
	}
}

void CDataTable::slot_item_double_clicked(QTableWidgetItem * )
{
	slot_modify_record();
}

void CDataTable::slot_add_record()
{
	if(m_recordForm->exec() == QDialog::Accepted)
	{
		QVariantList lstRec = m_recordForm->getValueList();
		m_rtTable->addRecord(m_recordForm->getValueList());

		setRowCount(rowCount()+1);
		updateRow(rowCount()-1,lstRec);
	}
}

void CDataTable::slot_modify_record()
{
	QTableWidgetItem* pitem = item(row(currentItem()),0);
	int keyid = pitem->text().toInt();
	m_recordForm->slot_record_changed(keyid);
	if(m_recordForm->exec() == QDialog::Accepted)
	{
		QVariantList lstRec = m_recordForm->getValueList();
		m_rtTable->updateRecord(keyid,lstRec);

		updateRow(row(pitem),lstRec);
	}
}

void CDataTable::slot_delete_record()
{
	int keyid = item(row(currentItem()),0)->text().toInt();
	m_rtTable->deleteRecord(keyid);

	removeRow(row(currentItem()));
}

void CDataTable::slot_clone_record()
{
	QTableWidgetItem* pitem = item(row(currentItem()),0);
	int keyid = pitem->text().toInt();
	m_recordForm->slot_record_changed(keyid);
	m_recordForm->slot_update_keyid();
	if(m_recordForm->exec() == QDialog::Accepted)
	{
		QVariantList lstRec = m_recordForm->getValueList();
		m_rtTable->addRecord(lstRec);

		setRowCount(rowCount()+1);
		updateRow(rowCount()-1,lstRec);
	}
}

