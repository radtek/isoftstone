
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include "datawidget.h"

CDataWidget::CDataWidget(QObject* parent )
{
	m_tableList = new CRtTableView(this);
	m_dataTable = new CDataTable(this);

	connect(m_tableList,SIGNAL(signal_table_changed(int)),m_dataTable,SLOT(slot_table_changed(int)));

	resize(800,800);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_tableList);
	layout->addWidget(m_dataTable);

	setLayout(layout);
	setWindowTitle(QObject::tr("Êý¾Ý±à¼­Æ÷"));
}

CDataWidget::~CDataWidget()
{

}