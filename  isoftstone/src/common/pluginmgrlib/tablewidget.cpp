/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: ctablewidget.cpp
** ժҪ: �̳�QTableWidget,���ڸ���Cursor
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ������
** �������: 2011.11.4
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ������      2011.11.4   V1.0      ����
**
****************************************************************************/

#include "tablewidget.h"
#include <QPoint>
#include <QMouseEvent>

CTableWidget::CTableWidget(QWidget* parent) :
	QTableWidget(parent)
{
	setMouseTracking(true);
	
}

void CTableWidget::mouseMoveEvent(QMouseEvent* event)
{
	//QPoint pt = event->pos();

	//QTableWidgetItem* item = itemAt(pt.x(), pt.y());
	//if(item == NULL)
	//{
	//	setCursor(Qt::ArrowCursor);
	//}
	//else
	//{
	//	if(item->column() == 1)
	//	{
	//		setCursor(Qt::PointingHandCursor);
	//	}
	//	else
	//	{
	//		setCursor(Qt::ArrowCursor);
	//	}
	//}
	event->accept();
}