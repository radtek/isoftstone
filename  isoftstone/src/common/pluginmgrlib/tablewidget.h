/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: ctablewidget.h
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

#ifndef CTABLEWIDGET_H
#define CTABLEWIDGET_H

#include <QTableWidget>

class CTableWidget : public QTableWidget
{
public:
	CTableWidget(QWidget* parent = 0);
	~CTableWidget(){};

protected:

	virtual void mouseMoveEvent(QMouseEvent *event);
};

#endif