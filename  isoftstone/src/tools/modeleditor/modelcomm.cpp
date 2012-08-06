#include "modelcomm.h"
#include "modelwindow.h"
#include "modelctrl.h"
#include <QTextCodec>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
CModelComm::CModelComm(CModelWindow* parent,CModelCtrl* modelCtrl)
      : m_parent(parent),
        m_modelCtrl1(modelCtrl)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    //default init
    m_OpenAction = 0;
    m_SaveAction = 0;
    m_CloseAction = 0;
    m_FileActionGroup = 0;
    m_MouseActionGroup = 0;
}
CModelComm::~CModelComm()
{

}
//Functions----------------------------------------
//setUp Actions
void CModelComm::setUpAction(QWidget *parent)
{
    m_OpenAction = new QAction(this);
    m_OpenAction->setText(tr("打开"));
    m_OpenAction->setShortcut(tr("Ctrl+O"));
    //OpenAction->setIcon();
    connect(m_OpenAction,SIGNAL(triggered()),this,SLOT(slots_OpenFiles()));

    m_SaveAction = new QAction(this);
    m_SaveAction->setText(tr("保存"));
    m_SaveAction->setShortcut(tr("Ctrl+S"));
    //SaveAction->setIcon();
    connect(m_SaveAction,SIGNAL(triggered()),this,SLOT(slots_SaveFiles()));

    m_CloseAction =new QAction(this);
    m_CloseAction->setText(tr("关闭文件"));
    //CloseAction->setIcon();
    m_CloseAction->setShortcut(tr("Ctrl+W"));
    connect(m_CloseAction,SIGNAL(triggered()),this,SLOT(slots_CloseFiles()));
    setActionGroup(parent);
}

//setup action group
void CModelComm::setActionGroup(QWidget *parent)
{
    //file action group
    m_FileActionGroup = new QActionGroup(parent);
    m_FileActionGroup->addAction(m_OpenAction);
    m_FileActionGroup->addAction(m_SaveAction);
    m_FileActionGroup->addAction(m_CloseAction);
    //mouse action group
    m_MouseActionGroup = new QActionGroup(parent);
}
//get files actions
QActionGroup* CModelComm::getFileActions()
{
    return m_FileActionGroup;
}
//get mouse actions
QActionGroup* CModelComm::getMouseActions()
{
    return m_MouseActionGroup;
}

//public slots------------------------------------
//open files
void CModelComm::slots_OpenFiles()
{
	if(!m_parent)
		return;
    //创建打开文件对话框
    QString fileName = QFileDialog::getOpenFileName(m_parent, tr("打开"),
                                                     "/",
                                                     tr("文件类型 (*.XML)"));
	if (fileName.isNull())
	{
		return;
	}
    m_modelCtrl1->ParseXml(fileName);
}

//slot save files
void CModelComm::slots_SaveFiles()
{
	if(!m_parent)
		return;
	QString saveName = QFileDialog::getSaveFileName(m_parent,tr("SAVE"),"/",tr("FileType(*.XML)")) ;
}

//slot close files

void CModelComm::slots_CloseFiles()
{

}
