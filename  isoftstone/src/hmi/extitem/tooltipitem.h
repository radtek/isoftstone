#ifndef INFOMATIONITEM_H
#define INFOMATIONITEM_H

#include "extitem.h"

#define PICTURE_SIZE 150

class EXPORT_EXTITEM CToolTipItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    CToolTipItem(const QRectF &rect, const QPixmap &pix, const QString &strText = QString(""), QGraphicsItem *parent = 0);

    CToolTipItem(QGraphicsItem *parent = 0);

    QRectF boundingRect()const;

    QPainterPath shape() const;

    void setRect(const QRectF &rect);

    void setPixmap(const QPixmap &pix);

    void setText(const QString &strText);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QString m_strText;
    QPixmap m_pix;
    QPixmap m_background;
    QRectF  m_rectArea;

};

#endif // INFOMATIONITEM_H
