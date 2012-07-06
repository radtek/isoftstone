# »´æ÷…Ë÷√
include ($(LSCADA)/src/pri/sliceimpl.pri)

TEMPLATE	= lib
CONFIG		+= qt warn_on thread dll
LANGUAGE	= C++
			
HEADERS	+=  \
	commoncommand.h \
	connectpool.h \
	otlclient.h \
	otlv4.h

SOURCES	+=  \
	connectpool.cpp \
	otlclient.cpp

DEPENDPATH *= \
	$(LSCADA)/src/common/core

	
INCLUDEPATH *= $$DEPENDPATH
		

OBJECTS_DIR = $$LCSH_OBJ_PATH/common/sqlwrapper

DESTDIR = $$LCSH_BIN_PATH

debug {
	TARGET = sqlwrapper_d
}
release {
	TARGET = sqlwrapper
}

debug{
	LIBS += \
		-lslicelib_d \
		-lcore_d
}

release{
	LIBS += \
		-lslicelib \
		-lcore
}
