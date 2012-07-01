
#include "Image.h"
#include "config.h"


CImage::CImage(QGraphicsItem *parent):QGraphicsObject(parent)
{
}

CImage::CImage(const Image_Struct& attrInfo,QGraphicsItem* parent):QGraphicsObject(parent)
{
	m_Info = attrInfo;
}

CImage::~CImage(void)
{
	//关掉定时器
	if (m_nTimerID > 0)
	{
		killTimer(m_nTimerID);
	}
}

int	 CImage::type() const
{
	return CIMGImage;
}

void CImage::init()
{
	QString strFile =  getAttrValue("ahref");
	strFile = CConfig::instance()->getImagePath(strFile);
	
	init(strFile,QSize(m_Info.w,m_Info.h),false);
}

void CImage::draw()
{
	setPos(m_Info.x,m_Info.y);
}

QGraphicsItem* CImage::clone()
{
	CImage* pItem = new CImage(m_Info);
	return pItem;
}


void CImage::init(const QString& fileName,const QSize& size,bool bClip )
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

void CImage::LoadPixmap()
{
	//填充像素图对象
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

QRectF CImage::boundingRect() const
{
	return QRectF(0, 0, m_fileSize.width(),m_fileSize.height());
}

void CImage::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (m_nCurrFrame >= m_oImageList.size())
	{
		return;
	}

	//绘制
	painter->drawImage(boundingRect(), m_oImageList[m_nCurrFrame]);

}

void CImage::timerEvent(QTimerEvent *event)
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
