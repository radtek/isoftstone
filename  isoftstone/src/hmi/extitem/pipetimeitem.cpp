
#include <QtGui>

#include "pipetimeitem.h"

CPipeTimeItem::CPipeTimeItem(QGraphicsItem* parent):QGraphicsObject(parent)
													,m_Rect(0,0,100,100)
{
	m_timecolor			= Qt::cyan;
	m_timepipefont		= QFont(QString::fromLocal8Bit("宋体"), 19);
	m_timerID = startTimer(1000);
}


QRectF CPipeTimeItem::boundingRect() const
{
	return m_Rect;
}

void CPipeTimeItem::setTimeColor(QColor color)			
{
	m_timecolor = color;		
}

QColor CPipeTimeItem::getTimeColor()	
{
	return m_timecolor;	
}

void CPipeTimeItem::paint( QPainter * painter, const QStyleOptionGraphicsItem * , QWidget *   )
{
	QRect rect = m_Rect.toRect();
	QTime curtime = QTime::currentTime();
	//晶体管时间
	QRect  timerect;
	timerect.setLeft(rect.left());
	timerect.setTop(rect.top());
	timerect.setRight(rect.right());
	timerect.setBottom(rect.bottom());

	char strText[128];
	sprintf (strText, "%02d:%02d:%02d", curtime.hour(), curtime.minute(), curtime.second());  

	drawPipeText(painter, timerect, strText);
}

void CPipeTimeItem::drawPipeText(QPainter *painter, QRect &rect, char *cText)
{
	//从右往左画----------------------------------------------------------------------------------//ngrn changed
	int xRight	= rect.right();
	int yTop	= rect.top();

	QFontMetrics fm(m_timepipefont);			//字体矩阵
	int pixelsHigh = fm.height();				//字符串像素高度
	
	int wCharW  = fm.width("0");				//单字符像素宽度
	int wCharH	= fm.height();					//单字符像素高度
	
	xRight	= rect.right();									//绘制数码管开始的横坐标	//ngrn changed
	yTop	= rect.top() + (rect.height() - pixelsHigh)/2;	//绘制数码管开始的纵坐标


	if (wCharW < 6 || wCharH < 6) return;		//字体太小返回
	
	int wCharWidth = wCharW;
	int wCharHeight = wCharH;
    QColor crFore = getTimeColor();			//颜色
	int wStrLen = strlen(cText);			//字符串长度, ngrn changed

	//======================//
	//字符ASCII码
    // decimal  character set:
    // 43        +
    // 45        -
    // 46        .
    // 48... 57  0... 9
    //======================//
	
	QColor crFont = crFore;

	int wNumPoint = 0;
	
	int x_idx = 0;
	
	for(int i = 0; i <= wStrLen; i++)
    {
		int wNumber = cText[wStrLen - i];	//取得字符串中的一个字符
		if(wNumber > 58 ) continue;			//判断ASCII码是否大于 “:”
		if(wNumber < 48 && wNumber != 45 && wNumber != 46) continue;	//判断ASCII码是否小于“0” ，“-”，“.”
		
		wNumber -= 48;						//所以字符都减去48
		
		if(wNumber == -2 || wNumber == 10)	//若字符为“.” 或者字符为“:”
			wNumPoint = 1;					
		else if(wNumPoint == 1)
			wNumPoint = -1;
		
		if(wNumPoint == 1)
		{
			x_idx = (int)(x_idx + wCharWidth * 2.0 / 5);
		}
		else {
			x_idx += wCharWidth;
		}

		QRect piperect(xRight - x_idx, yTop, wCharWidth, wCharHeight);		//单个字符矩形
		
		drawPipeNum(painter, piperect, wNumber);

	}
	//从右往左画----------------------------------------------------------------------------------//ngrn changed
}

