
#include "resource.h"


QIcon CResource::createColorIcon(QColor color)
{
	QPixmap pixmap(20, 20);
	QPainter painter(&pixmap);
	painter.setPen(Qt::NoPen);
	painter.fillRect(QRect(0, 0, 20, 20), color);

	return QIcon(pixmap);
}

QIcon CResource::createColorToolButtonIcon(const QString &imageFile,QColor color)
{
	QPixmap pixmap(50, 80);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	QPixmap image(imageFile);
	QRect target(0, 0, 50, 60);
	QRect source(0, 0, 42, 42);
	painter.fillRect(QRect(0, 60, 50, 80), color);
	painter.drawPixmap(target, image, source);

	return QIcon(pixmap);
}

QPixmap CResource::createPixmap(const QPolygonF& polygon ,const QColor& color )
{
	QPixmap pixmap(250, 250);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	painter.setPen(QPen(color, 8));
	painter.translate(125, 125);
	painter.drawPolyline(polygon);

	return pixmap;
}

QMenu* CResource::createColorMenu(QWidget* parent,const char *slot, QColor defaultColor)
{
	QStringList names = QColor::colorNames();

	QMenu *colorMenu = new QMenu(parent);
	QString colorName;
	for (int i = 0; i < names.count(); ++i)
	{
		colorName = names.at(i);
		QAction *action = new QAction( colorName , parent);
		QColor color(colorName);
		action->setData(color);
		action->setIcon(createColorIcon(color));
		QObject::connect(action, SIGNAL(triggered()),parent, slot);
		colorMenu->addAction(action);
		if (color == defaultColor)
		{
			colorMenu->setDefaultAction(action);
		}
	}
	return colorMenu;
}

QWidget* CResource::createCellWidget(QButtonGroup* buttonGroup,const QString &text,const QString &image)
{
	QToolButton *button = new QToolButton;
	button->setText(text);
	button->setIcon(QIcon(image));
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	buttonGroup->addButton(button);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}

QWidget* CResource::createCellWidget(QButtonGroup* buttonGroup,const QString &text,const QPixmap& image,int type)
{
	QIcon icon(image);

	QToolButton *button = new QToolButton;
	button->setIcon(icon);
	button->setIconSize(QSize(50, 50));
	button->setCheckable(true);
	buttonGroup->addButton(button, type);

	QGridLayout *layout = new QGridLayout;
	layout->addWidget(button, 0, 0, Qt::AlignHCenter);
	layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	return widget;
}
