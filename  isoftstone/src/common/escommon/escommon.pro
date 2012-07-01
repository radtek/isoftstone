# »´æ÷…Ë÷√
include ($(STONEDIR)/proj/stone.pri)
include ($(STONEDIR)/proj/stone_ice_define.pri)

TEMPLATE	= lib
CONFIG		+= qt warn_on thread dll
LANGUAGE	= C++
			
HEADERS	+=  \
	objectdirectacessvector.h \
	objectmap.h \
	objectmultimap.h \
	objectset.h \
	objectsortvector.h \
	predicateinterface.h \
	qualitywrapper.h \
	synchronousset.h \
	synchronousvector.h \
	unaryprocinterface.h \
	freetemplate.h \
	limitpool.h

SOURCES	+=  \
	objectdirectacessvector.cpp \
	objectmap.cpp \
	objectmultimap.cpp \
	objectset.cpp \
	objectsortvector.cpp \
	predicateinterface.cpp \
	qualitywrapper.cpp \
	synchronousset.cpp \
	synchronousvector.cpp \
	unaryprocinterface.cpp \
	freetemplate.cpp \
	limitpool.cpp

DEPENDPATH *= \
	$(STONEDIR)/src/common/core \
	$(STONEDIR)/src/common/common

	
INCLUDEPATH *= $$DEPENDPATH


DESTDIR    = $$STONE_LIB_PATH 
DLLDESTDIR = $$STONE_BIN_PATH     

debug {
	TARGET = escommon_d
}
release {
	TARGET = escommon
}

debug{
	LIBS += \
		-lcore_d
}

release{
	LIBS += \
		-lcore
}