void CPipeTimeItem::drawPipeNum(QPainter *painter, QRect &rect, int wNumber)
{
	/* pipe discription:

		  A
		 ---
	  F |   | B
		 ---  <----G
	  E |   | C
		 ---
		  D
	*/
	
	int wCellWidth = (int)((rect.right() - rect.left())*1.0/2);
    int wCellSpace = wCellWidth/4==0?1:(int)(wCellWidth/4.0);

	int wBevelWidth = (wCellWidth/4==0?1:wCellWidth/4);
    int wCellHeight = (int)((rect.bottom() - rect.top() - wCellSpace * 3.0)/2.0);

	//////////////////////////
	//	if(wCellWidth/4<2)
	wBevelWidth = (int)(wCellWidth/4*1.5) * 2;		//ngrn changed
	/////////////////////////////
	
	int sx0 = rect.left() + wCellSpace * 2;	
	int sy0 = rect.top() + wCellSpace;
	
	
	if(wNumber == 1 )
		sx0 = sx0 + wCellWidth;
	
	int sx1 = sx0 + wCellWidth + wCellSpace;
	int sy1 = sy0;
    int sx2 = sx1;
	int sy2 = sy1 + wCellHeight + wCellSpace;
    int sx3 = sx2 - wCellSpace;
	int sy3 = sy2 + wCellHeight;
    int sx4 = sx3 - wCellWidth-wCellSpace;
	int sy4 = sy3;
    int sx5 = sx4;
	int sy5 = sy4 - wCellHeight - wCellSpace;
    int sx6 = sx4 + wCellSpace;
	int sy6 = sy4 - wCellHeight - wCellSpace/2;


	QBrush		oldbrush = painter->brush();
	QPen		oldpen   = painter->pen();

	QPen		pOldPen(Qt::NoPen);
    QBrush		pNewBrush(getTimeColor());

	painter->setPen(Qt::NoPen);
	painter->setBrush(pNewBrush);

	//decimal point
    if(wNumber == -2)
		painter->drawRect(QRect(QPoint(sx4, sy4 - wCellSpace*2), QPoint(sx4 + wCellSpace*2, sy4)));//防止字太小时画不出
	
	if(wNumber == 10) {
		painter->drawRect(QRect(QPoint(sx4, sy2 - wCellSpace*2), QPoint(sx4 + wCellSpace*2, sy2)));//防止字太小时画不出
		painter->drawRect(QRect(QPoint(sx4, sy4 - wCellSpace*2), QPoint(sx4 + wCellSpace*2, sy4)));//防止字太小时画不出
		painter->setPen(oldpen);
		painter->setBrush(oldbrush);
		return;
	}
	
	
	QPolygon polygon(5);
	
    //A
    if(wNumber >= 0 && wNumber != 1 && wNumber != 4) 
	{
		polygon.setPoint(0, sx0, sy0);
		polygon.setPoint(1, sx0 + wCellWidth, sy0);
		polygon.setPoint(2, polygon[1].x() - wBevelWidth, sy0 + wBevelWidth);
		polygon.setPoint(3, sx0 + wBevelWidth, sy0 + wBevelWidth);
		polygon.setPoint(4, polygon[0].x(), polygon[0].y());
		painter->drawPolygon(polygon);
    }
	
	//B
	polygon.resize(4);
    if(wNumber >= 0 && wNumber != 1 && wNumber != 5 && wNumber != 6)  
	{
		polygon.setPoint(0, sx1, sy1);
		polygon.setPoint(1, sx1, sy1 + wCellHeight);
		polygon.setPoint(2, polygon[1].x() - wBevelWidth, polygon[1].y() - wBevelWidth); 
		polygon.setPoint(3, sx1 - wBevelWidth, sy1 + wBevelWidth);
		painter->drawPolygon(polygon);
    }
	
    //C
    if(wNumber >= 0 && wNumber != 1 && wNumber != 2)   
	{
		polygon.setPoint(0, sx2, sy2); 
		polygon.setPoint(1, sx2, sy2 + wCellHeight);
		polygon.setPoint(2, polygon[1].x() - wBevelWidth, polygon[1].y() - wBevelWidth); 
		polygon.setPoint(3, sx2 - wBevelWidth, sy2 + wBevelWidth); 
		painter->drawPolygon(polygon);
    }
	
    //D
    if(wNumber >= 0 && wNumber != 1 && wNumber != 4 && wNumber != 7)  
	{
		polygon.setPoint(0, sx3, sy3);
		polygon.setPoint(1, sx3 - wCellWidth, sy3); 
		polygon.setPoint(2, polygon[1].x() + wBevelWidth, polygon[1].y() - wBevelWidth);
		polygon.setPoint(3, sx3 - wBevelWidth, sy3 - wBevelWidth); 
		painter->drawPolygon(polygon);
    }
	
    //E
    if( wNumber >= 0 && wNumber < 3 ||  wNumber > 5 && wNumber != 7 && wNumber != 9) 
	{
		polygon.setPoint(0, sx4, sy4); 
		polygon.setPoint(1, sx4, sy4 - wCellHeight); 
		polygon.setPoint(2, polygon[1].x() + wBevelWidth, polygon[1].y() + wBevelWidth);  
		polygon.setPoint(3, sx4 + wBevelWidth, sy4 - wBevelWidth);  
		painter->drawPolygon(polygon);
    }
	//F
    if(wNumber >= 0 && wNumber != 2 && wNumber != 3 && wNumber != 7)  
	{
		polygon.setPoint(0, sx5, sy5); 
		polygon.setPoint(1, sx5, sy5 - wCellHeight); 
		polygon.setPoint(2, polygon[1].x() + wBevelWidth, polygon[1].y() + wBevelWidth); 
		polygon.setPoint(3, sx5 + wBevelWidth, sy5 - wBevelWidth); 
		painter->drawPolygon(polygon);
    }
	
    //G ; negtive char
	polygon.resize(6);
    if(wNumber == -3 || wNumber > 1  &&  wNumber != 7)  
	{
		if(wBevelWidth<2)wBevelWidth=2;//防止字太小时画不出

		polygon.setPoint(0, sx6, sy6); 
		polygon.setPoint(1, sx6 + wBevelWidth/2, sy6 - wBevelWidth/2); 
		polygon.setPoint(2, sx6 + wCellWidth - wBevelWidth/2, polygon[1].y()); 
		polygon.setPoint(3, sx6 + wCellWidth, sy6);  
		polygon.setPoint(4, polygon[3].x() - wBevelWidth/2, polygon[3].y() + wBevelWidth/2);  
		polygon.setPoint(5, sx6 + wBevelWidth/2, sy6 + wBevelWidth/2);  
		painter->drawPolygon(polygon);
    }

	painter->setPen(oldpen);
	painter->setBrush(oldbrush);
}

void CPipeTimeItem::timerEvent(QTimerEvent * event)
{
	if (event->timerId() == m_timerID)
	{
		update();
	}
}