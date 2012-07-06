
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

QT              += sql

#INCLUDEPATH     += $$(STONEDIR)/include

TEMPLATE	= app

HEADERS       = \
        
SOURCES       = main.cpp

debug{
	TARGET = dbi_d   
}
release{
	TARGET = dbi
}

debug{
	LIBS += -lcommon_d \
                -lrtdb_api_d  
           
}
release{
	LIBS += -lcommon \
                -lrtdb_api 
}



