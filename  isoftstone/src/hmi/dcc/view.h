
#ifndef CView_H
#define CView_H

#include <QtGui>

#include "scene.h"
#include "contextmenu.h"
#include "toolbaritem.h"

class CView : public QGraphicsView
{
	Q_OBJECT

public:

	CView(QWidget *parent = 0);

	void	openFile(const QString& fileName);
	QString currentFile();

	void setToolbar(CItemToolBar* pBar);
	void adjustScene();

public slots:
	void setViewBackground(bool enable);
	void setViewOutline(bool enable);

protected:
	void wheelEvent(QWheelEvent *event);
	void resizeEvent( QResizeEvent* event );
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
	bool event(QEvent *event);

	void dragEnterEvent(QDragEnterEvent *event);
	void dragMoveEvent(QDragMoveEvent *event);
	void dragLeaveEvent(QDragLeaveEvent *event);
	void dropEvent(QDropEvent *event);

private:

	QPointF					m_lastPos;
	CItemToolBar*			m_itemBar;
};
#endif // CView_H
