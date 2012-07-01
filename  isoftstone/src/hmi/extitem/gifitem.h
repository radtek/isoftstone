
#ifndef GIF_ITEM_H
#define GIF_ITEM_H

#include "extitem.h"

//����ͼͼԪ������
class EXPORT_EXTITEM CGifItem : public QGraphicsObject
{
public:
	CGifItem(QGraphicsItem *parent = 0);
	~CGifItem(void);

	void init(const QString& fileName,const QSize& size = QSize(-1,-1),bool bClip = false);
public:
	//����
	virtual QRectF boundingRect() const;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
	virtual void timerEvent(QTimerEvent *event);
	
protected:

	void LoadPixmap();	//����ͼƬ

private:

	QList<QImage>	m_oImageList;
	int				m_nCurrFrame;	//��ǰ��ͼƬ֡����
	int				m_nTimerID;
	QString			m_fileName;
	QSize			m_fileSize;
	bool			m_bClip;
	
};

#endif