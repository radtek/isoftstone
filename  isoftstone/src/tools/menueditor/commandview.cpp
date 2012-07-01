#include "commandview.h"
#include "mainwindow.h"
#include "setting.h"
#include "treeview.h"
#include "alg.h"

CCommandView::CCommandView()
{
}

CCommandView::~CCommandView(void)
{
}

void CCommandView::dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight )
{
// 	if (topLeft == bottomRight)
// 	{
// 		QStandardItemModel* pStandModel = dynamic_cast<QStandardItemModel*>(model());
// 		QStandardItem* pItem = pStandModel->item(topLeft.row(),topLeft.column());
// 		onTableViewChanged(pItem);
// 	}
}

void CCommandView::onTableViewChanged(QStandardItem * pItem)
{
	if(pItem && pItem->column() == 1)
	{
		QString strkey;
		QStandardItem * pLeftItem = pItem->model()->item(pItem->row(), 0);
		if (pLeftItem)
		{
			strkey	= pLeftItem->data( Qt::EditRole).toString();
			QString strKeyOld = pItem->data(Qt::UserRole).toString().simplified();
			//将数据转换成字符串，去掉两边空格
			QString strValue = pItem->data( Qt::EditRole).toString().simplified();
			if( strKeyOld == strValue)
			{
				return;
			}
			bool flag =true;
			//bool flag = isValid(pItem->data(Qt::EditRole).toUInt());
			//if (QMessageBox::Yes == QMessageBox::question(this, "", QObject::tr("确认修改？"), QMessageBox::Yes, QMessageBox::No))
			if (flag)
			{								
				pItem->setData(QVariant(strValue.toUInt()),Qt::UserRole);
				char* visdir = getenv("VISDIR");
				QString strFileName = QString(visdir) + "/conf/popup/popup_command.ini";
				CSettings st(strFileName);
				st.saveValue("command",strkey,strValue);
				st.sync();

				// 级联修改
				QString strFilePath = QString(visdir) + "/conf/popup";
				QDir dir(strFilePath, "*_popup_menu.ini", QDir::Name | QDir::IgnoreCase, QDir::Files);
				QStringList lstFileName = dir.entryList();
				bool bChanged = false;
				foreach(QString strFileName, lstFileName)
				{													
					strFileName = dir.absoluteFilePath(strFileName);
					CSettings st(strFileName);
					QMap<QString,QMap<QString,QVariant> > commandMap = st.getIniMap();
					QMapIterator<QString,QMap<QString,QVariant> > iter(commandMap);
					while (iter.hasNext())
					{
						iter.next();
						const QString& strGroup = iter.key();
						const QMap<QString,QVariant> &keyValues = iter.value();						
						QMapIterator<QString,QVariant> it(keyValues);
						while (it.hasNext())
						{
							it.next();
							QString strPos = it.key();						
							QString strCommand = it.value().toString();
							if (strPos.contains("NORMAL_MENU"))
							{
								QStringList lstCommand = strCommand.split("/");							
								if (lstCommand.size() > 1)
								{									
									QString tmpStr = lstCommand.last();
									if (lstCommand.last() == strkey && lstCommand.first() != strValue)
									{									
										int iCommand = lstCommand.last().toInt();
										st.beginGroup(strGroup);
										st.setValue(strPos, strValue + "/" + strkey);									
										st.sync();
										st.endGroup();									
										bChanged = true;
										break;
									}
								}								
							}
						}
					}	// while	
				}	// foreach
				if (bChanged)
				{
					emit sigUpdate();
				}
			}
			else
			{
				pItem->setData(QVariant(strKeyOld.toUInt()),Qt::EditRole);
				this->resizeDate();
			}
		}
	}
}

//恢复原始数据
void CCommandView::resizeDate()
{
	//CMenuMgrWindow *menu = new CMenuMgrWindow;
	//menu->initCommandList();
}

bool CCommandView::isValid(int nCommand)
{
	bool bRet = false;
	char* visdir = getenv("VISDIR");
	QString strFileName = QString(visdir) + "/conf/popup/popup_command.ini";
	CSettings st(strFileName);

	QMap<QString,QMap<QString,QVariant> > commandMap = st.getIniMap();
	QMapIterator<QString,QMap<QString,QVariant> > iter(commandMap);
	//限制范围
	if (nCommand > 0 && nCommand < MAX_COMMAND)
	{
		//判断是否重复
		while (iter.hasNext())
		{
			iter.next();
			const QMap<QString,QVariant>& keyValues = iter.value();
			QMapIterator<QString,QVariant> it(keyValues);
			while (it.hasNext())
			{
				it.next();
				if (it.value().toInt() == nCommand)
				{
					bRet = false;
					QMessageBox::warning(this,tr("warning"),tr("重复！"));
					return bRet;
				}
			}
		}
		commandMap.clear();
		bRet = true;
	}
	else
	{
		QMessageBox::warning(this,tr("warning"),tr("数值越界！"));
	}
	return bRet;
}

