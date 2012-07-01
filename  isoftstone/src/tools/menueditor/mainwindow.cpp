#include "mainwindow.h"
#include "setting.h"

CMenuMgrWindow::CMenuMgrWindow()
{
	setupUi();
	this->initCommandList();
	this->initItemList();
	//this->initMenuList();
	bool bRet = connect(tableViewCommand, SIGNAL(sigUpdate()), treeViewMenu, SLOT(initMenuList()));

}

CMenuMgrWindow::~CMenuMgrWindow()
{
}

void CMenuMgrWindow::setupUi()
{
	setWindowTitle(tr("�˵��༭��"));
	setFixedSize(1000,600);
	labelMenu = new QLabel(tr("�˵��༭��"));
	labelItem = new QLabel(tr("ͼԪ�б�"));
	labelCommand = new QLabel(tr("�����б�"));

	tableViewCommand = new CCommandView();
	treeViewMenu = new CTreeWidget();
	treeViewItem = new CTreeView();

	treeViewMenu->setAcceptDrops(true);

	//����
	QVBoxLayout *leftLayout = new QVBoxLayout;
	leftLayout->addWidget(labelMenu);
	leftLayout->addWidget(treeViewMenu);

	QVBoxLayout *midLayout = new QVBoxLayout;
	midLayout->addWidget(labelItem);
	midLayout->addWidget(treeViewItem);

	QVBoxLayout *rightLayout = new QVBoxLayout;
	rightLayout->addWidget(labelCommand);
	rightLayout->addWidget(tableViewCommand);

	QHBoxLayout *mainLayout = new QHBoxLayout;
	mainLayout->addLayout(leftLayout);
	mainLayout->addLayout(midLayout);
	mainLayout->addLayout(rightLayout);
	setLayout(mainLayout);
}


