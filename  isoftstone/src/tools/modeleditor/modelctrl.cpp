#include <QTextCodec>
#include <QSplitter>
#include <QFile>
#include <QMessageBox>
#include <QDomElement>
#include <QIODevice>
#include <QDomDocument>
#include <QTreeWidgetItem>
#include "modelctrl.h"
#include "dommodel.h"
CModelCtrl::CModelCtrl(QWidget* parent)
    : QSplitter(parent)
{
    QTextCodec::setCodecForTr(QTextCodec::codecForName("GBK"));
    mkTree();
}
CModelCtrl::~CModelCtrl()
{
	//delete model;
}
void CModelCtrl::mkTree()
{
    QSplitter *splitter = new QSplitter(Qt::Horizontal,this);
	QStringList headerLabel = (QStringList() << tr("����") << tr("����") << tr("ֵ")); 
	model = new DomModel(QDomDocument(), this);
    m_pviewR = new QTreeView(this);
	m_pviewR->setModel(model);
    splitter->addWidget(m_pviewR);
    m_pviewL = new QTreeView(this);
	m_pviewL->setModel(model);
    splitter->addWidget(m_pviewL);

}

//func parsexml
void CModelCtrl::ParseXml(const QString fileName)
{

	if (!fileName.isEmpty()) 
	{
		QFile file(fileName);
		if (file.open(QIODevice::ReadOnly)) 
		{
			QDomDocument document;
			if (document.setContent(&file)) 
			{
				DomModel *newModel = new DomModel(document, this);
				m_pviewR->setModel(newModel);
				m_pviewL->setModel(newModel);
				delete model;
				model = newModel;
				xmlPath = fileName;
			}
			file.close();
		}
	}
}


