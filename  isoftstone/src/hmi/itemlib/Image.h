#ifndef CLASS_IMAGE_H
#define CLASS_IMAGE_H

#include "interface.h"
#include "itemlib.h"
#include "Image_Auto.h"
#include "CreateItem.h"

/*  图元由基础图形，自动序列化属性（包含模型属性），动态数据接口组成*/
class EXPORT_ITEMLIB CImage :public QGraphicsObject,public CImage_Auto, public CStaticItemBase
{
public:

	CImage(QGraphicsItem* parent = NULL);

	CImage(const Image_Struct& attrInfo,QGraphicsItem* parent = NULL);

	~CImage(void);

	virtual int	 type() const;

	virtual void init();

	virtual void draw();

	virtual QGraphicsItem* clone();

public:
	//重载
	virtual QRectF	boundingRect() const;
	virtual void	paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
	virtual void	timerEvent(QTimerEvent *event);

protected:
	void init(const QString& fileName,const QSize& size,bool bClip );
	void LoadPixmap();	//加载图片

private:

	QList<QImage>	m_oImageList;
	int				m_nCurrFrame;	//当前的图片帧索引
	int				m_nTimerID;
	QString			m_fileName;
	QSize			m_fileSize;
	bool			m_bClip;
};

#endif
