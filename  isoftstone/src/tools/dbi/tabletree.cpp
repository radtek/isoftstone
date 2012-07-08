
#include <QContextMenuEvent>
#include <QFileDialog>
#include <QFile>

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

	act = new QAction(QObject::tr("����±�"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_add_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("�޸ı�"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_modify_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("ɾ����"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_delete_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("��¡��"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_clone_table()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("�����������ļ�"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_save_create_to_file()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("�������뵽�ļ�"),m_popMenu);
	connect(act,SIGNAL(triggered(bool)),this,SLOT(slot_save_insert_to_file()));
	m_popMenu->addAction(act);

	act = new QAction(QObject::tr("���ļ�������"),m_popMenu);
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

			// ���ĵ�ǰ��ʾ����
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
	// ���ݱ���Ϣ�������Ϣ�����ɴ������
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

		QString fileName = QFileDialog::getSaveFileName(this,tr("���洴�����ļ�"), QString(), "*.sql");
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
	// �Ȼ��ģʽ��Ϣ
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


		// ��ѯ��������
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

		// ����insert ��䣬���浽�ļ�

		QString fileName = QFileDialog::getSaveFileName(this,tr("������뵽�ļ�"), QString(), "*.sql");
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
	// �����ı��ļ���Ȼ���������������Ȼ����
}