#ifndef NODEFIND_H
#define NODEFIND_H
#include <QDialog>
#include "ui_FindDialog.h"
class CModelWindow;
class CModelCtrl;
class CNodeFind : public QDialog,public Ui::UFindDialog
{
	Q_OBJECT
public:
    explicit CNodeFind(CModelWindow*,CModelCtrl*);
private:
    CModelWindow* m_ModelWindow;
    CModelCtrl* m_ModelCtrl;
};

#endif // NODEFIND_H
