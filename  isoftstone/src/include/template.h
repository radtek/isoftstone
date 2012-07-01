
#ifndef TEMPLATE_H
#define TEMPLATE_H

#include <QString>
#include <QVariant>
#include <QMap>
#include <QMapIterator>
#include <QDebug>

template<class TKey,class TValue>
QMap<TKey,TValue> convertMap(const QMap<QString,QVariant>& mapVar)
{
	QMap<TKey,TValue> map;
	QMapIterator<QString,QVariant> iter(mapVar);
	while (iter.hasNext())
	{
		iter.next();
		TKey key = qvariant_cast<TKey>(qVariantFromValue(iter.key()));
		TValue value = qvariant_cast<TValue>(iter.value());
		map.insert(key,value);
	}
	return map;
}

#endif