
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

QT              += sql

#INCLUDEPATH     += $$(STONEDIR)/include

TEMPLATE	= app

HEADERS       = datawidget.h \
                modelwidget.h \
                uiwidget.h
        
SOURCES       = main.cpp \
                datawidget.cpp \
                modelwidget.cpp

FORMS        += tablemodel.ui \
                fieldmodel.ui
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



