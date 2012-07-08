
#ifndef DATA_WIDGET_H
#define DATA_WIDGET_H

#include "tablelist.h"
#include "datatable.h"

class CDataWidget : public QWidget
{
	Q_OBJECT

public:

	CDataWidget(QObject* parent = 0);
	~CDataWidget();

private:

	CRtTableView*	m_tableList;
	CDataTable*		m_dataTable;
};

#endif