#ifndef TIP_FRAME_H_
#define TIP_FRAME_H_

#include <qframe.h>
#include <qstring.h>

#include "customdef.h"

class EXPORT_WIDGET CTipFrame : public QFrame  
{
	Q_OBJECT
public:
	CTipFrame(QWidget * parent = 0);
	virtual ~CTipFrame();

	void setText(const QString& strText);
	QString getText();
	void tipShow(const QPoint& point);
	void tipShow(const int x, const int y);

protected:
	void update();
	virtual void drawFrame (QPainter * p);
	virtual void paintEvent(QPaintEvent * event);

private:
	QString m_strText;
};

#endif //TIPWND_H_
