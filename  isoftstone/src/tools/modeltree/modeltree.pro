
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

QT              += sql

TEMPLATE	= app

HEADERS       = dbtree.h 
        
SOURCES       = main.cpp \
                dbtree.cpp

debug{
	TARGET = modeltree_d   
}
release{
	TARGET = modeltree
}

debug{
	LIBS += -lcommon_d \
                -lrtdb_api_d  
           
}
release{
	LIBS += -lcommon \
                -lrtdb_api 
}



