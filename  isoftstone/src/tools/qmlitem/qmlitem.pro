
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

QT           += xml
QT           += declarative

CONFIG       += lib

HEADERS       =  \
                 qmlitem.h \
                 itemplugin.h
        
SOURCES       =  \
                qmlitem.cpp \
                itemplugin.cpp       

debug{
        LIBS += -lcommon_d
}
else{
        LIBS += -lcommon
}
                