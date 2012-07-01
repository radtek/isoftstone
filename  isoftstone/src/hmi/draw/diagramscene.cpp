

#include <QtGui>

#include "diagramscene.h"
#include "arrow.h"

#include "itemfactory.h"

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : CGraphicsSceneBase(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = DiagramItem::Step;
}

void DiagramScene::setLineColor(const QColor &color)
{
	m_LineColor = color;
    foreach(QGraphicsItem* item,selectedItems())
	{
		Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
		if (arrow)
		{
			arrow->setColor(color);
			update();
		}
    }
}

void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(DiagramItem::DiagramType type)
{
    myItemType = type;
}

void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
	bool bRet = item->getFocus();
	if (!bRet)
	{
		removeItem(item);
	}
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton) return;

    DiagramItem *item;
    switch (myMode) 
	{
        case InsertItem:
            item = new DiagramItem(myItemType, myItemMenu);
            item->setBrush(m_FillColor);
            addItem(item);
            item->setPos(mouseEvent->scenePos());
            emit itemInserted(item);
            break;
        case InsertLine:
			{
				m_LinkLine = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),mouseEvent->scenePos()));
				m_LinkLine->setPen(QPen(m_LineColor, 2));
				addItem(m_LinkLine);
			}
			break;
        case InsertText:
			{
				DiagramTextItem* textItem = new DiagramTextItem();
				textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
				textItem->setZValue(1000.0);
				connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
						this, SLOT(editorLostFocus(DiagramTextItem*)));
				connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
						this, SIGNAL(itemSelected(QGraphicsItem*)));
				addItem(textItem);
				textItem->setDefaultTextColor(m_FontColor);
				textItem->setPos(mouseEvent->scenePos());
				emit textInserted(textItem);
			}
			break;
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && m_LinkLine != 0)
	{
        QLineF newLine(m_LinkLine->line().p1(), mouseEvent->scenePos());
        m_LinkLine->setLine(newLine);
    } 
	else if (myMode == MoveItem) 
	{
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_LinkLine != 0 && myMode == InsertLine) 
	{
		Arrow::drawArraw(this,&m_LinkLine,m_LineColor);	
    }
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) 
	{
        if (item->type() == type)
            return true;
    }
    return false;
}

void DiagramScene::saveFile(QString fileName)
{
	QFile file( fileName );
	file.open(QIODevice::WriteOnly | QIODevice::Truncate);
	QDataStream out(&file); 

	// 对场景相关配置保存
	QBrush bkBrush = backgroundBrush();
	out << bkBrush;

	QList<QGraphicsItem *> lstItems = items();
	foreach(QGraphicsItem* item ,lstItems)
	{
		int ntype = item->type();
		out << ntype;

		ISerialize* serial = dynamic_cast<ISerialize*>(item);
		out << serial;

	}
	file.close();
}

void DiagramScene::saveImage(QString fileName)
{
	QImage sImage;
	QGraphicsView* m_View;
	QList<QGraphicsView *> lstViews = this->views();
	if (lstViews.count() > 0)
	{
		m_View = lstViews.first();
		QPixmap pixmap = QPixmap::grabWidget(m_View,sceneRect().toRect());
		sImage = pixmap.toImage();
		sImage.save(fileName,"png");
	}
	
}

void DiagramScene::openGFile(QString fileName)
{
	CItemFactory::instance()->draw(this,fileName);
}

void DiagramScene::openFile(QString fileName)
{
	QFile file( fileName );
	file.open(QIODevice::ReadOnly);
	QDataStream out(&file); 

	setBackgroundBrush(QPixmap(":/images/background4.png"));
	clear();

	if (!out.atEnd())
	{
		QBrush bkBrush;
		out >> bkBrush;
		setBackgroundBrush(bkBrush);
	}

	QList<Arrow*> lstArrows;

	while (!out.atEnd())
	{
		int ntype;
		out >> ntype;

		if (ntype == DiagramItem::Type)
		{
			DiagramItem* diag = new DiagramItem(myItemMenu);
			out >> diag;
			addItem(diag);
		}
		else if (ntype == DiagramTextItem::Type)
		{
			DiagramTextItem* diag = new DiagramTextItem(NULL,this);
			out >> diag;
			addItem(diag);
		}
		else if (ntype == Arrow::Type)
		{
			// 暂时不设置开始图元与结束图元，在后面进行绑定。
			Arrow* diag = new Arrow(NULL,NULL,NULL,NULL);
			out >> diag;
			diag->setScene(this);
			lstArrows.append(diag);
		}
	}

	foreach(Arrow* ar,lstArrows)
	{
		ar->build();
		addItem(ar);
		ar->updatePosition();
	}
}