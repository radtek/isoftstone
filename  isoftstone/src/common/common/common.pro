
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

QT              += svg

DEFINES         += COMMONLIB

HEADERS	    =   painterpath.h   \
                resource.h \
                scenebase.h \
                window.h \
                ialgorithm.h \
                common.h  \
                thread.h  \
                setting.h \
                pluginmgrbase.h \
                config.h    \
                localserver.h \
                tcpclient.h
                 
SOURCES	    =   painterpath.cpp \
                resource.cpp \
                scenebase.cpp  \
                window.cpp \
                ialgorithm.cpp  \
                common.cpp  \
                thread.cpp  \
                setting.cpp \
                pluginmgrbase.cpp \
                config.cpp    \
                localserver.cpp \
                tcpclient.cpp
                
RESOURCES *=	

INCLUDEPATH *= \
		
LIBS *= 

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug{
	TARGET = common_d   
}
release{
	TARGET = common
}

debug{
	LIBS += \  
           
}
release{
	LIBS += \
}



