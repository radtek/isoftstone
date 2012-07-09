
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QFile>
#include <QInputDialog>

#include "tabletree.h"
#include "uiwidget.h"
#include "rtdb_api.h"
#include "odb_api.h"

CTableTree::CTableTree(QWidget* parent):CTableList(parent)
{
	setAlternatingRowColors(true);

	connect(this,SIGNAL(currentItemChanged ( QTreeWidgetItem * , QTreeWidgetItem *  )),this,SLOT(slot_item_changed()));
	connect(this,SIGNAL(itemDoubleClicked (QTreeWidgetItem * , int )),this,SLOT(slot_item_double_clicked()));
	createPopMenu();
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

	act = new QAction(QObject::tr("导出创建到文件"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_save_create_to_file()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("导出插入到文件"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_save_insert_to_file()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("从输入框导入表格"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_import_from_input()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("从文件导入表格"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_import_from_file()));
	m_popMenu->addAction(act);
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
		emit signal_table_changed(tableID);
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
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		int tableID = item->text(0).toInt();
		CODBTable::instance()->deleteTable(tableID);
		m_rootItem->removeChild(item);
	}
}

void CTableTree::slot_clone_table()
{
	CTableModelForm frm;
	frm.exec();
}

void CTableTree::slot_save_create_to_file()
{
	// 根据表信息表和域信息表生成创建语句
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		QString strSQL ;

		int tableID = item->text(0).toInt();
		TABLE_PARA_STRU stTable = CODBTable::instance()->getTableParam(tableID);

		strSQL = "CREATE TABLE ";
		strSQL += stTable.table_name_eng;
		strSQL += "(\n";
		
		QMap<int,FIELD_PARA_STRU> fieldMap = CODBTable::instance()->getFieldMap(tableID);
		QMapIterator<int,FIELD_PARA_STRU > iter(fieldMap);
		int i = 0;
		while(iter.hasNext())
		{
			i++;
			iter.next();
			int fieldID = iter.key();
			const FIELD_PARA_STRU& field = iter.value();
			
			strSQL += field.field_name_eng;
			strSQL += " ";
			strSQL += CODBTable::getDataType(field.data_type,field.data_length,field.is_keyword,field.allow_null); 
			if (i < fieldMap.count())
			{
				strSQL += ",\n";
			}
		}
		strSQL += "\n)";

		QString fileName = QFileDialog::getSaveFileName(this,tr("保存创建到文件"), QString(), "*.sql");
		if (fileName.isEmpty())
			return;

		QFile file(fileName);
		if (file.open(QFile::WriteOnly|QFile::Text)) 
		{
			QTextStream out(&file);
			out << strSQL;
			out.flush();
			file.close();
		}
	}
}

void CTableTree::slot_save_insert_to_file()
{
	// 先获得模式信息
	QTreeWidgetItem* item = currentItem();
	if (item && item->parent() == m_rootItem)
	{
		QString strSQL ;

		int tableID = item->text(0).toInt();
		TABLE_PARA_STRU stTable = CODBTable::instance()->getTableParam(tableID);

		QStringList vecInserts;

		strSQL = "INSERT INTO ";
		strSQL += stTable.table_name_eng;
		strSQL += "(";
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
			strSQL += field.field_name_eng;
			strSQL += " "; 
			if (i < fieldMap.count())
			{
				strSQL += ",";
			}
		}
		strSQL += ") VALUES(";


		// 查询到表数据
		CRtTable table(tableID);
		QVector< QVariantList > vecRows;
		table.getTableRecs(vecRows);
		
		foreach (const QVariantList& lstRec,vecRows)
		{
			int i = 0;
			QString insertSql = strSQL;
			if (lstRec.count() == fieldMap.count())
			{
				foreach(const QVariant& rec,lstRec)
				{
					if (vecFields[i++].data_type == C_STRING_TYPE)
					{
						insertSql += "'";
						insertSql += rec.toString();
						insertSql += "'";
					}
					else
					{
						insertSql += QString::number(rec.toInt());
					}
					if (i < lstRec.count())
					{
						insertSql += ",";
					}
				}
				insertSql += ");\n";

				vecInserts.append(insertSql);
			}
		}

		// 生成insert 语句，保存到文件

		QString fileName = QFileDialog::getSaveFileName(this,tr("保存插入到文件"), QString(), "*.sql");
		if (fileName.isEmpty())
			return;

		QFile file(fileName);
		if (file.open(QFile::WriteOnly|QFile::Text)) 
		{
			QTextStream out(&file);
			foreach(QString strSQL,vecInserts)
			{
				out << strSQL;
			}
			out.flush();
			file.close();
		}
	}

}

