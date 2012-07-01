#include <QMimeData>
#include <QUrl>
#include <QInputDialog>
#include <QDir>
#include <QDebug>
#include <QMessageBox>
#include "treewidget.h"
#include "setting.h"
#include "mainwindow.h"

CTreeWidget::CTreeWidget(void)
{
	//connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(st_Expanded(QTreeWidgetItem*)));
	initMenuList();
}

CTreeWidget::~CTreeWidget(void)
{
		
}

//void CTreeWidget::st_Expanded(QTreeWidgetItem* item)
//{
//	resizeColumnToContents(0);
//}

bool CTreeWidget::dropMimeData( QTreeWidgetItem* parent, int index, const QMimeData* data, Qt::DropAction action)
{
	QList<QUrl> urlList;
	QTreeWidgetItem *item;

	urlList = data->urls(); // retrieve list of urls
	QString strType = data->text();
	
	//foreach(QUrl url, urlList) // iterate over list
	//{
		// make new QTreeWidgetItem and set its text
		// if parent is null - add top level item (this parent)
	if (NULL == parent)
	{
		return false;
	}
	else 
	{    			
		if (NULL == parent->parent())
		{
			if ("Item" == strType)
			{
				QString strApp = parent->text(0);
				QString strItemType = urlList.first().toLocalFile().trimmed();
				char* visdir = getenv("VISDIR");
				QString strFilePath = QString(visdir) + "/conf/popup/popup_menu_relation.ini";
				CSettings relSetting(strFilePath);
				
				relSetting.beginGroup(strApp);
				if (relSetting.contains(strItemType))
				{
					QMessageBox::critical(this, tr("vmi"), tr("已存在此图元菜单"));
					return false;
				}
				relSetting.endGroup();
					
				bool ok = false;
				QString strItemName = QInputDialog::getText(this, tr("新建图元右键菜单"),
					tr("输入名称:"), QLineEdit::Normal,
					parent->text(0).toUpper() + urlList.last().toLocalFile().trimmed() + tr("菜单"), &ok);
				if (ok && !strItemName.isEmpty())
				{
					qDebug() << strItemName;
					item = new QTreeWidgetItem(parent);
					parent->setExpanded(true);
					item->setText(0, strItemName);
					relSetting.saveValue(strApp, strItemType, QVariant(strItemName));
					
					strFilePath = QString(visdir) + QString("/conf/popup/%1_popup_menu.ini").arg(strApp);
					CSettings menuSetting(strFilePath);
					menuSetting.addGroups(strItemName);
					menuSetting.sync();
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			QTreeWidgetItem* parentItem = parent->parent()->parent();
			if (NULL == parentItem && "Commond" == strType)
			{
				bool ok = false;
				int iPos = -1;
				int iMax = parent->childCount() + 1;
				iPos = QInputDialog::getInt(this, tr("关联菜单"), tr("选择位置"), iMax, 1, iMax, 1, &ok);
				if (ok && iPos != -1)
				{
					item = new QTreeWidgetItem(parent);
					parent->setExpanded(true);
					QString strPos = QString("NORMAL_MENU_%1").arg(iPos);
					QString strCommand = urlList.first().toLocalFile().trimmed() + "/" +urlList.last().toString();
					item->setText(0, strPos);
					item->setText(1, strCommand);
					QString strMenu = parent->text(0);
					QString strApp = parent->parent()->text(0);
					moveCommand(strApp, strMenu, iPos, eInsert);
					char* visdir = getenv("VISDIR");
					QString strFilePath = QString(visdir) + QString("/conf/popup/%1_popup_menu.ini").arg(strApp);
					CSettings menuSetting(strFilePath);
					menuSetting.saveValue(strMenu, strPos, strCommand);
						
					clear();
					initMenuList();

					QList<QTreeWidgetItem*> lstItems = findItems(strMenu, Qt::MatchRecursive);
					lstItems.first()->setExpanded(true);
					lstItems = findItems(strApp, Qt::MatchExactly);
					lstItems.first()->setExpanded(true);
				}
			}
			else
			{
				return false;
			}
		}
	}

	return true;
}

QStringList CTreeWidget::mimeTypes () const 
{
	QStringList qstrList;
	// list of accepted mime types for drop
	qstrList.append("text/uri-list");
	return qstrList;
}


Qt::DropActions CTreeWidget::supportedDropActions () const
{
	// returns what actions are supported when dropping
	return Qt::CopyAction | Qt::MoveAction;
}

void CTreeWidget::moveCommand(QString strApp, QString strItem, int iPos, Mode eType)
{
	char* visdir = getenv("VISDIR");
	QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
	CSettings st(strFileName);
	st.beginGroup(strItem);
	
	int iMax = getMaxPos(strApp, strItem);	// 最大位置
	
	if (eInsert == eType)
	{
		for (int i = iMax; i >= iPos; i-- )
		{
			QString strPos = getStrByPos(strApp, strItem, i);
			QStringList lstPos = strPos.split("_");
			QString strCommand = st.value(strPos).toString();
			st.remove(strPos);
			strPos.clear();
			lstPos.last() = QString("%1").arg(i+1);
			foreach (QString str, lstPos)
			{
				strPos.push_back(str);
				if (str != lstPos.last())
				{
					strPos.push_back("_");
				}					
			}						
			st.setValue(strPos, strCommand);	
		}
	}
	
	else
	{
		for (int i = iPos + 1 ; i <= iMax; i++)
		{
			QString strPos = getStrByPos(strApp, strItem, i);
			QStringList lstPos = strPos.split("_");
			QString strCommand = st.value(strPos).toString();
			st.remove(strPos);	
			strPos.clear();
			lstPos.last() = QString("%1").arg(i - 1);
			foreach (QString str, lstPos)
			{
				strPos.push_back(str);
				if (str != lstPos.last())
				{
					strPos.push_back("_");
				}					
			}						
			st.setValue(strPos, strCommand);	
		}
	}

	st.endGroup();
	st.sync();
}

//菜单列表
void CTreeWidget::initMenuList()
{
	clear();
	//设置表中的列的列数目	
	setColumnCount(2);

	//添加表头
	QStringList headers;
	headers << tr("菜单") << tr("中文名称");

	setHeaderLabels(headers);//设置表头

	QStringList fileTextList;
	QStringList rootTextList;
	QStringList leafTextList; 
	char* visdir = getenv("VISDIR");
	QString strFilePath = QString(visdir) + "/conf/popup";
	QDir dir(strFilePath, "*_popup_menu.ini", QDir::Name | QDir::IgnoreCase, QDir::Files);
	QStringList lstFileName = dir.entryList();
	foreach(QString strFileName, lstFileName)
	{
		int iPos = strFileName.indexOf("_");
		QString strStatus = strFileName.left(iPos);
		fileTextList << strStatus;
		QTreeWidgetItem* fileItem = new QTreeWidgetItem(this,fileTextList);//根节点数据
		fileTextList.clear();
		this->addTopLevelItem(fileItem);
		rootTextList.clear();

		strFileName = dir.absoluteFilePath(strFileName);
		CSettings st(strFileName);
		QMap<QString,QMap<QString,QVariant> > commandMap = st.getIniMap();
		QMapIterator<QString,QMap<QString,QVariant> > iter(commandMap);
		while (iter.hasNext())
		{
			iter.next();
			const QString& strGroup = iter.key();

			QStringList rootTextList;

			const QMap<QString,QVariant> &keyValues = iter.value();
			rootTextList<<strGroup;

			QTreeWidgetItem *root = new QTreeWidgetItem(fileItem, rootTextList);//根节点数据
			fileItem->addChild(root);

			QMapIterator<QString,QVariant> it(keyValues);
			QList<QTreeWidgetItem*> lstChildren;
			while (it.hasNext())
			{
				it.next();
				leafTextList.clear();	//清除之前的数据，防止覆盖
				QString strItem = it.value().toString();

				leafTextList<<it.key()<<strItem;//子节点一行数据
				QTreeWidgetItem *leaf = new QTreeWidgetItem(root,leafTextList);//子节点数据
				lstChildren.append(leaf);
			}

			root->addChildren(lstChildren);//添加子节点
		}	// while	

	}	// foreach
}

int CTreeWidget::getMaxPos(QString strApp, QString strItem)
{
	int iMax = 0;
	char* visdir = getenv("VISDIR");
	QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
	CSettings st(strFileName);
	st.beginGroup(strItem);
	foreach (QString str, st.allKeys())
	{
		QStringList lstPos = str.split("_");
		int iNo = lstPos.last().toInt();
		if (iNo > iMax)
		{
			iMax = iNo;
		}
	}
	st.endGroup();
	return iMax;
}

QString CTreeWidget::getStrByPos(QString strApp, QString strItem, int iPos)
{
	QString strPos;
	char* visdir = getenv("VISDIR");
	QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
	CSettings st(strFileName);
	st.beginGroup(strItem);
	foreach (QString str, st.allKeys())
	{
		QStringList lstPos = str.split("_");
		int iNo = lstPos.last().toInt();
		if (iNo == iPos)
		{
			strPos = str;
			break;
		}
	}
	st.endGroup();
	return strPos;
}

void CTreeWidget::keyPressEvent(QKeyEvent *event)
{
	if (currentItem() && currentItem()->parent())
	{
		char* visdir = getenv("VISDIR");
		if (event->key() == Qt::Key_Delete && currentItem()->parent()->parent() && currentItem()->parent()->parent())
		{
			if (QMessageBox::Yes == QMessageBox::question(this, "", QObject::tr("确认删除？"), QMessageBox::Yes, QMessageBox::No))
			{				
				QString strPos = currentItem()->text(0);
				QString strItem = currentItem()->parent()->text(0);
				QString strApp = currentItem()->parent()->parent()->text(0);								
				currentItem()->parent()->removeChild(currentItem());
				QString strFileName = QString(visdir) + "/conf/popup/" + strApp + "_popup_menu.ini";
				CSettings st(strFileName);
				st.beginGroup(strItem);
				st.remove(strPos);
				st.endGroup();
				st.sync();
				QStringList lstPos = strPos.split("_");
				int iPos = lstPos.last().toInt();
				moveCommand(strApp, strItem, iPos, eRemove);
				
				clear();
				initMenuList();

				QList<QTreeWidgetItem*> lstItems = findItems(strItem, Qt::MatchRecursive);
				if (lstItems.first()->childCount() >0)
				{
					lstItems.first()->setExpanded(true);
				}
				lstItems = findItems(strApp, Qt::MatchExactly);
				lstItems.first()->setExpanded(true);

				return;
			}
		}

		else if (event->key() == Qt::Key_Insert )
		{
			QTreeWidgetItem* parentItem = currentItem()->parent();
			if (parentItem->parent() == NULL)
			{
					
			}
			else
			{

			}
		}
	}
	
}