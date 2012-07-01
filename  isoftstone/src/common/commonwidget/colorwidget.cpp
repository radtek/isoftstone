
#include <QPainter>
#include <QBrush>

#include "colorwidget.h"
#include "ialgorithm.h"

CColorWidget::CColorWidget()
{
	resize(300, 200);
	m_Smooth = true;

	float f = -1*0.1;
	while (f < 1.0)
	{
		f += 0.1;
		m_vecData.append(f);
	}
}

void CColorWidget::paintEvent(QPaintEvent *)
{
	paintSmooth();
	paintSection();
}

void CColorWidget::paintSmooth()
{
	QPainter painter(this);

	painter.save();

	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(0, height() / 2);

	painter.setPen(Qt::NoPen);
	
	QRect rect = QRect(0,30,m_vecData.count()*20,20);
	QLinearGradient liner(rect.topLeft(),rect.bottomRight());
	for (int i = 0; i < m_vecData.count(); ++i)
	{
		float f = m_vecData[i];

		float r = colorMapped('R',f,m_Smooth);
		float g = colorMapped('G',f,m_Smooth);
		float b = colorMapped('B',f,m_Smooth);

		QColor color = QColor::fromRgbF(r,g,b);
		liner.setColorAt((double)(i+1)/m_vecData.count(),color);
	}
	painter.setBrush(liner);	
	painter.drawRect(rect);
	painter.restore();
}

void CColorWidget::paintSection()
{
	QPainter painter(this);

	painter.save();

	painter.setRenderHint(QPainter::Antialiasing);
	painter.translate(0, height() / 2);
	//painter.scale(side / 200.0, side / 200.0);

	painter.setPen(Qt::NoPen);

	for (int i = 0; i < m_vecData.count(); ++i)
	{
		float f = m_vecData[i];

		float r = colorMapped('R',f,m_Smooth);
		float g = colorMapped('G',f,m_Smooth);
		float b = colorMapped('B',f,m_Smooth);

		//QColor color = QColor::fromRgbF(r*255,g*255,b*255);
		QColor color = QColor::fromRgbF(r,g,b);
		QBrush brush(color);
		brush.setStyle(Qt::LinearGradientPattern);
		painter.setBrush(brush);
		//painter.setPen(color);

		painter.drawRect(i*20, 0, 20, 20);
	}

	painter.restore();
}
