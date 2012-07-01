
#ifndef COMMON_DIALOG_H
#define COMMON_DIALOG_H

#include <QWidget>
#include <QVector>

#include "customdef.h"

class EXPORT_WIDGET CColorWidget : public QWidget
{
public:

	CColorWidget();

protected:

	virtual void paintEvent(QPaintEvent *);

	void paintSmooth();

	void paintSection();

private:

	QVector<float> m_vecData;
	bool	m_Smooth;
};

#endif