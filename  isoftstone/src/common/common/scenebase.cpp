
#include <QPainter>
#include <QSvgGenerator>
#include <QGraphicsSvgItem>

#include "scenebase.h"

CGraphicsSceneBase::CGraphicsSceneBase(QObject *parent) : QGraphicsScene(parent)
{

}

void CGraphicsSceneBase::setTextColor(const QColor &color)
{
	m_FontColor = color;
	foreach(QGraphicsItem* tmp,selectedItems())
	{
		QGraphicsTextItem* item = dynamic_cast<QGraphicsTextItem *>(tmp);
		if (item)
		{
			item->setDefaultTextColor(color);
		}
	}
}

void CGraphicsSceneBase::setItemColor(const QColor &color)
{
	m_FillColor = color;
	foreach(QGraphicsItem* tmp,selectedItems())
	{
		QGraphicsPolygonItem* item = dynamic_cast<QGraphicsPolygonItem *>(tmp);
		if (item)
		{
			item->setBrush(color);
		}
	}
}

void CGraphicsSceneBase::setFont(const QFont &font)
{
	foreach(QGraphicsItem* tmp,selectedItems())
	{
		QGraphicsTextItem* item = dynamic_cast<QGraphicsTextItem *>(tmp);
		if (item)
		{
			item->setFont(font);
		}
	}
}

void CGraphicsSceneBase::openSvg(const QString &file)
{
	if (!QFile::exists(file))
		return;

	bool drawBackground = true;
	bool drawOutline = true;

	clear();

	m_svgItem = new QGraphicsSvgItem(file);
	m_svgItem->setFlags(QGraphicsItem::ItemClipsToShape);
	m_svgItem->setCacheMode(QGraphicsItem::NoCache);
	m_svgItem->setZValue(0);

	m_backgroundItem = new QGraphicsRectItem(m_svgItem->boundingRect());
	m_backgroundItem->setBrush(Qt::white);
	m_backgroundItem->setPen(Qt::NoPen);
	m_backgroundItem->setVisible(drawBackground);
	m_backgroundItem->setZValue(-1);

	m_outlineItem = new QGraphicsRectItem(m_svgItem->boundingRect());
	QPen outline(Qt::black, 2, Qt::DashLine);
	outline.setCosmetic(true);
	m_outlineItem->setPen(outline);
	m_outlineItem->setBrush(Qt::NoBrush);
	m_outlineItem->setVisible(drawOutline);
	m_outlineItem->setZValue(1);

	addItem(m_backgroundItem);
	addItem(m_svgItem);
	addItem(m_outlineItem);

	setSceneRect(m_outlineItem->boundingRect().adjusted(-10, -10, 10, 10));
}

void CGraphicsSceneBase::saveSvg(const QString& newPath)
{
	QSvgGenerator generator;
	generator.setFileName(newPath);
	generator.setSize(QSize(1000, 1000));
	generator.setViewBox(QRect(0, 0, 1000, 1000));
	generator.setTitle(tr("SVG Save"));
	generator.setDescription(tr("svg"));

	QPainter printer;
	printer.begin(&generator);
	render(&printer);
	printer.end();
}