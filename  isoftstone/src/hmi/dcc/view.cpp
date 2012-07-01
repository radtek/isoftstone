
#include <QFileInfo>

#include "view.h"
#include "ItemFactory.h"


CView::CView(QWidget *parent): QGraphicsView(parent)
{
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	setViewportUpdateMode(BoundingRectViewportUpdate);
	setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform | QPainter::TextAntialiasing);
	setAcceptDrops(true);

	m_itemBar = NULL;

}

void CView::openFile(const QString& fileName)
{
	QFileInfo info(fileName);
	QString ext = info.suffix();
	if (ext == "g")
	{
		dynamic_cast<CGraphicsScene*>(scene())->draw(fileName);
		fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
		adjustScene();
	}
	else if (ext == "qml")
	{
		m_itemBar = NULL;
		dynamic_cast<CGraphicsScene*>(scene())->drawQML(fileName);
		//fitInView(scene()->sceneRect(), Qt::KeepAspectRatio);
	}
}

QString CView::currentFile()
{
	return dynamic_cast<CGraphicsScene*>(scene())->currentFile();
}

void CView::setViewBackground(bool enable)
{

}

void CView::setViewOutline(bool enable)
{
	
}

void CView::setToolbar(CItemToolBar* pBar)
{
	if (m_itemBar)
	{
		m_itemBar = NULL;
	}

	m_itemBar = pBar;
}

void CView::wheelEvent(QWheelEvent *event)
{
	qreal factor = qPow(1.2, event->delta() / 240.0);
	scale(factor, factor);
	event->accept();
	adjustScene();
}

void CView::resizeEvent( QResizeEvent *event)
{
	fitInView(sceneRect(), Qt::KeepAspectRatio);

	adjustScene();
	QGraphicsView::resizeEvent(event);
}

void CView::adjustScene()
{
	if (m_itemBar)
	{
		m_itemBar->fitItemBar();

		CGraphicsScene* pScene = dynamic_cast<CGraphicsScene*>(this->scene());
		pScene->setScaleFactor(transform().m11(),transform().m22());
		pScene->hideContextMenu();
	}
}

void CView::mouseMoveEvent(QMouseEvent *event)
{	
	QPointF pos = mapToScene(event->pos());
	if ((event->buttons() == Qt::LeftButton))
	{
		setCursor(Qt::ClosedHandCursor);
		if ((pos - m_lastPos).manhattanLength() > QApplication::startDragDistance())
		{
			translate(pos.x() - m_lastPos.x(),pos.y() - m_lastPos.y());
		}
	}

	QGraphicsView::mouseMoveEvent(event);
}

void CView::mouseReleaseEvent(QMouseEvent *event)
{
	setCursor(Qt::ArrowCursor);
	QGraphicsView::mouseReleaseEvent(event);
}

void CView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_lastPos = mapToScene(event->pos());
	}
	QGraphicsView::mousePressEvent(event);
}

void CView::dragEnterEvent(QDragEnterEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	if (mimeData->hasUrls())
		event->acceptProposedAction();
}

void CView::dragMoveEvent(QDragMoveEvent *event)
{
	event->acceptProposedAction();
}

void CView::dragLeaveEvent(QDragLeaveEvent *event)
{
	event->accept();
}

void CView::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();
	if (!mimeData->hasUrls())
		return;
	const QList<QUrl> urlList = mimeData->urls();
	foreach (const QUrl &url, urlList) 
	{
		if (url.scheme() == QLatin1String("file"))
		{
			openFile(url.toLocalFile());
			event->accept();
			return;
		}
	}
}

bool CView::event(QEvent *event)
{
	if (event->type() == QEvent::ToolTip) 
	{
		QHelpEvent *helpEvent = static_cast<QHelpEvent *>(event);
		QGraphicsItem* pItem = itemAt(helpEvent->pos());
		if (pItem != NULL) 
		{
			QString strToolTip ;//= m_PluginLoader->getToolTip(pItem,m_appID);
			if (!strToolTip.isEmpty())
			{
				QToolTip::showText(helpEvent->globalPos(), strToolTip);	
			}
		}
		else 
		{
			QToolTip::hideText();
			event->ignore();
		}	
	}
	return QGraphicsView::event(event);
}
