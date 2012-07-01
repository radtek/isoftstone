

#include "renamedlg.h"

RenameDlg::RenameDlg(QWidget *parent) :
    QWidget(parent)
{
    mainLayout=new QVBoxLayout;
    lineEdit=new CLineEdit(this);

    mainLayout->addWidget(lineEdit);

    setLayout(mainLayout);

    connect(lineEdit,SIGNAL(enterPressed()),this,SLOT(Fire_SetText()));

    setWindowFlags(Qt::Tool);
    setWindowModality(Qt::ApplicationModal);
    lineEdit->setFocus(Qt::PopupFocusReason);
//    setAttribute(Qt::WA_TranslucentBackground);
}

void RenameDlg::Fire_SetText()
{

    QString strText = lineEdit->text();
    emit sig_SetText(strText);
}


void RenameDlg::SetText(const QString &str)
{
    lineEdit->setText(str);
}
