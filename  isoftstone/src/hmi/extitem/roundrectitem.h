
#include "extitem.h"

class EXPORT_EXTITEM RoundRectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:

    RoundRectItem( const QRectF & rect, const QBrush & brush, QWidget* embeddedWidget = 0 );

    QRectF boundingRect() const;

    void setPixmap( const QPixmap & pixmap );

    qreal opacity() const;

    void setOpacity( qreal opacity );

    void setBorderWidth( qreal width );

    void setRoundBorder( bool round );

    void setBorderBrush( const QBrush& brush );

protected:
    void paint( QPainter* painter, const QStyleOptionGraphicsItem*, QWidget* );

private:
    QBrush m_brush;
    QPixmap m_pixmap;
    qreal m_opacity;

    qreal m_borderWidth;
    bool m_roundBorder;

    QGraphicsProxyWidget* m_proxyWidget;
};
