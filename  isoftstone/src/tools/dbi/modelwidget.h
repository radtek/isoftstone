
#ifndef MODEL_WIDGET_H
#define MODEL_WIDGET_H

#include <QtCore>
#include <QWidget>

#include "tabletree.h"
#include "fieldtable.h"

class CModelWidget : public QWidget
{
	Q_OBJECT

public:

	CModelWidget(QObject* parent = 0);
	~CModelWidget();

private:

	CTableTree*		m_tableTree;
	CFieldTable*	m_fieldTable;
};

#endif