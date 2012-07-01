
#ifndef MENU_SORT_H
#define MENU_SORT_H

#include <QSortFilterProxyModel>

class CCommandSortProxy : public QSortFilterProxyModel
{
public:
	CCommandSortProxy(){};

protected:

	virtual void sort(int column, Qt::SortOrder order = Qt::AscendingOrder)
	{
		QSortFilterProxyModel::sort(column,order);
	}

	virtual bool lessThan ( const QModelIndex & left, const QModelIndex & right )
	{
		if (left.column() == 1 && right.column() == 1)
		{
			QVariant leftValue = sourceModel()->data(left,Qt::EditRole);
			QVariant rightValue = sourceModel()->data(right,Qt::EditRole);

			if (leftValue.toUInt() < rightValue.toUInt())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return QSortFilterProxyModel::lessThan(left,right);
	}

};

#endif