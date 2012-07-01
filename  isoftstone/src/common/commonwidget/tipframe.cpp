#include <qpainter.h>
#include <qpalette.h>
#include <qpen.h>
#include <qrect.h>
#include <qsize.h>

#include "tipframe.h"

using namespace Qt;

CTipFrame::CTipFrame(QWidget *parent): QFrame(parent)
{
	QPalette pal;
	pal.setColor(QPalette::Background,QColor(255,255,231));
	setPalette(pal);
}

CTipFrame::~CTipFrame()
{
}

void CTipFrame::setText(const QString &strText)
{
	m_strText = strText;
	update();
}

QString CTipFrame::getText()
{
	return m_strText;
}

void CTipFrame::tipShow(const QPoint& point)
{
	tipShow(point.x(), point.y());
}

void CTipFrame::tipShow(const int x, const int y)
{
	QSize	sizeTip = size();
	QSize	sizeParent = parentWidget()->size();
	int		nOffsetX = x + sizeTip.width() - sizeParent.width();
	int		nOffsetY = y + sizeTip.height() - sizeParent.height();
	int		x1 = (nOffsetX > 0) ? x - nOffsetX : x;
	int		y1 = (nOffsetY > 0) ? y - nOffsetY : y;
	move(x1, y1);
	show();
}

void CTipFrame::update()
{
	QPainter	painter(this);
	QRect	rectFrame(0, 0, 1023, 20);
	rectFrame = painter.boundingRect(rectFrame,
		AlignLeft | AlignTop | TextExpandTabs | TextWordWrap,
		m_strText);
	rectFrame.adjust(0, 0, 6, 6);
	setFixedSize(rectFrame.size());
	
	rectFrame.adjust(1, 1, -1, -1);
	repaint(rectFrame);
}

void CTipFrame::drawFrame(QPainter *p)
{
	QPen pen(Qt::black, 1);
	p->setPen(pen);
	p->drawRect(frameRect());
}

void CTipFrame::paintEvent(QPaintEvent * event)
{
	QPainter p;
	QPen	pen(Qt::black, 1);
	QRect	rectText = frameRect();
	rectText.adjust(4, 3, -1, -1);
	p.setPen(pen);
	p.drawText(rectText, 
		Qt::AlignLeft | Qt::AlignTop | Qt::TextExpandTabs | Qt::TextWordWrap, 
		m_strText);
	drawFrame(&p);
}
