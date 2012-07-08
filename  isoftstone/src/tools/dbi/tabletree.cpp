
#include <QContextMenuEvent>

#include "tabletree.h"
#include "uiwidget.h"
#include "rtdb_api.h"
#include "odb_api.h"

CTableTree::CTableTree(QWidget* parent):QTreeWidget(parent)
{
	setAlternatingRowColors(true);

	connect(this,SIGNAL(currentItemChanged ( QTreeWidgetItem * , QTreeWidgetItem *  )),this,SLOT(slot_item_changed()));
	connect(this,SIGNAL(itemDoubleClicked (QTreeWidgetItem * , int )),this,SLOT(slot_item_double_clicked()));
	createPopMenu();
	init();
}

void CTableTree::createPopMenu()
{
	m_popMenu = new QMenu(this);
	QAction* act = NULL;

	act = new QAction(QObject::tr("添加新表"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_add_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("修改表"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_modify_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("删除表"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_delete_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("克隆表"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_clone_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("保存到文件"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_save_to_file()));
	m_popMenu->addAction(act);
}

void CTableTree::init()
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

QTreeWidgetItem* CTableTree::toItem(const TABLE_PARA_STRU& stTable)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(m_rootItem);
	item->setText(0,QString::number(stTable.table_id));
	item->setText(1,stTable.table_name_eng);
	item->setText(2,stTable.table_name_chn);
	item->setText(3,QString::number(stTable.next_id));

	return item;
}

void CTableTree::updateItem(QTreeWidgetItem* item,const TABLE_PARA_STRU& stTable)
{
	item->setText(0,QString::number(stTable.table_id));
	item->setText(1,stTable.table_name_eng);
	item->setText(2,stTable.table_name_chn);
	item->setText(3,QString::number(stTable.next_id));
}

TABLE_PARA_STRU CTableTree::toTableParam(CTableModelForm* frm)
{
	TABLE_PARA_STRU table;
	table.table_id = frm->line_tableno->text().toInt();
	table.table_name_eng = frm->line_enname->text();
	table.table_name_chn = frm->line_cnname->text();
	table.next_id = frm->line_nextid->text().toInt();

	return table;
}

void CTableTree::contextMenuEvent(QContextMenuEvent * event)
{
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		m_popMenu->exec(event->globalPos());
	}
}

void CTableTree::slot_item_changed()
{
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		int tableID = item->text(0).toInt();
		QString tableName = item->text(1);

		emit signal_table_changed(tableID,tableName);
	}
}

void CTableTree::slot_item_double_clicked()
{
	slot_modify_table();
}

void CTableTree::slot_add_table()
{
	CTableModelForm frm;
	frm.line_tableno->setText(QString::number( CODBTable::instance()->getNextID(1)));
	if(frm.exec() == QDialog::Accepted)
	{
		TABLE_PARA_STRU table = toTableParam(&frm);
		CODBTable::instance()->addTable(table);
		m_rootItem->addChild(toItem(table));
	}
}

void CTableTree::slot_modify_table()
{
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		CTableModelForm frm;
		frm.line_tableno->setEnabled(false);
		frm.line_tableno->setText(item->text(0));
		frm.line_enname->setText(item->text(1));
		frm.line_cnname->setText(item->text(2));
		frm.line_nextid->setText(item->text(3));
		if(frm.exec() == QDialog::Accepted)
		{
			TABLE_PARA_STRU table = toTableParam(&frm);
			CODBTable::instance()->modifyTable(table);

			// 更改当前显示属性
			updateItem(item,table);
		}
	}
}

void CTableTree::slot_delete_table()
{
	
}

void CTableTree::slot_clone_table()
{
	CTableModelForm frm;
	frm.exec();
}

void CTableTree::slot_save_to_file()
{

}