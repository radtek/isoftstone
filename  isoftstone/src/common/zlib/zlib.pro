include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib
CONFIG		+= qt warn_on thread dll
LANGUAGE	= C++

HEADERS += minizip.h \
	zip.h \
	unzip.h \
	ioapi.h \
	iowin32.h \
	crypt.h

SOURCES += minizip.cpp \
	zip.cpp \
	unzip.cpp \
	ioapi.cpp

win32{
	SOURCES += iowin32.cpp
}
	
INCLUDEPATH *= $$DEPENDPATH

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug {
	TARGET = zip_d
}
release {
	TARGET = zip
}