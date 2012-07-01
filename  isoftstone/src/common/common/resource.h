
#ifndef ITEM_RESOURCE_H
#define ITEM_RESOURCE_H

#include <QtGui>

#include "common.h"

class EXPORT_COMMON CResource
{
public:

	static QIcon createColorIcon(QColor color);

	static QIcon createColorToolButtonIcon(const QString &imageFile,QColor color);

	static QPixmap createPixmap(const QPolygonF& polygon ,const QColor& color );

	static QMenu* createColorMenu(QWidget* parent,const char *slot, QColor defaultColor);

	static QWidget* createCellWidget(QButtonGroup* buttonGroup,const QString &text,const QString &image);

	static QWidget* createCellWidget(QButtonGroup* buttonGroup,const QString &text,const QPixmap& image,int type);

};

#endif
