
#pragma once

#include <QtGui>

#include <QDeclarativePropertyMap>
#include <QDeclarativeView>
#include <QDeclarativeContext>
#include <QDeclarativeEngine>
#include <QDeclarativeComponent>

class CQMLView : public QDeclarativeView
{
public:

	CQMLView();

protected:

	virtual void timerEvent(QTimerEvent* event);

private:

	void init();
	void refresh();
	void updateValue();

private:

	int			m_timerID;

	QDeclarativePropertyMap	m_propertyMap;

	QDeclarativeContext*	m_context;


};