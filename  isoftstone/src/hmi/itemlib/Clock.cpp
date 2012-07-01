
#include "Clock.h"

#include <QLCDNumber>
#include <QDateTime>
#include <QPalette>

CClock::CClock(QGraphicsItem* parent):QGraphicsProxyWidget(parent)
{
}

CClock::CClock(const Clock_Struct& attrInfo,QGraphicsItem* parent):QGraphicsProxyWidget(parent)
{
	m_Info = attrInfo;
}

CClock::~CClock()
{
	if (m_timerID > -1)
	{
		killTimer(m_timerID);
	}
}

int	 CClock::type() const
{
	return CIMGClock;
}

void CClock::init() 
{
	m_lcd = new QLCDNumber;
	m_lcd->setSegmentStyle(QLCDNumber::Filled);
	m_lcd->setDigitCount(8);

	m_digit = m_Info.IsDigital.toInt();
	
	if (m_digit == 3)
	{
		m_timerID = startTimer(30000);
	}
	else
	{
		m_timerID = startTimer(1000);
	}
	QPalette pal;
	pal.setColor(QPalette::Base,QColor(0,0,0,0));
	pal.setColor(QPalette::Foreground,m_Info.fc);
	pal.setColor(QPalette::Window, QColor (0, 0 , 0, 0));
	setPalette(pal);

	m_lcd->setFrameShadow(QFrame::Plain);
	m_lcd->setFrameShape(QFrame::NoFrame);
	m_lcd->resize(m_Info.w,m_Info.h);
	setWidget(m_lcd);

	update();
}

QGraphicsItem* CClock::clone(void)
{
	CClock* clock = new CClock();
	return clock;
}

void CClock::draw()
{
	setPos(m_Info.x,m_Info.y);
}

void CClock::update()
{
	QDateTime dt = QDateTime::currentDateTime();
	QString strValue = "";
	// ÈÕÆÚ
	if (m_digit == 3)
	{
		strValue  = dt.toString("yyyy-MM-dd");
	}
	else
	{
		strValue  = dt.toString("HH:mm:ss");
	}
	m_lcd->display(strValue);
}

void CClock::timerEvent(QTimerEvent * )
{
	update();
}