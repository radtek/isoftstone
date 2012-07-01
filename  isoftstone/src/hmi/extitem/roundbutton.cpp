#include "roundbutton.h"

CRoundButton::CRoundButton(const QPixmap &pixmap, QGraphicsItem *parent) :
			  QGraphicsWidget(parent), m_pix(pixmap)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}
CRoundButton::CRoundButton(const QString &strText, QGraphicsItem *parent):
			 QGraphicsWidget(parent), m_strText(strText)
{
    setAcceptHoverEvents(true);
    setCacheMode(DeviceCoordinateCache);
}

QRectF CRoundButton::boundingRect() const
{
	return QRectF(-65, -65, 130, 130);
}

QPainterPath CRoundButton::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}
void CRoundButton::setText(const QString &str)
{
	m_strText = str;
}

void CRoundButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
	bool down = option->state & QStyle::State_Sunken;
	QRectF r = boundingRect();
	QLinearGradient grad(r.topLeft(), r.bottomRight());
	grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);
	grad.setColorAt(down ? 0 : 1, Qt::darkGray);
	painter->setPen(Qt::darkGray);
	painter->setBrush(grad);
	painter->drawEllipse(r);
	QLinearGradient grad2(r.topLeft(), r.bottomRight());
	grad.setColorAt(down ? 1 : 0, Qt::darkGray);
	grad.setColorAt(down ? 0 : 1, Qt::lightGray);
	painter->setPen(Qt::NoPen);
	painter->setBrush(grad);
	if (down)
		painter->translate(2, 2);
	painter->drawEllipse(r.adjusted(5, 5, -5, -5));
	if(!m_pix.isNull())
		painter->drawPixmap(-m_pix.width()/2, -m_pix.height()/2, m_pix);
	if(!m_strText.isEmpty())
	{
		painter->save();

		QFont font(qApp->font());
		font.setPointSize(20);
		painter->setFont(font);
		painter->setPen(Qt::red);
		painter->drawText(r, Qt::AlignCenter, m_strText);
		painter->restore();
		qDebug() << m_strText;
	}
}

void CRoundButton::mousePressEvent(QGraphicsSceneMouseEvent *)
{
	emit pressed();
	update();
}

void CRoundButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
	update();
}
