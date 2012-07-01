
#ifndef FILETREE_H
#define FILETREE_H

#include <QTreeWidget>
#include <QResizeEvent>
#include <QListWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QContextMenuEvent>
#include <QMenu>

#include "util.h"
#include "renamedlg.h"
#include "customdef.h"

#define IT_H_CNT 8
#define IT_V_CNT 16

#define IT_LIGHT_COLOR Qt::white
#define IT_DARK_COLOR QColor(150,150,)

class EXPORT_WIDGET CFileTree : public QTreeWidget
{
Q_OBJECT
public:
    explicit CFileTree(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *event);

protected:
    void paintEvent(QPaintEvent *e);

    void mousePressEvent(QMouseEvent *event);

    void contextMenuEvent(QContextMenuEvent *);

    void keyPressEvent(QKeyEvent *event);
private:
    void drawBackground(QPainter* painter);


private:
    QMenu* rootContextMenu;

    QAction* rootDeleteAct;
    QAction* rootRenameAct;
    QAction* rootLocateAct;


    QMenu* childContextMenu;

    QAction* renameAct;
    QAction* locateAct;
    QAction* deleteAct;

    RenameDlg* renameDlg;

    QPoint m_lastPot;

private:
    void initContextMenu();


private slots:
    void RenameItem();
    void DeleteItem();
    void RenameFolder();
    void DeleteFolder();
    void LocateFolder();
    void DoRenameItem(const QString& str);
    void SaveSettings();
Q_SIGNALS:
    void sig_DeleteFolder(const QString& strFolderName);
};

#endif // IMAGETREE_H
