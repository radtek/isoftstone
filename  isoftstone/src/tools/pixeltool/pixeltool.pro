TEMPLATE = app
CONFIG  += qt warn_on
QT += network

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

DEPENDPATH += .
INCLUDEPATH += .
TARGET = pixeltool

SOURCES += main.cpp qpixeltool.cpp
HEADERS += qpixeltool.h

