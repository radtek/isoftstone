/**********************************************
 *���������ò�
 *���ã�1������ACTIONS��2�������ȡACTION�ӿ�
 *3������ӿں��������� ModelCtrl ��ӿڣ�
 *���ڣ�2012-7-22
 *********************************************/
#ifndef  MODELCOMM_H
#define  MODELCOMM_H
#include <QTreeWidget>
#include <QAction>
#include <QActionGroup>
class CModelWindow;
class CModelCtrl;
class CModelComm : public QWidget
{
	Q_OBJECT
public:
     explicit CModelComm(CModelWindow*,CModelCtrl*);
    ~CModelComm();
    //void mkTree();
    void setUpAction(QWidget*);
    void setActionGroup(QWidget*);
    QActionGroup* getFileActions();
    QActionGroup* getMouseActions();
public slots:
    void slots_OpenFiles();
    void slots_SaveFiles();
    void slots_CloseFiles();
private:
    QWidget* m_parent; //transfer modelwindow's parent
    CModelCtrl* m_modelCtrl1;

    //ACTIONS
    QAction* m_OpenAction;
    QAction* m_SaveAction;
    QAction* m_CloseAction;
    QActionGroup* m_FileActionGroup;  //File Menu Action Group
    QActionGroup* m_MouseActionGroup; //Mouse right clicked action group

};

#endif // MODELTREE_H
