
include ($(STONEDIR)/proj/stone.pri)

HEADERS       =  \
                 transform.h \
                 transcommon.h
        
SOURCES       = main.cpp \
                transform.cpp  \
                transcommon.cpp          

debug{
        LIBS += -lcommon_d
}
else{
        LIBS += -lcommon
}
                
QT           += xml


