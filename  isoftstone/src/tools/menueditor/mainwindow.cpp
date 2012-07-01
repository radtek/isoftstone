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
	setWindowTitle(tr("菜单编辑器"));
	setFixedSize(1000,600);
	labelMenu = new QLabel(tr("菜单编辑器"));
	labelItem = new QLabel(tr("图元列表"));
	labelCommand = new QLabel(tr("命令列表"));

	tableViewCommand = new CCommandView();
	treeViewMenu = new CTreeWidget();
	treeViewItem = new CTreeView();

	treeViewMenu->setAcceptDrops(true);

	//布局
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


//命令列表
void CMenuMgrWindow::initCommandList()
{
	QStandardItemModel *model;
	model = new QStandardItemModel(0,2);//设置表格列数

	tableViewCommand->setSortingEnabled(true);//开启排序

	tableViewCommand->setSelectionBehavior(QAbstractItemView::SelectRows);//只选中整行
	tableViewCommand->setSelectionMode(QAbstractItemView::SingleSelection);//单行选中
	tableViewCommand->setShowGrid(true);//显示网格
	tableViewCommand->verticalHeader()->hide();//隐藏表头编号
	//设置行色
	tableViewCommand->setAlternatingRowColors(true);

	////设置任意颜色
	//QPalette pal;
	//pal = tableViewCommand->palette();
	//pal.setColor(QPalette::AlternateBase,Qt::darkCyan);
	//tableViewCommand->setPalette(pal);

	tableViewCommand->setModel(model);

	tableViewCommand->horizontalHeader()->setStretchLastSection(true);//对列进行设置，使其完全填充
	//设置表头
	model->setHeaderData(0,Qt::Horizontal,QObject::tr("参数值"));
	model->setHeaderData(1,Qt::Horizontal,QObject::tr("参数名称"));

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
	model->sort(0,Qt::AscendingOrder);//升序排列
	//保存
	QObject::connect(model,SIGNAL(itemChanged(QStandardItem*)),tableViewCommand,SLOT(onTableViewChanged(QStandardItem*)));
	for (int i = 0; i < model->rowCount(); i++)
	{
		model->item(i)->setFlags(Qt::ItemIsDragEnabled | Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
}

//保存图元列表的修改
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

//图元列表
void CMenuMgrWindow::initItemList()
{
	QStandardItemModel *modelList;
	modelList = new QStandardItemModel(0,2);
	modelList->setHeaderData(0,Qt::Horizontal,QObject::tr("图元名称"));
	modelList->setHeaderData(1,Qt::Horizontal,QObject::tr("中文名称"));
	//显示颜色
	treeViewItem->setAlternatingRowColors(true);

	//设置任意颜色
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

//菜单列表
void CMenuMgrWindow::initMenuList()
{
	//设置表中的列的列数目
	treeViewMenu->setColumnCount(2);

	//添加表头
	QStringList headers;
	headers << tr("菜单") << tr("中文名称");

	treeViewMenu->setHeaderLabels(headers);//设置表头

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
		QTreeWidgetItem* fileItem = new QTreeWidgetItem(treeViewMenu,fileTextList);//根节点数据
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