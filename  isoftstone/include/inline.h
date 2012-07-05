#ifndef INLINE_H
#define INLINE_H

#include <QGraphicsItem>

#include "interface.h"


inline QDataStream& operator<<(QDataStream& out,const ISerialize* item)
{
	item->serialize(out);
	return out;
}

inline  QDataStream& operator>>( QDataStream& out,ISerialize* item)
{
	item->deserialize(out);
	return out;
}

inline QDataStream& operator<<(QDataStream& out,const QGraphicsItem& item)
{
	out << item.isVisible();
	out << item.rotation();
	out << item.scale();
	out << item.flags();
	return out;
}

inline  QDataStream& operator>>( QDataStream& out,QGraphicsItem& item)
{
	bool bvisible;
	out >> bvisible;
	item.setVisible(bvisible);

	qreal rotateion;
	out >> rotateion;
	item.setRotation(rotateion);

	qreal scale;
	out >> scale;
	item.setScale(scale);

	qint32 nflags;
	out >> nflags;
	item.setFlags(QGraphicsItem::GraphicsItemFlags(nflags));
	return out;
}

#endif