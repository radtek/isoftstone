
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
}

void CDataTable::createPopMenu()
{
	m_popMenu = new QMenu(this);
	QAction* act = NULL;

	act = new QAction(QObject::tr("����¼�¼"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_add_record()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("�޸ĵ�ǰ��¼"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_modify_record()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("ɾ����ǰ��¼"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_delete_record()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("���ƿ�¡��¼"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_clone_record()));
	m_popMenu->addAction(act);
}

void CDataTable::slot_table_changed(int tableID)
{
	// �����ṹ��������ͷ������
	m_tableID = tableID;
	clear();

	// ��ӱ�ͷ
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

	// �������
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
			int j = 0;
			foreach(const QVariant& rec,lstRec)
			{
				item = new QTableWidgetItem();
				item->setText(rec.toString());
				setItem(i,j++,item);
			}
			i++;
		}
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
	CRecordForm frm(this,this);
	frm.slot_table_changed(m_tableID);
	frm.exec();
}

void CDataTable::slot_modify_record()
{
	CRecordForm frm(this,this);
	frm.exec();
}

void CDataTable::slot_delete_record()
{

}

void CDataTable::slot_clone_record()
{
	CRecordForm frm(this,this);
	frm.exec();
}

