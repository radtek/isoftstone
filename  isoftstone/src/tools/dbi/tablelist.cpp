
#include "tablelist.h"

CTableList::CTableList(QWidget* parent ):QTreeWidget(parent)
{
	init();
}

void CTableList::init()
{
	// 读取表信息表中数据，然后显示
	setHeaderLabels(QStringList() << QObject::tr("表号") << QObject::tr("表名") << QObject::tr("中文名") << QObject::tr("NEXT序号") );
	setColumnCount(4);
	m_rootItem = new QTreeWidgetItem(this);
	m_rootItem->setText(0,QObject::tr("关系表"));
	addTopLevelItem(m_rootItem);

	const QMap<int,TABLE_PARA_STRU>& tableMap = CODBTable::instance()->getTableMap();
	QMapIterator<int,TABLE_PARA_STRU> iter(tableMap);
	while(iter.hasNext())
	{
		iter.next();

		const TABLE_PARA_STRU& stTable = iter.value();
		m_rootItem->addChild(toItem(stTable));
	}
	m_rootItem->setExpanded (true);
}

QTreeWidgetItem* CTableList::toItem(const TABLE_PARA_STRU& stTable)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(m_rootItem);
	updateItem(item,stTable);
	return item;
}

void CTableList::updateItem(QTreeWidgetItem* item,const TABLE_PARA_STRU& stTable)
{
	item->setText(0,QString::number(stTable.table_id));
	item->setText(1,stTable.table_name_eng);
	item->setText(2,stTable.table_name_chn);
	item->setText(3,QString::number(stTable.next_id));
}


TABLE_PARA_STRU CTableList::toTableParam(CTableModelForm* frm)
{
	TABLE_PARA_STRU table;
	table.table_id = frm->line_tableno->text().toInt();
	table.table_name_eng = frm->line_enname->text();
	table.table_name_chn = frm->line_cnname->text();
	table.next_id = frm->line_nextid->text().toInt();

	return table;
}

// 只读表列表

CRtTableView::CRtTableView(QWidget* parent ):CTableList(parent)
{
	connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem * , QTreeWidgetItem* )),this,SLOT(slot_item_double_clicked()));
}

void CRtTableView::slot_item_double_clicked()
{
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		int tableID = item->text(0).toInt();
		emit signal_table_changed(tableID);
	}
}