# »´æ÷…Ë÷√
include ($(STONEDIR)/proj/stone.pri)
include ($(STONEDIR)/proj/stone_ice_define.pri)
include ($(STONEDIR)/proj/stone_thirdlib.pri)

TEMPLATE	= lib
CONFIG		+= qt warn_on thread dll
LANGUAGE	= C++

DEFINES         += ESCORE
DEFINES         -= UNICODE

HEADERS	+=  \
	activity.h \
	activitythread.h \
	algorithm.h \
	component.h \
	container2stream.h \
	coremacro.h \
	dispatchthread.h \
	dllplugin.h \
	encrypt.h \
	enumfile.h \
	exceptions.h \
	general.h \
	histring.h \
	interface.h \
	invokecommand.h \
	lapplication.h \
	llogger.h \
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
	sessiontemplate.h \
	sqlcommand.h \
	stringlist.h \
	taskpool.h \
	threadmonitor.h \
	threadpool.h \
	threadwrapper.h \
	timerreactor.h \
	transform.h \
	treeiterator.h  \
        base64.h \
        sbdes.h
        			
SOURCES	+=  \
	activity.cpp \
	activitythread.cpp \
	component.cpp \
	container2stream.cpp \
	dispatchthread.cpp \
	dllplugin.cpp \
	encrypt.cpp \
	histring.cpp \
	interface.cpp \
	invokecommand.cpp \
	lapplication.cpp \
	llogger.cpp \
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
	sessiontemplate.cpp \
	stringlist.cpp \
	taskpool.cpp \
	threadmonitor.cpp \
	threadPool.cpp \
	threadwrapper.cpp \
	timerreactor.cpp \
	transform.cpp \
	treeiterator.cpp  \
        base64.cpp   \
        sbdes.cpp

	
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
