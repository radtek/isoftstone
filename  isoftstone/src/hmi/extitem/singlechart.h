#ifndef SINGLE_CHART1_H
#define SINGLE_CHART1_H

#define TEXT_BOX_SPACE 5
#define X_INCREMENT 5
#define POINT_RADIUS 3

#include <QtGui>

#include "extitem.h"

class EXPORT_EXTITEM CSingleChart : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit CSingleChart(QGraphicsItem *parent = 0);

public slots:
    void addData(qreal data);

    void setUseAntialiasing(bool use);

    bool getUseAntialiasing() const;

    void setHorizontalLineColor(const QColor& clr);

    void setShowPoint(bool show);

    void setTitle(const QString& str);

	QRectF boundingRect() const;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    void resetVariables(QPainter* painter);
    void drawBackground(QPainter* painter);
    void drawBox(QPainter* painter);
    void drawText(QPainter* painter);
    void drawGraph(QPainter* painter);
    void drawTitle(QPainter* painter);

private:
    qreal            m_leftSpace;
    qreal            m_topSpace;
    QVector<qreal>   m_dataVec;
    QVector<QPointF> m_potVec;
    bool             m_bUseAntialiasing;
    bool             m_bShowHLine;
    bool             m_bShowPoint;
    QRectF           m_topRect;
    QRectF           m_bottomRect;
    QRectF           m_boxRect;
    QColor           m_hLineClr;
    QString          m_strTitle;

    void initVariables();
    void updateVector();

};

#endif // MYCHART1_H
