#include "modelwindow.h"
#include "modelctrl.h"
#include "modeldata.h"
#include "nodefind.h"
#include "modelcomm.h"
#include "ui_modelwindow.h"
#include <QTextCodec>
#include <QActionGroup>
#include <QList>
#include <QMenuBar>
#include <QDebug>
CModelWindow::CModelWindow(QWidget *parent) :
    QMainWindow(parent),ui(new Ui::CModelWindow)
{
    setWindowFlags(Qt::Window);
    setWindowModality(Qt::WindowModal);
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    setWindowTitle(tr("模型编辑器"));
    setGeometry(QRect(350,200,750,500));

    m_modelCtrl1 = new CModelCtrl(this);
    m_commAction = new CModelComm(this,m_modelCtrl1);
    m_commAction->setUpAction(this);
    setCentralWidget(m_modelCtrl1);
    initWindow();
}
CModelWindow::~CModelWindow()
{
    delete m_modelCtrl1;
    delete m_commAction;
    delete ui;
}
void CModelWindow::initWindow()
{
	if(!m_commAction)
		return;
	qDebug()<<m_commAction;
    QActionGroup* actionGroup = m_commAction->getFileActions();
    if(actionGroup)
    {
        QList<QAction*> list = actionGroup->actions();
        m_FileMenu = menuBar()->addMenu(tr("文件"));
        foreach(QAction *action,list)
        {
            m_FileMenu->addAction(action);
        }
    }
}

