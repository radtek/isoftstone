#ifndef TREEVIEW_H  
#define TREEVIEW_H

#include <QTreeView>

class CTreeView : public QTreeView
{
public:
	CTreeView(){}
	~CTreeView(){}

protected:
	virtual void mousePressEvent(QMouseEvent *event);
};

#endif