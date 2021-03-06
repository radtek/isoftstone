
#include "gifitem.h"

CGifItem::CGifItem(QGraphicsItem *parent):QGraphicsObject(parent)
{
}

CGifItem::~CGifItem(void)
{
	//�ص���ʱ��
	if (m_nTimerID > 0)
	{
		killTimer(m_nTimerID);
	}
}

void CGifItem::init(const QString& fileName,const QSize& size,bool bClip )
{
	m_oImageList.clear();
	m_nCurrFrame = 0;
	m_nTimerID = 0;
	m_fileName = fileName;
	QSize tmp(0,0);
	m_fileSize = tmp;
	m_bClip = bClip;

	if (size.isValid())
	{
		m_fileSize = size;
	}

	setFlags(ItemIsSelectable | ItemIsFocusable);
	LoadPixmap();

}

void CGifItem::LoadPixmap()
{
	//�������ͼ����
	QImageReader oImageReader(m_fileName);
	if(oImageReader.canRead())
	{
		int nCount = oImageReader.imageCount();
		if (m_fileSize.isNull())
		{
			m_fileSize = oImageReader.size();
		}
		
		for (int nIndex = 0; nIndex < nCount; nIndex++)
		{
			oImageReader.setScaledSize(m_fileSize);
			QImage oImage = oImageReader.read();
			m_oImageList.append(oImage);
		}

		if(nCount > 1)
		{
			m_nTimerID = startTimer(200);
		}
	}
}

QRectF CGifItem::boundingRect() const
{
	return QRectF(0, 0, m_fileSize.width(),m_fileSize.height());
}

void CGifItem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (m_nCurrFrame >= m_oImageList.size())
	{
		return;
	}

	//����
	painter->drawImage(boundingRect(), m_oImageList[m_nCurrFrame]);

}

void CGifItem::timerEvent(QTimerEvent *event)
{
	if (m_nTimerID == event->timerId())
	{
		m_nCurrFrame++;
		if (m_nCurrFrame >= m_oImageList.count())
		{
			m_nCurrFrame = 0;
		}
	}
	update();
}
