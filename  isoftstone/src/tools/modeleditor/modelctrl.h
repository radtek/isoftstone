/**********************************************
 *���������Ʋ�
 *���ã�1�������������������в�����2������XML����DB��
 *3�����������ϲ���Ҫ�Ľӿ�
 *Ȩ�ޣ���������Ȩ��
 *���ڣ�2012-7-22
 *********************************************/
#ifndef MODELCTRL_H
#define MODELCTRL_H
#include <QTreeWidget>
#include "modelwindow.h"
#include <QTableWidget>
#include <QTreeView>
#include <QDomElement>
#include <QDomDocument>
#include <QHash>

class DomModel;

namespace Ui {
    class CModelCtrl;
}
class CModelCtrl : public QSplitter
{
	Q_OBJECT
public:
     explicit CModelCtrl(QWidget* parent);
    ~CModelCtrl();
    void mkTree();
	void ParseXml(const QString fileName);
private:
	DomModel *model;
	QMenu *fileMenu;
	QString xmlPath;
	QTreeView *m_pviewR;
	QTreeView *m_pviewL;

};

#endif // DBTREE_H
