#include <QtGui>
#include "nodefind.h"

CNodeFind::CNodeFind(CModelWindow* parent,CModelCtrl* modelCtrl):
    m_ModelWindow(parent),m_ModelCtrl(modelCtrl)
{
    setupUi(this);
    setWindowTitle(tr("≤È’“"));

}

