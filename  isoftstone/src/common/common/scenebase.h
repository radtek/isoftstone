
#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "common.h"

class EXPORT_COMMON CGraphicsSceneBase : public QGraphicsScene
{
public:

	CGraphicsSceneBase(QObject *parent);

	void setTextColor(const QColor &color);

	void setItemColor(const QColor &color);

	void setFont(const QFont &font);

	void openSvg(const QString &file);

	void saveSvg(const QString& newPath);

protected:

	QColor m_FillColor;
	QColor m_LineColor;
	QColor m_FontColor;
	QFont  m_Font;

	QGraphicsItem *m_svgItem;
	QGraphicsRectItem *m_backgroundItem;
	QGraphicsRectItem *m_outlineItem;
};

#endif