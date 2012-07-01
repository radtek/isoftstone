
#include "qmlmainwindow.h"

CQMLView::CQMLView():QDeclarativeView()
{
	m_timerID = startTimer(1000);
	srand(100);

	m_context = rootContext();

	init();
	m_context->setContextProperty("pmap",&m_propertyMap);
}

void CQMLView::init()
{
	m_propertyMap.insert("l_rate",0);
	m_propertyMap.insert("l_in_press",0);
	m_propertyMap.insert("l_out_press",0);
	m_propertyMap.insert("l_shrink",0);

	m_propertyMap.insert("r_rate",0);
	m_propertyMap.insert("r_in_press",0);
	m_propertyMap.insert("r_out_press",0);
	m_propertyMap.insert("r_shrink",0);
}

void CQMLView::updateValue()
{
	foreach (QString key,m_propertyMap.keys())
	{
		m_propertyMap[key] = rand();
	}

	refresh();
}

void CQMLView::refresh()
{
	m_context->setContextProperty("pmap",&m_propertyMap);
}

void CQMLView::timerEvent(QTimerEvent* event)
{
	if (event->timerId() == m_timerID)
	{
		updateValue();
	}
}