
#include "filetree.h"

CFileTree::CFileTree(QWidget *parent) :QTreeWidget(parent)
{
    renameDlg=new RenameDlg(this);
    renameDlg->hide();
    connect(renameDlg,SIGNAL(sig_SetText(QString)),this,SLOT(DoRenameItem(QString)));
    initContextMenu();
}

void CFileTree::initContextMenu()
{
    rootContextMenu=new QMenu(tr("Root Context Menu"),this);

    rootDeleteAct=new QAction(QIcon(":/images/delete.png"),tr("delete"),this);

    rootLocateAct=new QAction(QIcon(":/images/locate_folder.png"),tr("locate"),this);

    rootRenameAct=new QAction(QIcon(":/images/rename.png"),tr("rename"),this);

    rootContextMenu->addAction(rootRenameAct);
    rootContextMenu->addAction(rootLocateAct);
    rootContextMenu->addAction(rootDeleteAct);

    connect(rootRenameAct,SIGNAL(triggered()),this,SLOT(RenameFolder()));
    connect(rootLocateAct,SIGNAL(triggered()),this,SLOT(LocateFolder()));
    connect(rootDeleteAct,SIGNAL(triggered()),this,SLOT(DeleteFolder()));

    ////////
    childContextMenu =new QMenu(tr("Child Context Menu"),this);

    /// setup actions
    renameAct=new QAction(QIcon(":/images/rename.png"),tr("rename"),this);

    locateAct=new QAction(QIcon(":/images/locate_file.png"),tr("locate"),this);

    deleteAct=new QAction(QIcon(":/images/delete.png"),tr("delete"),this);

    childContextMenu->addAction(renameAct);
    childContextMenu->addAction(locateAct);
    childContextMenu->addAction(deleteAct);

    connect(renameAct,SIGNAL(triggered()),this,SLOT(RenameItem()));
    connect(deleteAct,SIGNAL(triggered()),this,SLOT(DeleteItem()));
}

void CFileTree::resizeEvent(QResizeEvent *event)
{
    qreal firstWid = width() * 0.3;
    qreal secondWid = width() * 0.7;

    setColumnWidth(0,firstWid);
    setColumnWidth(1,secondWid);

    QTreeWidget::resizeEvent(event);
}

void CFileTree::paintEvent(QPaintEvent *e)
{
    QPainter painter(viewport());
    drawBackground(&painter);

    QTreeWidget::paintEvent(e);
}

void CFileTree::mousePressEvent(QMouseEvent *event)
{
	if(event->buttons() & Qt::LeftButton)
    {
        QTreeWidget::mousePressEvent(event);
    }else{
        m_lastPot = event->pos();
        qDebug() << __FUNCTION__ << "mouse right button clicked";
    }
}

void CFileTree::contextMenuEvent(QContextMenuEvent *e)
{
    QTreeWidgetItem* currItem = currentItem();

    if(currItem)
    {
        // if it's root
        if(currItem->parent() == NULL)
        {
            rootContextMenu->exec(e->globalPos());
        }else{
            childContextMenu->exec(e->globalPos());
        }
    }
    e->accept();
}

void CFileTree::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        DeleteItem();
    }
}

void CFileTree::drawBackground(QPainter *painter)
{
#if 0
    painter->save();
    qreal thisWidth = width();
    qreal thisHeight = height();

    qreal rectWidth = (qreal)width()/IT_H_CNT;
    qreal rectHeight = (qreal)height()/IT_V_CNT;

    qreal initY = 0;

    painter->setPen(Qt::NoPen);
    for(int vIndex = 0 ;vIndex < IT_V_CNT ; vIndex++)
    {
        qreal initX = 0;
        int guard = 0;
        if(vIndex%2)
        {
            guard = 0;
        }else{
            guard = 1;
        }
        for(int hIndex = 0; hIndex < IT_H_CNT ; hIndex++)
        {
            QPointF topLeft(initX,initY);
            QPointF bottomRight(initX + rectWidth,initY + rectHeight);

            if(guard++%2)
            {
                painter->setBrush(IT_LIGHT_COLOR);
            }else{
                painter->setBrush(IT_DARK_COLOR);
            }

            painter->drawRect(QRectF(topLeft,bottomRight));

            initX += rectWidth;
        }

        initY += rectHeight;
    }
    painter->restore();
#endif


#if 1
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPoint(0,0),QPoint(width(),0));
    bgGradient.setColorAt(0.0,START_COLOR);
    bgGradient.setColorAt(1.0,END_COLOR);
//    bgGradient.setColorAt(1.0,QColor(210,210,210));
    painter->setBrush(bgGradient);
    painter->drawRect(rect());

    painter->restore();
#endif


}


void CFileTree::RenameItem()
{
    QTreeWidgetItem* currItem = currentItem();

    if(currItem)
    {
        QString strFullPath = currItem->data(1,Qt::UserRole).toString();

        if(strFullPath.isEmpty())
        {
            return ;
        }
        QFileInfo fInfo(strFullPath);
        QString strBaseName = fInfo.baseName();
        renameDlg->SetText(strBaseName);
        QRect currItemRect =visualItemRect(currItem);
        renameDlg->resize(currItemRect.size());
        renameDlg->move(currItemRect.bottomLeft());
        renameDlg->show();
    }

}

void CFileTree::DeleteItem()
{
    QTreeWidgetItem* currItem = currentItem();

    if(currItem)
    {
        QTreeWidgetItem* parentItem = currItem->parent();
        int childIndex = parentItem->indexOfChild(currItem);
        parentItem->takeChild(childIndex);
        Util::FSO::RemoveFile(currItem->data(1,Qt::UserRole).toString());
    }
}

void CFileTree::RenameFolder()
{

}

void CFileTree::LocateFolder()
{
    QTreeWidgetItem* currItem = currentItem();

    if(currItem)
    {
        QString strFolder = currItem->data(1,Qt::UserRole).toString();
        //Util::Shell::LocateFile(strFolder);
    }


}

void CFileTree::DeleteFolder()
{
    QTreeWidgetItem* currItem = currentItem();

    if(currItem)
    {
        int rootIndex = indexOfTopLevelItem(currItem);
        takeTopLevelItem(rootIndex);
        SaveSettings();
        emit sig_DeleteFolder(currItem->text(0));
    }

}

void CFileTree::SaveSettings()
{
    int rootCnt = topLevelItemCount();
    QString strAllFolders ;

    for(int rootIndex = 0 ; rootIndex < rootCnt ;rootIndex++)
    {
        QTreeWidgetItem* rootItem = topLevelItem(rootIndex);
        strAllFolders += tr("%1;").arg(rootItem->data(0,Qt::UserRole).toString());
    }

    Util::SettingMgr::WriteSetting("ImageRepository",strAllFolders);

}

void CFileTree::DoRenameItem(const QString &str)
{

    renameDlg->close();
    QTreeWidgetItem* currItem  = currentItem();

    if(currItem)
    {
        QString strFullPath = currItem->data(1,Qt::UserRole).toString();
        QFileInfo fInfo(strFullPath);
        QString strNewFileName ;
        strNewFileName = tr("%1/%2.%3").arg(fInfo.canonicalPath()).arg(str).arg(fInfo.completeSuffix());
        qDebug() << __FUNCTION__ << "strNewFileName:" <<  strNewFileName;

        QFile::rename(strFullPath,strNewFileName);

        //update current item
        currItem->setText(1,str);
        currItem->setData(1,Qt::UserRole,QVariant(strNewFileName));
        currItem->setToolTip(1,strNewFileName);
    }
}