//�����б�
void CMenuMgrWindow::initCommandList()
{
	QStandardItemModel *model;
	model = new QStandardItemModel(0,2);//���ñ������

	tableViewCommand->setSortingEnabled(true);//��������

	tableViewCommand->setSelectionBehavior(QAbstractItemView::SelectRows);//ֻѡ������
	tableViewCommand->setSelectionMode(QAbstractItemView::SingleSelection);//����ѡ��
	tableViewCommand->setShowGrid(true);//��ʾ����
	tableViewCommand->verticalHeader()->hide();//���ر�ͷ���
	//������ɫ
	tableViewCommand->setAlternatingRowColors(true);

	////����������ɫ
	//QPalette pal;
	//pal = tableViewCommand->palette();
	//pal.setColor(QPalette::AlternateBase,Qt::darkCyan);
	//tableViewCommand->setPalette(pal);

	tableViewCommand->setModel(model);

	tableViewCommand->horizontalHeader()->setStretchLastSection(true);//���н������ã�ʹ����ȫ���
	//���ñ�ͷ
	model->setHeaderData(0,Qt::Horizontal,QObject::tr("����ֵ"));
	model->setHeaderData(1,Qt::Horizontal,QObject::tr("��������"));

	QModelIndex index;

	int i = 0;

	char* visdir = getenv("VISDIR");
	QString strFileName = QString(visdir) + "/conf/popup/popup_command.ini";
	CSettings st(strFileName);
	//CSettings st("E:\\zsy\\popup\\popup_command.ini");
	QMap<QString,QMap<QString,QVariant> > commandMap = st.getIniMap();
	QMapIterator<QString,QMap<QString,QVariant> > iter(commandMap);
	while (iter.hasNext())
	{
		iter.next();
		const QMap<QString,QVariant>& keyValues = iter.value();
		model->setRowCount(model->rowCount() + keyValues.count());
		QMapIterator<QString,QVariant> it(keyValues);
		while (it.hasNext())
		{
			it.next();
			index = model->index(i,0);
			QVariant varNum = it.key().toInt();
			model->setData(index,varNum, Qt::DisplayRole);

			index = model->index(i,1);
			QVariant varCommand = it.value()/*.toUInt()*/;
			model->setData(index,varCommand);
			model->setData(index,varCommand,Qt::UserRole);
			i++;
		}
	}
	model->sort(0,Qt::AscendingOrder);//��������
	//����
	QObject::connect(model,SIGNAL(itemChanged(QStandardItem*)),tableViewCommand,SLOT(onTableViewChanged(QStandardItem*)));
	for (int i = 0; i < model->rowCount(); i++)
	{
		model->item(i)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
}

//����ͼԪ�б���޸�
void CMenuMgrWindow::onTreeItemChanged(QStandardItem * item)
{
	if (item)
	{
		QString strGroup ;
		QStandardItem * pItem = item->parent();
		if (pItem)
		{
			strGroup	= pItem->data( Qt::EditRole).toString();

			QStandardItem* kItem = pItem->child(item->row(),item->column() - 1);
			if (kItem)
			{
				QString strkey = kItem->data( Qt::EditRole).toString();
				QString strValue = item->data( Qt::EditRole).toString();
				char* visdir = getenv("VISDIR");
				QString strFileName = QString(visdir) + "/conf/popup/popup_menu_text.ini";
				CSettings st(strFileName);
				st.saveValue(strGroup,strkey,strValue);
			}
		}
	}
}

//ͼԪ�б�
void CMenuMgrWindow::initItemList()
{
	QStandardItemModel *modelList;
	modelList = new QStandardItemModel(0,2);
	modelList->setHeaderData(0,Qt::Horizontal,QObject::tr("ͼԪ����"));
	modelList->setHeaderData(1,Qt::Horizontal,QObject::tr("��������"));
	//��ʾ��ɫ
	treeViewItem->setAlternatingRowColors(true);

	//����������ɫ
	/*QPalette pal;
	pal = treeViewItem->palette();
	pal.setColor(QPalette::AlternateBase,QColor(255,250,0));
	treeViewItem->setPalette(pal);*/

	treeViewItem->setModel(modelList);

	QModelIndex index;
	char* visdir = getenv("VISDIR");
	QString strFileName = QString(visdir) + "/conf/popup/popup_menu_text.ini";
	CSettings st(strFileName);
	//CSettings st("E:\\zsy\\popup\\popup_menu_text.ini");
	QMap<QString,QMap<QString,QVariant> > itemMap = st.getIniMap();
	QMapIterator<QString,QMap<QString,QVariant> > iter(itemMap);
	while (iter.hasNext())
	{
		iter.next();

		const QString& strGroup = iter.key();
		QModelIndex parent;
		modelList->insertRows(0,1,parent);
		parent = modelList->index(0,0,parent);
		modelList->setData(parent,strGroup);

		const QMap<QString,QVariant> &keyValues = iter.value();
		modelList->insertRows(0,keyValues.count(),parent);
		modelList->insertColumns(0, 2, parent);
		int i = 0;
		QMapIterator<QString,QVariant> it(keyValues);
		while (it.hasNext())
		{
			it.next();

			index = modelList->index(i, 0, parent);
			modelList->setData(index,it.key());

			index = modelList->index(i,1,parent);
			QString strItem = it.value().toString();
			modelList->setData(index,strItem);
			i++;	
		}
	}
	//QObject::connect(modelList,SIGNAL(itemChanged ( QStandardItem * )),this,SLOT(onTreeItemChanged(QStandardItem * )));
}

//�˵��б�
void CMenuMgrWindow::initMenuList()
{
	//���ñ��е��е�����Ŀ
	treeViewMenu->setColumnCount(2);

	//��ӱ�ͷ
	QStringList headers;
	headers << tr("�˵�") << tr("��������");

	treeViewMenu->setHeaderLabels(headers);//���ñ�ͷ

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
		QTreeWidgetItem* fileItem = new QTreeWidgetItem(treeViewMenu,fileTextList);//���ڵ�����
		fileTextList.clear();
		treeViewMenu->addTopLevelItem(fileItem);
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

			QTreeWidgetItem *root = new QTreeWidgetItem(fileItem, rootTextList);//���ڵ�����
			fileItem->addChild(root);

			QMapIterator<QString,QVariant> it(keyValues);
			QList<QTreeWidgetItem*> lstChildren;
			while (it.hasNext())
			{
				it.next();
				leafTextList.clear();	//���֮ǰ�����ݣ���ֹ����
				QString strItem = it.value().toString();

				leafTextList<<it.key()<<strItem;//�ӽڵ�һ������
				QTreeWidgetItem *leaf = new QTreeWidgetItem(root,leafTextList);//�ӽڵ�����
				lstChildren.append(leaf);
			}

			root->addChildren(lstChildren);//����ӽڵ�
		}	// while	

	}	// foreach

}