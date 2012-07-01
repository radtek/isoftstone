/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: ctablewidget.h
** 摘要: 继承QTableWidget,用于更改Cursor
**       
**
** 当前版本: 1.0.0.0
** 作者:  杜寅辰
** 完成日期: 2011.11.4
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 杜寅辰      2011.11.4   V1.0      创建
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