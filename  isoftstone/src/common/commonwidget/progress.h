#ifndef PROGRESSINDICATOR_H
#define PROGRESSINDICATOR_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include "customdef.h"

#define PI_RECT_COUNT 20
#define PI_EXTRA_SPACE 2
#define PI_ANGLE_RADIUS 7

class EXPORT_WIDGET CProgressBar : public QWidget
{
Q_OBJECT
public:
    explicit CProgressBar(QWidget *parent = 0);


public slots:
    void setRange(int min,int max);

    void setValue(int value);
protected:
    void paintEvent(QPaintEvent *);

    QSize sizeHint() const
    {
        return QSize(200,30);
    }

    QSize minimumSizeHint() const
    {
        return QSize(120,10);
    }

private:

    void drawBackground(QPainter* painter);
    void drawRects(QPainter* painter);


private:
    int m_nMin;
	int m_nMax;
	int m_nCurrValue;


private:
    void initVariables();

Q_SIGNALS:
    void sig_Finished();

};

#endif // PROGRESSINDICATOR_H
