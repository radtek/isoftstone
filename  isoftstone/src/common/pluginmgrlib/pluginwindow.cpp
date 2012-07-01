/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: pluginwindow.cpp
** ժҪ: Ӧ�ó��������������������
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2011.11.4
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2011.11.4   V1.0      ����
**
****************************************************************************/

#include <QMessageBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "pluginwindow.h"

CPluginWindow::CPluginWindow(QWidget *parent) : QWidget(parent)
	
{
	init();
	setMouseTracking(true);
}

QObject* CPluginWindow::getObject()
{
	return this;
}

IPluginBase* CPluginWindow::getPlugin(const QString& pluginName)
{
	return m_pluginManager.getPlugin(pluginName);
}

void CPluginWindow::setMenuBar(QMenuBar* pMenuBar)
{
	m_pluginManager.initMenuBar(pMenuBar);	

	updateTable();
}

void CPluginWindow::setParentWindow(QWidget* pParentWindow) 
{
	m_pluginManager.setParentWindow(pParentWindow);
}

void CPluginWindow::updateTable()
{
	QStringList pluginList = m_pluginManager.m_pluginInfo.keys();
	tableWidget->setRowCount(m_pluginManager.m_pluginInfo.size());
	tableWidget->setColumnCount(3);
	for(int i = 0; i < m_pluginManager.m_pluginInfo.size(); i++)
	{		
		QString pluginName = pluginList.at(i);		
		tableWidget->setItem(i, 0, new QTableWidgetItem(pluginName));	// �����
		
		QFont font;
		//font.setUnderline(true);
		font.setBold(true);

		if(m_pluginManager.m_pluginInfo.value(pluginName).bStatus == true)
		{
			tableWidget->setItem(i, 1, new QTableWidgetItem());
			tableWidget->item(i,1)->setIcon(QIcon(":/res/enable.png"));			
			tableWidget->item(i,1)->setFont(font);
			tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
			tableWidget->item(i,1)->setText(tr("�Ѽ���"));
			//tableWidget->item(i,1)->setToolTip(tr("����"));
			// �������
			QString description = m_pluginManager.m_pluginInfo[pluginName].description;
			tableWidget->setItem(i, 2, new QTableWidgetItem(description));
		}
		else
		{
			tableWidget->setItem(i, 1, new QTableWidgetItem());
			tableWidget->item(i,1)->setIcon(QIcon(":/res/banned.png"));
			tableWidget->item(i,1)->setFont(font);
			tableWidget->item(i,1)->setTextAlignment(Qt::AlignCenter);
			tableWidget->item(i,1)->setText(tr("δ����"));
			tableWidget->item(i,2)->setText(tr("����ʧ�ܣ�����²��"));
			//tableWidget->item(i,1)->setToolTip(tr("����"));
		}
		
	}
	for(int i = 0; i < tableWidget->rowCount(); i++)
	{
		for(int j = 0; j < tableWidget->columnCount(); j++)
		{
			QTableWidgetItem* qItem = tableWidget->item(i, j);		
			qItem->setFlags(qItem->flags() & (~Qt::ItemIsEditable) &(~Qt::ItemIsSelectable));
		}
	}
}

void CPluginWindow::init()
{
	initWidget();
	createConnect();
}

void CPluginWindow::createConnect()
{
	connect(refreshButton, SIGNAL(clicked()), this, SLOT(refresh()));
	connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
	//connect(tableWidget, SIGNAL(cellClicked(int, int)), this, SLOT(changeStatus(int, int)));
	//connect(tableWidget, SIGNAL(cellChanged(int, int)), this, SLOT(saveDescription(int, int)));
}

void CPluginWindow::refresh()
{
	int rowCount = tableWidget->rowCount();
	for(int k = 0; k < rowCount; k++)
		tableWidget->removeRow(k);

	m_pluginManager.loadDir();
	updateTable();
}

void CPluginWindow::changeStatus(int row, int column)
{
	if(1 == column)	//״̬��
	{
		QString pluginName = tableWidget->item(row, 0)->text();
		QString strStatus = tableWidget->item(row, column)->text();

		QFont font;
		font.setUnderline(true);
		font.setBold(true);

		if(tr("����") == strStatus)	//����Ϊ����
		{
			bool bExecOK = m_pluginManager.setPluginEnabled(pluginName, false);
			if(bExecOK != true)
			{
				QMessageBox::critical(this ,tr("���"), tr("����ʧ��"));
			}
			else
			{
				tableWidget->item(row, 1)->setIcon(QIcon(":/res/banned.png"));
				tableWidget->item(row, 1)->setFont(font);
				tableWidget->item(row, 1)->setTextAlignment(Qt::AlignCenter);
				tableWidget->item(row, 1)->setText(tr("����"));
				tableWidget->item(row, 1)->setToolTip(tr("����"));
			}			
		}
		else	//����Ϊ����
		{
			bool bExecOK = m_pluginManager.setPluginEnabled(pluginName, true);
			if(bExecOK != true)
			{
				QMessageBox::critical(this ,tr("���"), tr("����ʧ��"));
			}
			else
			{
				tableWidget->item(row, 1)->setIcon(QIcon(":/res/enable.png"));
				tableWidget->item(row, 1)->setFont(font);
				tableWidget->item(row, 1)->setTextAlignment(Qt::AlignCenter);
				tableWidget->item(row, 1)->setText(tr("����"));
				tableWidget->item(row, 1)->setToolTip(tr("����"));	
				tableWidget->item(row, 2)->setText(m_pluginManager.m_pluginInfo[pluginName].description);
			}	
		}		
	}
}

void CPluginWindow::saveDescription(int row, int column)
{
	if(column == 2)
	{
		QString pluginName = tableWidget->item(row, 0)->text();
		QString description = tableWidget->item(row, column)->text();		
		m_pluginManager.savePluginDescription(pluginName, description);
	}
}

void CPluginWindow::initWidget()
{
	setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint);
	setWindowIcon(QIcon(":/res/config.png"));
	setWindowTitle(tr("�������"));
	resize(400, 300);
	refreshButton = new QPushButton(tr("ˢ�²��"));
	closeButton = new QPushButton(tr("�ر�"));

	tableWidget = new CTableWidget;
	QStringList headerList;
	headerList << tr("����") << tr("״̬") << tr("����");
	tableWidget->setColumnCount(headerList.size());
	tableWidget->setHorizontalHeaderLabels(headerList);
	tableWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch); 
	tableWidget->setAlternatingRowColors(true);
	tableWidget->setShowGrid(true);

	QHBoxLayout *buttonsLayout = new QHBoxLayout;
	buttonsLayout->addStretch(1);
	buttonsLayout->addWidget(refreshButton);
	buttonsLayout->addWidget(closeButton);
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tableWidget);
	//mainLayout->addStretch(1);
	//mainLayout->addSpacing(10);
	mainLayout->addLayout(buttonsLayout);
	setLayout(mainLayout);
	
}

void CPluginWindow::setDataPointer(const QMap<int,void*>& pointerMap,bool bApp)
{
	m_pluginManager.setDataPointer(pointerMap,bApp);
}
