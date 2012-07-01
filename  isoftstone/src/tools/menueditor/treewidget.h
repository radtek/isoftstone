
#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QTreeWidget>

class CTreeWidget: public QTreeWidget
{
	Q_OBJECT

public:
	enum Mode { eInsert, eRemove};
	CTreeWidget(void);
	~CTreeWidget(void);

protected:
	virtual void keyPressEvent(QKeyEvent *event);
	virtual bool dropMimeData(QTreeWidgetItem* parent, int index, const QMimeData* data, Qt::DropAction action);
	QStringList mimeTypes() const;    
	Qt::DropActions supportedDropActions () const;
	void moveCommand(QString strApp, QString strItem, int iPos, Mode eType);
	int getMaxPos(QString strApp, QString strItem);
	QString getStrByPos(QString strApp, QString strItem, int iPos);

public slots:
	void initMenuList();

};

#endif