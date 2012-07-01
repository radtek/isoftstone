
#ifndef STRUCT_H
#define STRUCT_H

#include <QPixmap>
#include <QColor>

struct QThree
{
	QThree& operator=(const QThree& three)
	{
		this->rotate = three.rotate;
		this->scale_x = three.scale_x;
		this->scale_y = three.scale_y;
		return *this;
	}

	qreal rotate;
	qreal scale_x;
	qreal scale_y;
};

inline QDataStream & operator<< ( QDataStream & stream, const QThree & three )
{
	stream << three.rotate;
	stream << three.scale_x;
	stream << three.scale_y;
	return stream;
}

inline QDataStream & operator>> ( QDataStream & stream, QThree & three )
{
	stream >> three.rotate;
	stream >> three.scale_x;
	stream >> three.scale_y;
	return stream;
}

struct SData_Struct 
{
	quint64 appID;
	quint64 keyID;
	int		terminalID;
	uint	nodeID;
	quint64	objID;
};

// Í¼ÔªÐÅÏ¢
struct SItemInfo
{
	SItemInfo()
	{
		bDynamic = true;
		bSingle = true;
	}

	bool	bDynamic;
	bool	bSingle;
};

struct SLayerInfo
{
	SLayerInfo():backColor(QColor(0,0,0))
	{
		x = 0;
		y = 0;
		width = 1024;
		height = 512;
		backPixmapFlag = 0;
		initAppID = 10000;
		backPixmapName = "";
		id = -1;
		name = "";
		show = 1;
	}

	int x;
	int y;
	int	width;
	int height;
	int backPixmapFlag;
	int initAppID;
	int initAppAvailable;
	QColor backColor;
	QString backPixmapName;
	int id;
	QString name;
	int show;
};

#endif