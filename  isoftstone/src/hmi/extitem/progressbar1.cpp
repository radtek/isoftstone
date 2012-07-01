#include "progressbar1.h"

CProgressBar1::CProgressBar1(QGraphicsItem *parent) :QGraphicsObject(parent)
{
    initVariables();
}

void CProgressBar1::initVariables()
{
    m_min = 0;
    m_max = 100;
    m_value = 0;
}

QRectF CProgressBar1::boundingRect() const
{
	return QRectF(0,0,400,50);
}	

void CProgressBar1::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    drawBg(painter);
    drawBar(painter);
}

void CProgressBar1::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(PYP_BG_COLOR);

    QLinearGradient BgGradient(QPoint(0,0),QPoint( boundingRect().width(),0));
    BgGradient.setColorAt(0.0,QColor(222,222,222));
    BgGradient.setColorAt(0.05,PYP_BG_COLOR);
    BgGradient.setColorAt(1.0,PYP_BG_COLOR);
    painter->setBrush(BgGradient);
    painter->drawRoundedRect(boundingRect(),PYP_RECT_RADIUS,PYP_RECT_RADIUS);

    painter->restore();
}

void CProgressBar1::drawBar(QPainter *painter)
{
    painter->save();

    // DRAW UNDER BAR
    painter->setPen(Qt::NoPen);

    QPointF uTopLeft(PYP_LEFT_SPACE1,PYP_TOP_SPACE1);
    QPointF uBottomRight(boundingRect().width() - PYP_RIGHT_SPACE1 * 2 - PYP_TEXT_WIDTH,boundingRect().height() - PYP_TOP_SPACE1);
    QRectF uRect(uTopLeft,uBottomRight);
    painter->setBrush(PYP_UNDER_BAR_COLOR);
    painter->drawRoundedRect(uRect,PYP_RECT_RADIUS,PYP_RECT_RADIUS);


    //  DRAW REAL BAR
    qreal range = (m_max - m_min);
    qreal RectWidth = boundingRect().width() - PYP_LEFT_SPACE1  - PYP_RIGHT_SPACE1 * 2 - PYP_TEXT_WIDTH;
    qreal dX = (qreal) RectWidth/range;


    qreal initX = PYP_LEFT_SPACE1;
    QPointF TopLeft(initX,PYP_TOP_SPACE1);
    QPointF BottomRight(initX + dX * m_value,boundingRect().height() - PYP_TOP_SPACE1);
    QRectF BarRect(TopLeft,BottomRight);

    QLinearGradient BarGradient(uRect.topLeft(),uRect.topRight());
    BarGradient.setColorAt(0.0,PYP_BAR_START_COLOR);
    BarGradient.setColorAt(0.5,PYP_BAR_MIDDLE_COLOR);
    BarGradient.setColorAt(1.0,PYP_BAR_END_COLOR);

    painter->setBrush(BarGradient);

    painter->drawRoundedRect(BarRect,PYP_RECT_RADIUS,PYP_RECT_RADIUS);

    // DRAW COVER LINES

    int nLineCnt = uRect.width()/PYP_D_LINE;
    int dLineX = (qreal)uRect.width()/(nLineCnt - 1);
    painter->setPen(PYP_LINE_COLOR);
    while(initX < uRect.width())
    {
        QPointF topPot(initX + dLineX,PYP_TOP_SPACE1);
        QPointF bottomPot(initX + dLineX,boundingRect().height() - PYP_TOP_SPACE1);
        painter->drawLine(topPot,bottomPot);

        /// increment initX
        initX += dLineX;

    }

    // draw text
    QPointF TextTopLeft(boundingRect().width() - PYP_RIGHT_SPACE1 - PYP_TEXT_WIDTH,PYP_TOP_SPACE1);
    QPointF TextBottomRight(boundingRect().width() - PYP_RIGHT_SPACE1,boundingRect().height() - PYP_TOP_SPACE1);
    QRectF TextRect(TextTopLeft,TextBottomRight);
    painter->setPen(PYP_UNDER_BAR_COLOR);
    painter->setBrush(PYP_UNDER_BAR_COLOR);
    painter->drawRoundedRect(TextRect,PYP_RECT_RADIUS,PYP_RECT_RADIUS);

    painter->setPen(PYP_TEXT_COLOR);

    QFont TextFont("Times New Roman");
    TextFont.setBold(true);
    painter->setFont(TextFont);

    QString strText;
    qreal value = (qreal)m_value * 100/(m_max - m_min);
    strText = tr("%1%").arg(value,3,'f',1,'0');
    painter->drawText(TextRect,strText,Qt::AlignVCenter|Qt::AlignHCenter);
    painter->restore();
}

void CProgressBar1::setRange(qreal min, qreal max)
{
    Q_ASSERT(min < max);
    m_min = min;
    m_max = max;
    update();
}

void CProgressBar1::setValue(qreal value)
{
    m_value = value;
    update();
}