void CCommandView::keyPressEvent(QKeyEvent *event)//快捷键
{
	if (event->key() == Qt::Key_Delete)
	{
		if(QMessageBox::Yes == QMessageBox::question(this, tr("删除"), QObject::tr("确认删除？"), QMessageBox::Yes, QMessageBox::No))
		{
			char* visdir = getenv("VISDIR");
			QString strFileName = QString(visdir) + "/conf/popup/popup_command.ini";
			CSettings st(strFileName);
			QMap<QString,QMap<QString,QVariant> > itemMap = st.getIniMap();
			QMapIterator<QString,QMap<QString,QVariant> > iter(itemMap);
			QString strValue = currentIndex().data().toString();
			st.beginGroup("command");
			st.remove(currentIndex().data().toString());
			st.endGroup();
			st.sync();
			int curRow = currentIndex().row();
			model()->removeRow(curRow);

			// 级联删除
			QString strFilePath = QString(visdir) + "/conf/popup";
			QDir dir(strFilePath, "*_popup_menu.ini", QDir::Name | QDir::IgnoreCase, QDir::Files);
			QStringList lstFileName = dir.entryList();
			bool bChanged = false;
			foreach(QString strFileName, lstFileName)
			{													
				strFileName = dir.absoluteFilePath(strFileName);
				CSettings st(strFileName);
				QMap<QString,QMap<QString,QVariant> > commandMap = st.getIniMap();
				QMapIterator<QString,QMap<QString,QVariant> > iter(commandMap);
				while (iter.hasNext())
				{
					iter.next();
					const QString& strGroup = iter.key();
					const QMap<QString,QVariant> &keyValues = iter.value();						
					QMapIterator<QString,QVariant> it(keyValues);
					while (it.hasNext())
					{
						it.next();
						QString strPos = it.key();						
						QString strCommand = it.value().toString();
						if (strPos.contains("NORMAL_MENU"))
						{
							QStringList lstCommand = strCommand.split("/");							
							if (lstCommand.size() > 1)
							{									
								QString tmpStr = lstCommand.last();
								if (lstCommand.last() == strValue)
								{									
									int iCommand = lstCommand.last().toInt();
									st.beginGroup(strGroup);
									st.remove(strPos);									
									st.sync();
									st.endGroup();									
									bChanged = true;
									break;
								}
							}								
						}
					}
				}	// while	
			}	// foreach
			if (bChanged)
			{
				emit sigUpdate();
			}
			return;
		}
	}
	else if (event->key() == Qt::Key_Insert)
	{
		char* visdir = getenv("VISDIR");
		QString strFileName = QString(visdir) + "/conf/popup/popup_command.ini";
		CSettings st(strFileName);
		st.beginGroup("command");
		
		bool ok = false;
		QString strNum = QInputDialog::getText(this, tr("新建右键命令"),
			tr("输入命令值:"), QLineEdit::Normal, QString(""), &ok);
		if (ok && !strNum.isEmpty() && !st.contains(strNum))
		{
			ok = false;
			QString strCommand = QInputDialog::getText(this, tr("新建右键命令"),
				tr("输入命令名称:"), QLineEdit::Normal, QString(""), &ok);
			if (ok && !strCommand.isEmpty() && !st.allKeys().contains(strCommand))
			{
				st.setValue(strNum, strCommand);
				st.sync();				
				model()->insertRow(model()->rowCount());
				QModelIndex indexNo = model()->index(model()->rowCount() - 1, 0);
				model()->setData(indexNo, QVariant(strNum.toUInt()));
				QModelIndex indexCommand = model()->index(model()->rowCount() - 1, 1);
				model()->setData(indexCommand, strCommand);
			}
		}				
	}
}

void CCommandView::mousePressEvent(QMouseEvent *event)
{
	QTableView::mousePressEvent(event);
	if (!(event->buttons() & Qt::LeftButton)) 
	{	
		return;
	}

	QModelIndex index = currentIndex();
	if (index.isValid() == false)
	{
		return;
	}

	QDrag *drag = new QDrag(this);
	QMimeData *mimeData = new QMimeData;

	QList<QUrl> list;
	int iRow = index.row();
	bool bRet = model()->index(iRow, 1).isValid();
	QString strNum = model()->index(iRow, 0).data().toString();	
	list.push_back(model()->index(iRow, 1).data().toUrl()); 	
	list.push_back(QUrl(strNum));	
	// mime stuff
	mimeData->setUrls(list); 
	mimeData->setText("Commond");
	drag->setMimeData(mimeData);

	// start drag
	drag->start(Qt::CopyAction | Qt::MoveAction);

}