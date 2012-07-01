
#include "tooltipitem.h"

const QString STR_BACKGROUND = ":/images/details.png";

CToolTipItem::CToolTipItem(const QRectF &rect, const QPixmap &pix, const QString &strText, QGraphicsItem *parent) :
    QGraphicsItem(parent), m_rectArea(rect), m_pix(pix), m_strText(strText)
{
    setCacheMode(DeviceCoordinateCache);
    m_background = QPixmap(STR_BACKGROUND);
}

CToolTipItem::CToolTipItem(QGraphicsItem *parent):QGraphicsItem(parent)
{
    setCacheMode(DeviceCoordinateCache);
    m_background = QPixmap(STR_BACKGROUND);
}

QRectF CToolTipItem::boundingRect()const
{
	return m_rectArea;
}
QPainterPath CToolTipItem::shape() const
{
	QPainterPath path;
	path.addRect(boundingRect());
	return path;
}
void CToolTipItem::setRect(const QRectF &rect)
{
	m_rectArea = rect;
}

void CToolTipItem::setPixmap(const QPixmap &pix)
{
	m_pix = pix.scaled(PICTURE_SIZE, PICTURE_SIZE);
}

void CToolTipItem::setText(const QString &strText)
{
	m_strText = strText;
}

void CToolTipItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF textRectArea(m_rectArea);
    painter->drawPixmap( m_rectArea,
                         m_background,
                         QRectF(0,0,m_background.width(), m_background.height()));
    if(!m_pix.isNull())
    {
        QRectF pixRectArea(m_rectArea.left() + (m_rectArea.width()- m_pix.width())/2,
                m_rectArea.top() + 50, m_pix.width(), m_pix.height());
        painter->drawPixmap(pixRectArea.left(), pixRectArea.top(), m_pix);
        textRectArea.setTop(pixRectArea.bottom());
        textRectArea.setHeight(textRectArea.height() - pixRectArea.height());
    }
    if(!m_strText.isNull() && !m_strText.isEmpty())
    {
        QFont font(qApp->font());
        font.setPointSize(15);
        painter->save();
        painter->setPen(Qt::darkGray);
        painter->setFont(font);
        painter->drawText(textRectArea, Qt::AlignCenter, m_strText);
        painter->restore();
    }
}
