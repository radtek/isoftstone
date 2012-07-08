
#include "datatable.h"
#include "rtdb_api.h"
#include "odb_api.h"

CDataTable::CDataTable(QWidget* parent ):QTableWidget(parent)
{
	setAlternatingRowColors(true);
	setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void CDataTable::slot_table_changed(int tableID)
{
	// 清理表结构，包括表头和数据

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