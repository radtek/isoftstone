/*****************************************************
 *�������������
 *���ã�1����ʼ�����棬�����˵�����״̬�������ACTIONS
 *2�����з�����setSavePath������openFile����--�����²�ӿ�
 *���ڣ�2012-7-22
 *Ȩ�ޣ���������Ȩ��
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
