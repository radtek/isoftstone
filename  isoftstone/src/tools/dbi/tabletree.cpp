
#include "tabletree.h"

#include "rtdb_api.h"

CTableTree::CTableTree(QWidget* parent):QTreeWidget(parent)
{
	setAlternatingRowColors(true);
	init();
}

void CTableTree::contextMenuEvent(QContextMenuEvent * event)
{
	
}

void CTableTree::init()
{
	// 读取表信息表中数据，然后显示
	setHeaderLabels(QStringList() << QObject::tr("表号") << QObject::tr("表名") << QObject::tr("中文名") << QObject::tr("NEXT序号") );
	setColumnCount(4);
	m_rootItem = new QTreeWidgetItem(this);
	m_rootItem->setText(0,QObject::tr("关系表"));
	addTopLevelItem(m_rootItem);

	CRtTable table(1);
	const QMap<int,TABLE_PARA_STRU>& tableMap = table.getTableMap();
	QMapIterator<int,TABLE_PARA_STRU> iter(tableMap);
	while(iter.hasNext())
	{
		iter.next();

		const TABLE_PARA_STRU& stTable = iter.value();
		QTreeWidgetItem* item = new QTreeWidgetItem(m_rootItem);
		item->setText(0,QString::number(stTable.table_id));
		item->setText(1,stTable.table_name_eng);
		item->setText(2,stTable.table_name_chn);
		item->setText(3,QString::number(stTable.next_id));

		m_rootItem->addChild(item);
	}
	m_rootItem->setExpanded (true);
}	