TEMPLATE = lib
CONFIG += qt plugin release
QT += declarative
QT += script
 
TARGET  = canvasplugin

 DESTDIR = ..\\Canvas
 OBJECTS_DIR = tmp
 MOC_DIR = tmp

 HEADERS += context2d.h \
            canvas.h \
            canvastimer.h \
            canvasplugin.h

 SOURCES += context2d.cpp \
            canvas.cpp \
            canvasplugin.cpp \
    canvastimer.cpp
