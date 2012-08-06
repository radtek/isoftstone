/*****************************************************
 *描述：主界面层
 *作用：1、初始化界面，创建菜单栏、状态栏并添加ACTIONS
 *2、公有方法：setSavePath（）、openFile（）--调用下层接口
 *日期：2012-7-22
 *权限：保留所有权限
 *****************************************************/
#ifndef MODELWINDOW_H
#define MODELWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <QSplitter>
#include <QTreeWidget>
#include <QTableWidget>
#include <QMenu>
class CModelComm;
class CModelCtrl;
namespace Ui {
    class CModelWindow;
}
class CModelWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CModelWindow(QWidget *parent = 0);
    ~CModelWindow();

private:
	//MENUS
	QMenu* m_FileMenu;
	QMenu* m_FileSubMenu;
	QMenu* m_FileSubMenuFiles;
	QMenu* m_EditMenu;

    CModelComm* m_commAction;
    CModelCtrl* m_modelCtrl1;
    Ui::CModelWindow *ui;
    //Funcs
    void initWindow();

};

#endif // MAINWINDOW_H
