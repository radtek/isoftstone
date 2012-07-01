#pragma once

#include <QTableView>
#include <QStandardItem>
#include <QKeyEvent>

#include "setting.h"

#define MAX_COMMAND 65535

class CCommandView : public QTableView
{
	Q_OBJECT

public:
	CCommandView();
	~CCommandView(void);

public slots:

	void onTableViewChanged(QStandardItem *pItem);

protected:
	virtual void dataChanged ( const QModelIndex & topLeft, const QModelIndex & bottomRight );
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);	//¿ì½Ý¼ü

private:
	//Ð£Ñé
	bool isValid(int nCommand);
	void resizeDate();

signals:
	void sigUpdate();
};
