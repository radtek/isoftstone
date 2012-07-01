
#ifndef COLOR_FRAME_H
#define COLOR_FRAME_H

#include <QSpinBox>
#include <QColor>
#include <QString>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDialog>
#include <QLabel>
#include <QFrame>

#include "customdef.h"

EXPORT_WIDGET QColor bgColorForName(const QString &name);

EXPORT_WIDGET QColor fgColorForName(const QString &name);

EXPORT_WIDGET QSpinBox *createSpinBox(int value, QWidget *parent, int max = 1000);

class EXPORT_WIDGET ChangeDialog : public QDialog
{
public:

	ChangeDialog(QWidget* pWid,QWidget* parent = 0);
	
	QSize getSize();

private:

	QSpinBox *szHintW;
	QSpinBox *minSzHintW;
	QSpinBox *minSzHintH;
	QSpinBox *maxSzW;
	QSpinBox *maxSzH;
	QSpinBox *dwMaxSzW;
	QSpinBox *dwMaxSzH;
	QSpinBox *szHintH;
	
	QSize maxSz;
	QSize dwMaxSz;
};

class EXPORT_WIDGET ColorFrame : public QFrame
{
	Q_OBJECT
public:
	ColorFrame(const QString &c, QWidget *parent = 0);

	virtual QSize sizeHint() const;
	virtual QSize minimumSizeHint() const;

protected:
	void contextMenuEvent(QContextMenuEvent *event);
	void paintEvent(QPaintEvent *);

	QString color;
	QSize szHint, minSzHint;
};

#endif