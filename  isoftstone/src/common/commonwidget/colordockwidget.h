
#ifndef COLORSWATCH_H
#define COLORSWATCH_H

#include <QtGui>

#include "customdef.h"

class  EXPORT_WIDGET ColorTitleBar : public QWidget
{
	Q_OBJECT
public:
	ColorTitleBar(QWidget *parent = 0);

	QSize sizeHint() const { return minimumSizeHint(); }
	QSize minimumSizeHint() const;
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void contextMenuEvent(QContextMenuEvent *event);
	public slots:
		void updateMask();

private:
	QPixmap leftPm, centerPm, rightPm;
};

class CColorDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    CColorDockWidget(QWidget *parent = 0);

   
    void setCustomSizeHint(const QSize &size);
	void setWidget(QWidget *widget); 

protected:
    virtual void contextMenuEvent(QContextMenuEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent *e);

private:
    void allow(Qt::DockWidgetArea area, bool allow);
    void place(Qt::DockWidgetArea area, bool place);
	void setupTitleBarMenu();
	void exchangeWindow();

private slots:
	void changeSizeHints();
    void changeClosable(bool on);
    void changeMovable(bool on);
    void changeFloatable(bool on);
    void changeFloating(bool on);
    void changeVerticalTitleBar(bool on);
    void updateContextMenu();

    void allowLeft(bool a);
    void allowRight(bool a);
    void allowTop(bool a);
    void allowBottom(bool a);

    void placeLeft(bool p);
    void placeRight(bool p);
    void placeTop(bool p);
    void placeBottom(bool p);

    void splitInto(QAction *action);
    void tabInto(QAction *action);

private:
	QAction *closableAction;
	QAction *movableAction;
	QAction *floatableAction;
	QAction *floatingAction;
	QAction *verticalTitleBarAction;

	QActionGroup *allowedAreasActions;
	QAction *allowLeftAction;
	QAction *allowRightAction;
	QAction *allowTopAction;
	QAction *allowBottomAction;

	QActionGroup *areaActions;
	QAction *leftAction;
	QAction *rightAction;
	QAction *topAction;
	QAction *bottomAction;

	QAction *changeSizeHintsAction;

	QMenu *tabMenu;
	QMenu *splitHMenu;
	QMenu *splitVMenu;
	QMenu *m_dockMenu;

	QAction *windowModifiedAction;

	friend class ColorTitleBar;
};



#endif
