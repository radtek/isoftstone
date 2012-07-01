
#ifndef CREATE_DOCK_H
#define CREATE_DOCK_H

#include "customdef.h"

class EXPORT_WIDGET CreateDockWidgetDialog : public QDialog
{
public:
	CreateDockWidgetDialog(QWidget *parent = 0);

	QString objectName() const;
	Qt::DockWidgetArea location() const;

private:
	QLineEdit *m_objectName;
	QComboBox *m_location;
};

CreateDockWidgetDialog::CreateDockWidgetDialog(QWidget *parent)
: QDialog(parent)
{
	QGridLayout *layout = new QGridLayout(this);

	layout->addWidget(new QLabel(tr("窗口名称:")), 0, 0);
	m_objectName = new QLineEdit;
	layout->addWidget(m_objectName, 0, 1);

	layout->addWidget(new QLabel(tr("位置:")), 1, 0);
	m_location = new QComboBox;
	m_location->setEditable(false);
	m_location->addItem(tr("顶部"));
	m_location->addItem(tr("左边"));
	m_location->addItem(tr("右边"));
	m_location->addItem(tr("底部"));
	m_location->addItem(tr("保留"));
	layout->addWidget(m_location, 1, 1);

	QHBoxLayout *buttonLayout = new QHBoxLayout;
	layout->addLayout(buttonLayout, 2, 0, 1, 2);
	buttonLayout->addStretch();

	QPushButton *okButton = new QPushButton(tr("确定"));
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	buttonLayout->addWidget(okButton);

	QPushButton *cancelButton = new QPushButton(tr("取消"));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
	buttonLayout->addWidget(cancelButton);

	okButton->setDefault(true);
}

QString CreateDockWidgetDialog::objectName() const
{
	return m_objectName->text();
}

Qt::DockWidgetArea CreateDockWidgetDialog::location() const
{
	switch (m_location->currentIndex()) 
	{
	case 0: return Qt::TopDockWidgetArea;
	case 1: return Qt::LeftDockWidgetArea;
	case 2: return Qt::RightDockWidgetArea;
	case 3: return Qt::BottomDockWidgetArea;
	default:
		break;
	}
	return Qt::NoDockWidgetArea;
}

#endif