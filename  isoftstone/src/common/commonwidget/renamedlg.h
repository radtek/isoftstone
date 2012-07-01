
#ifndef RENAMEDLG_H
#define RENAMEDLG_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>

#include "lineedit.h"

class EXPORT_WIDGET RenameDlg : public QWidget
{
Q_OBJECT
public:
    explicit RenameDlg(QWidget *parent = 0);

signals:

public slots:
    void SetText(const QString& str);

private:
    CLineEdit* lineEdit;
    QVBoxLayout* mainLayout;

private slots:
    void Fire_SetText();
Q_SIGNALS:
    void sig_SetText(const QString& str);

};

#endif // RENAMEDLG_H
