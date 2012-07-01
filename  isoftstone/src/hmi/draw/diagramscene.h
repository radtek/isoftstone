

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include <QtGui>

#include "diagramitem.h"
#include "diagramtextitem.h"
#include "scenebase.h"


class DiagramScene : public CGraphicsSceneBase
{
    Q_OBJECT

public:
    enum Mode { InsertItem, InsertLine, InsertText, MoveItem };

    DiagramScene(QMenu *itemMenu, QObject *parent = 0);

    void setLineColor(const QColor &color);

	void saveFile(QString fileName);
	void openFile(QString fileName);
	void openGFile(QString fileName);
	void saveImage(QString fileName);

public slots:
    void setMode(Mode mode);
    void setItemType(DiagramItem::DiagramType type);
    void editorLostFocus(DiagramTextItem *item);

signals:
    void itemInserted(DiagramItem *item);
    void textInserted(QGraphicsTextItem *item);
    void itemSelected(QGraphicsItem *item);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

private:
    bool isItemChange(int type);

    DiagramItem::DiagramType myItemType;
	QGraphicsLineItem*		 m_LinkLine;
    QMenu*					 myItemMenu;
    Mode					 myMode;

};

#endif
