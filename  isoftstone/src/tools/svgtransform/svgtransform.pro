
include ($(STONEDIR)/proj/stone.pri)

HEADERS       =  transcommon.h \
                 transform.h \
                 symbol.h 
        
SOURCES       = main.cpp \
                transcommon.cpp \
                transform.cpp \
                symbol.cpp            

debug{
        LIBS += -lcommon_d
}
else{
        LIBS += -lcommon
}
                
QT           += xml


