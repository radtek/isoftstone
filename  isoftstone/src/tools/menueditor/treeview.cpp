#include <QDrag>
#include <QMimeData>
#include <QMouseEvent>
#include <QUrl>

#include "treeview.h"

void CTreeView::mousePressEvent(QMouseEvent *event)
{
	// if not left button - return
	QTreeView::mousePressEvent(event);
	if (!(event->buttons() & Qt::LeftButton)) 
	{	
		return;
	}
	// if no item selected, return (else it would crash)
	QModelIndex index = currentIndex();
	if (index.isValid() == false)
	{
		return;
	}

	if (index.parent().isValid() == false)
	{
		return;
	}
	QDrag *drag = new QDrag(this);
	QMimeData *mimeData = new QMimeData;

	// construct list of QUrls
	// other widgets accept this mime type, we can drop to them
	QList<QUrl> list;
	list.push_back(index.parent().child(index.row(), 0).data().toUrl()); 
	list.push_back(index.parent().child(index.row(), 1).data().toUrl());
	// mime stuff
	mimeData->setUrls(list); 
	mimeData->setText("Item");
	drag->setMimeData(mimeData);

	// start drag
	drag->start(Qt::CopyAction | Qt::MoveAction);
}