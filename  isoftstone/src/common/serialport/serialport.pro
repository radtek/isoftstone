
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE                = lib

DEFINES                 += STATIC_LIB

DEPENDDIR               = .
INCLUDEDIR              = .
HEADERS                 = qextserialbase.h \
                          qextserialport.h \
                          qextserialenumerator.h \
                          serial_include.h
SOURCES                 = qextserialbase.cpp \
                          qextserialport.cpp \
                          qextserialenumerator.cpp

unix:HEADERS           += posix_qextserialport.h
unix:SOURCES           += posix_qextserialport.cpp
unix:DEFINES           += _TTY_POSIX_


win32:HEADERS          += win_qextserialport.h
win32:SOURCES          += win_qextserialport.cpp
win32:DEFINES          += _TTY_WIN_

win32:LIBS             += -lsetupapi


DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug{
	TARGET = serialport_d
} 
release{
	TARGET = serialport
}

