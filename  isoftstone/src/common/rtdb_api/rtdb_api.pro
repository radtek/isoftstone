
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

QT              += sql

DEFINES         += EXPORT_STATIC

HEADERS	    =   \
                 
SOURCES	    =   rtdb_api.cpp \
                odb_api.cpp
                
RESOURCES *=	

INCLUDEPATH *= \
		
LIBS *= 

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug{
	TARGET = rtdb_api_d   
}
release{
	TARGET = rtdb_api
}

debug{
	LIBS += -lcommon_d  
           
}
release{
	LIBS += -lcommon
}



