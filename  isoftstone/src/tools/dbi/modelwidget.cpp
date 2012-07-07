
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>

#include "modelwidget.h"


CModelWidget::CModelWidget(QObject* parent )
{
	m_tableTree = new CTableTree(this);
	m_fieldTable = new CFieldTable(this);

	connect(m_tableTree,SIGNAL(signal_table_changed(int,QString)),m_fieldTable,SLOT(slot_table_changed(int,QString)));

	resize(800,800);
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addWidget(m_tableTree);
	layout->addWidget(m_fieldTable);
	
	setLayout(layout);
	setWindowTitle(QObject::tr("ģʽ�༭"));
}

CModelWidget::~CModelWidget()
{

}