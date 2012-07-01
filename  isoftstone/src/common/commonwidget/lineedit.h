#ifndef VLINEEDIT_H
#define VLINEEDIT_H

#include <QLineEdit>
#include <QKeyEvent>

#include "customdef.h"

class EXPORT_WIDGET CLineEdit : public QLineEdit
{
Q_OBJECT
public:
    explicit CLineEdit(QWidget *parent = 0);

signals:

public slots:

protected:
    void keyPressEvent(QKeyEvent *);

Q_SIGNALS:
    void enterPressed();

};

#endif
