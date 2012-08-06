/**********************************************
 *描述：控制层
 *作用：1、对左右两颗树的所有操作；2、解析XML生成DB树
 *3、定义所有上层需要的接口
 *权限：保留所有权限
 *日期：2012-7-22
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