void CTableTree::slot_import_from_file()
{
	// 解析文本文件，然后解析出表名和域，然后导入
}

void CTableTree::slot_import_from_input()
{
	// 解析文本框，然后导入

	QString strSQL = QInputDialog::getText(this,"Create SQL","SQL");
	if (checkSQLValid(strSQL))
	{
		importTableBySQL(strSQL);
	}
}

bool CTableTree::checkSQLValid(const QString& strSQL)
{
	if (strSQL.contains("CREATE TABLE",Qt::CaseInsensitive)
		&& strSQL.contains("(")
		&& strSQL.contains(")"))
	{
		return true;
	}
	return false;
}

void CTableTree::importTableBySQL(const QString& strSQL)
{
	TABLE_PARA_STRU stTable;
	QString en_name;

	int nLeftTable = strSQL.indexOf("TABLE",0,Qt::CaseInsensitive);
	int nRightTable = strSQL.indexOf('(');
	int nLast = strSQL.length();

	en_name = strSQL.mid(nLeftTable,nRightTable - nLeftTable);
	en_name.remove('[');
	en_name.remove(']');
	en_name.remove("TABLE",Qt::CaseInsensitive);
	en_name.trimmed().simplified();

	stTable.table_id = CODBTable::instance()->getNextID(1);
	stTable.table_name_eng = en_name;
	stTable.table_name_chn = en_name;
	stTable.next_id = 1;

	// 增加表
	CODBTable::instance()->addTable(stTable);
	m_rootItem->addChild(toItem(stTable));

	// 增加域
	
	QString strField = strSQL.mid(nRightTable,nLast - nRightTable);
	strField.simplified();
	strField.remove(0,1);
	strField.remove(-1,1);
	QStringList lstField = strField.split(',');

	int fieldID = CODBTable::instance()->getNextID(stTable.table_id);
	foreach(QString strField,lstField)
	{
		FIELD_PARA_STRU stField;
		stField.table_id = stTable.table_id;
		stField.field_id = fieldID++;

		QString strFieldName = strField.split(' ')[0];
		strFieldName.remove('[');
		strFieldName.remove(']');
		stField.field_name_eng = strFieldName;
		stField.field_name_chn = strFieldName;

		if (strField.contains("PRIMARY KEY",Qt::CaseInsensitive))
		{
			stField.is_keyword = true;
		}
		else
		{
			stField.is_keyword = false;
		}
		if (strField.contains("NOT NULL",Qt::CaseInsensitive))
		{
			stField.allow_null = false;
		}
		else
		{
			stField.allow_null = true;
		}
		
		if (strField.contains("INTEGER",Qt::CaseInsensitive))
		{
			stField.data_type = C_INT_TYPE;
			stField.data_length = 4;
		}
		if (strField.contains("BOOLEAN",Qt::CaseInsensitive))
		{
			stField.data_type = C_BOOLEAN_TYPE;
			stField.data_length = 1;
		}
		if (strField.contains("VARCHAR",Qt::CaseInsensitive))
		{
			stField.data_type = C_STRING_TYPE;
			int nL = strField.indexOf('(');
			int nR = strField.indexOf(')');

			QString strLen = strField.mid(nL+1,nR - nL -1);
			stField.data_length = strLen.toInt();
		}

		if (stField.field_name_eng.simplified().toUpper() != QString("id").toUpper())
		{
			CODBTable::instance()->addField(stField);
		}
	}
	emit signal_table_changed(stTable.table_id);
}