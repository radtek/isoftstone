/****************************************************************************
** 
** Copyright (c) 2009 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
** 
** This file is part of a Qt Solutions component.
**
** Commercial Usage  
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Solutions Commercial License Agreement provided
** with the Software or, alternatively, in accordance with the terms
** contained in a written agreement between you and Nokia.
** 
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
** 
** In addition, as a special exception, Nokia gives you certain
** additional rights. These rights are described in the Nokia Qt LGPL
** Exception version 1.1, included in the file LGPL_EXCEPTION.txt in this
** package.
** 
** GNU General Public License Usage 
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
** 
** Please note Third Party Software included with Qt Solutions may impose
** additional restrictions and it is the user's responsibility to ensure
** that they have met the licensing requirements of the GPL, LGPL, or Qt
** Solutions Commercial license and the relevant license of the Third
** Party Software they are using.
** 
** If you are unsure which license is appropriate for your use, please
** contact Nokia at qt-info@nokia.com.
** 
****************************************************************************/

#ifndef QTWINDOWLISTMENU_H
#define QTWINDOWLISTMENU_H

#include <QtCore/QPointer>
#include <QtCore/QMap>
#include <QtGui/QMenu>
#include <QtGui/QIcon>

class QMdiArea;
class QMdiSubWindow;
class QSignalMapper;
class QMenuBar;

#if defined(Q_WS_WIN)
#  if !defined(QT_QTWINDOWLISTMENU_EXPORT) && !defined(QT_QTWINDOWLISTMENU_IMPORT)
#    define QT_QTWINDOWLISTMENU_EXPORT
#  elif defined(QT_QTWINDOWLISTMENU_IMPORT)
#    if defined(QT_QTWINDOWLISTMENU_EXPORT)
#      undef QT_QTWINDOWLISTMENU_EXPORT
#    endif
#    define QT_QTWINDOWLISTMENU_EXPORT __declspec(dllimport)
#  elif defined(QT_QTWINDOWLISTMENU_EXPORT)
#    undef QT_QTWINDOWLISTMENU_EXPORT
#    define QT_QTWINDOWLISTMENU_EXPORT __declspec(dllexport)
#  endif
#else
#  define QT_QTWINDOWLISTMENU_EXPORT
#endif

class QT_QTWINDOWLISTMENU_EXPORT QtWindowListMenu : public QMenu
{
    Q_OBJECT

public:
    QtWindowListMenu(QWidget *parent = 0);
    virtual void attachToMdiArea(QMdiArea *mdiArea);
    QMdiArea *attachedMdiArea() const;

    void setWindowIcon(const QMdiSubWindow *window, const QIcon &icon);
    QIcon windowIcon(const QMdiSubWindow *window) const;
    void setDefaultIcon(const QIcon &icon);
    QIcon defaultIcon() const;

    enum StandardAction {
        CloseAction    = 0,
        CloseAllAction = 1,
        TileAction     = 3,
        CascadeAction  = 4,
        NextAction     = 6,
        PrevAction     = 7
    };

    QAction *standardAction(StandardAction item) const;

    // obsolete:
    QAction *addTo(const QString &text, QMenuBar *menubar, int idx = -1);
    void setCloseIcon(const QIcon &icon);
    void setCloseAllIcon(const QIcon &icon);
    void setCascadeIcon(const QIcon &icon);
    void setTileIcon(const QIcon &icon);

protected Q_SLOTS:
    virtual void syncWithMdiArea();
    void activateWindow(QAction *act);
    void windowDestroyed(QObject *obj);

private:
    bool attachToClosestMdiAreaObject();
    QPointer<QMdiArea> mdi;
    QActionGroup *stdGroup;
    QActionGroup *winGroup;
    QMap<QAction *, QMdiSubWindow *> winMap;
    QMap<const QMdiSubWindow *, QIcon> iconMap;
    QIcon defIcon;
};

#endif
