
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

DEFINES         += ELEMENTLIB

HEADERS	    =   element.h \
                arrow.h   \
                diagramtextitem.h \
                diagramitem.h
                 
SOURCES	    =   arrow.cpp \
                diagramtextitem.cpp \
                diagramitem.cpp 
                
RESOURCES *=	
	
INCLUDEPATH *= \
            $(STONEDIR)/thirdparty/rapidxml  
		
LIBS *= 

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug{
	TARGET = element_d   
}
release{
	TARGET = element
}

debug{
	LIBS += \  
                 -lcommon_d 
           
}
release{
	LIBS += \
                -lcommon
}
