load(qttest_p4)

QT += declarative
SOURCES += tst_canvas.cpp

SOURCES += ../../src/canvas.cpp
SOURCES += ../../src/context2d.cpp
SOURCES += ../../src/canvastimer.cpp
HEADERS += ../../src/canvas.h
HEADERS += ../../src/canvastimer.h
HEADERS += ../../src/context2d.h

DEFINES += SRCDIR=\\\"$$PWD\\\"

