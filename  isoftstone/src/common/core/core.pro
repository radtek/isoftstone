# »´æ÷…Ë÷√
include ($(STONEDIR)/proj/stone.pri)
include ($(STONEDIR)/proj/stone_thirdlib.pri)

TEMPLATE	= lib
CONFIG		+= qt warn_on thread dll
LANGUAGE	= C++

DEFINES         += ESCORE
DEFINES         -= UNICODE

HEADERS	+=  \
	algorithm.h \
	component.h \
	container2stream.h \
	coremacro.h \
	encrypt.h \
	enumfile.h \
	exceptions.h \
	general.h \
	objects.h \
	markupstl.h \
	md5.h \
	md5i.h \
	multitree.h \
	node.h \
	properties.h \
	serialcomm.h \
        serialize.cpp \
	serialcommuniximpl.h \
	serialcommwinimpl.h \
	sqlcommand.h \
	stringlist.h \
	transform.h \
	treeiterator.h  \
        base64.h \
        sbdes.h   \
        xmlsettings.h \
        exceptions.h
        			
SOURCES	+=  \
	component.cpp \
	container2stream.cpp \
	encrypt.cpp \
	objects.cpp \
	markupstl.cpp \
	md5.cpp \
	md5i.cpp \
	multitree.cpp \
	node.cpp \
	properties.cpp \
	serialcomm.cpp \
        serialize.cpp \
	serialcommuniximpl.cpp \
	serialcommwinimpl.cpp \
	stringlist.cpp \
	transform.cpp \
	treeiterator.cpp  \
        base64.cpp   \
        sbdes.cpp  \
        xmlsettings.cpp \
        exceptions.cpp

	
INCLUDEPATH *= $$DEPENDPATH

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug {
	TARGET = core_d
}
release {
	TARGET = core
}

debug{
	LIBS += 
}

release{
	LIBS += 
}
