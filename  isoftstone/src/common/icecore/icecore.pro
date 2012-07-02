# »´æ÷…Ë÷√
include ($(STONEDIR)/proj/stone.pri)
include ($(STONEDIR)/proj/stone_ice_define.pri)
include ($(STONEDIR)/proj/stone_thirdlib.pri)

TEMPLATE	= lib
CONFIG		+= qt warn_on thread dll
LANGUAGE	= C++

DEFINES         += ICECORE
DEFINES         -= UNICODE

INCLUDEPATH     += ../core

HEADERS	+=  \
        icecore.h \
	activity.h \
	activitythread.h \
	dispatchthread.h \
	dllplugin.h \
	iceexceptions.h \
	histring.h \
	invokecommand.h \
	lapplication.h \
	llogger.h \
	sessiontemplate.h \
	taskpool.h \
	threadmonitor.h \
	threadpool.h \
	threadwrapper.h \
	timerreactor.h 
        			
SOURCES	+=  \
	activity.cpp \
	activitythread.cpp \
	dispatchthread.cpp \
	dllplugin.cpp \
	iceexceptions.cpp \
	histring.cpp \
	invokecommand.cpp \
	lapplication.cpp \
	llogger.cpp \
	sessiontemplate.cpp \
	taskpool.cpp \
	threadmonitor.cpp \
	threadpool.cpp \
	threadwrapper.cpp \
	timerreactor.cpp 

	
INCLUDEPATH *= $$DEPENDPATH

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug {
	TARGET = icecore_d
}
release {
	TARGET = icecore
}

debug{
	LIBS += -lcore_d
}

release{
	LIBS += -lcore
}
