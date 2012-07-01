#ifndef ROUNDBUTTON_H
#define ROUNDBUTTON_H

#include "extitem.h"

class EXPORT_EXTITEM CRoundButton : public QGraphicsWidget
{
    Q_OBJECT

public:

    CRoundButton(const QPixmap &pixmap, QGraphicsItem *parent = 0);

    CRoundButton(const QString &strText, QGraphicsItem *parent = 0);

    QRectF boundingRect() const;

    QPainterPath shape() const;

    void setText(const QString &str);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

signals:
    void pressed();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *);

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:

    QPixmap m_pix;
    QString m_strText;
};

#endif // BUTTON_H
