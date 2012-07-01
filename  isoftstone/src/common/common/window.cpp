
#include <QAction>
#include <QIcon>

#include "resource.h"
#include "window.h"

CWindow::CWindow()
{

}

void CWindow::addCellWidget(int ,const QPixmap& ,const QString& )
{

}

void CWindow::addCellWidget(int id,const QString& image,const QString& label)
{
	Q_UNUSED(id);
	Q_UNUSED(image);
	Q_UNUSED(label);

// 	m_pixmapMap[label] = QPixmap(image);
// 		
// 	QGridLayout *layout = NULL;
// 	QButtonGroup* buttonGroup = NULL;
// 	if (m_toolWidget.contains(id))
// 	{
// 		layout = dynamic_cast<QGridLayout*>(m_toolWidget[id]->layout());
// 		buttonGroup = m_buttonGroups[id];
// 		m_buttonCount[id]++;
// 	}
// 	else
// 	{
// 		buttonGroup = new QButtonGroup(this);
// 		connect(buttonGroup, SIGNAL(buttonClicked(QAbstractButton*)), this, SLOT(toolButtonGroupClicked(QAbstractButton*)));
// 		layout = new QGridLayout;
// 		m_buttonCount[id] = 0;
// 		m_buttonGroups[id] = buttonGroup;
// 
// 		QWidget *subWidget = new QWidget;
// 		subWidget->setLayout(layout);
// 		m_toolWidget[id] = subWidget;
// 		
// 	}
// 	int count = m_buttonCount[id];
// 	layout->addWidget(CResource::createCellWidget(buttonGroup,label,image), count /2 ,count % 2  );
// 
// 	layout->setRowStretch(count /2 +1, 10);
// 	layout->setColumnStretch(count % 2 + 1, 10);

}

QAction* CWindow::createAction(const SAction& stAction)
{
	QAction* action = new QAction(QIcon(stAction.image),stAction.text, stAction.parent);
	action->setShortcut(stAction.shortCut);
	action->setStatusTip(stAction.tip);
	QObject::connect(action, SIGNAL(triggered()),stAction.receiver, stAction.slot.toLocal8Bit().data());
	return action;
}

int CWindow::getToolBox(QButtonGroup* buttonGroup)
{
	QMapIterator<int,QButtonGroup*> iter(m_buttonGroups);
	while(iter.hasNext())
	{
		iter.next();
		if (iter.value() == buttonGroup)
		{
			return iter.key();
		}
	}
	return -1;
}