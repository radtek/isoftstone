
#ifndef WINDOW_H
#define WINDOW_H

#include <QString>
#include <QPixmap>
#include <QMap>
#include <QObject>
#include <QAction>

#include "common.h"

struct SAction
{
	QString image;
	QString text;
	QString shortCut;
	QString tip;
	QWidget* parent;
	QObject* receiver;
	QString slot;
};


class EXPORT_COMMON CWindow 
{

public:

	CWindow();

	void addCellWidget(int id,const QPixmap& pixmap,const QString& label);
	
	void addCellWidget(int id,const QString& image,const QString& label);

	QAction* createAction(const SAction& stAction);

private :

	int getToolBox(QButtonGroup* buttonGroup);

protected:

	QMap<int,QWidget*>		m_toolWidget;

	QMap<int,QButtonGroup*> m_buttonGroups;

	QMap<int,int>			m_buttonCount;

	QMap<QString,QPixmap>	m_pixmapMap;

};

#endif