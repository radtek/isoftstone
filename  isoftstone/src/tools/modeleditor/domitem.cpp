#include <QtXml>

#include "domitem.h"

//! [0]
DomItem::DomItem(QDomNode &node, int row, DomItem *parent)
{
	domNode = node;
	//! [0]
	// Record the item's location within its parent.
	//! [1]
	rowNumber = row;
	parentItem = parent;
}
//! [1]

//! [2]
DomItem::~DomItem()
{
	QHash<int,DomItem*>::iterator it;
	for (it = childItems.begin(); it != childItems.end(); ++it)
		delete it.value();
}
//! [2]

//! [3]
QDomNode DomItem::node() const
{
	return domNode;
}
//! [3]

//! [4]
DomItem *DomItem::parent()
{
	return parentItem;
}
//! [4]

//! [5]
DomItem *DomItem::child(int i)
{
	if (childItems.contains(i))
		return childItems[i];

	if (i >= 0 && i < domNode.childNodes().count()) 
	{
		QDomNode childNode = domNode.childNodes().item(i);
		DomItem *childItem = new DomItem(childNode, i, this);
		childItems[i] = childItem;
		return childItem;
	}
	return 0;
}
//! [5]

//! [6]
int DomItem::row()
{
	return rowNumber;
}
//! [6]

