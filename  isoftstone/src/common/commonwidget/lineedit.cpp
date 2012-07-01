
#include "lineedit.h"

CLineEdit::CLineEdit(QWidget *parent) :QLineEdit(parent)
{
}

void CLineEdit::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
    {
        emit enterPressed();
    }
    QLineEdit::keyPressEvent(e);
}
