
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

DEFINES         += ITEMLIB

HEADERS	    = itemlib.h \
              Bar.h \
              DText.h   \
              Poke.h     \
              Text.h      \
              ACLine.h  \
              ACLineEnd.h \
              Bus.h \
              CBreaker.h \
              ConnectLine.h \
              Sensitive.h \
              Transformer.h \
              Disconnector.h \
              Reactor.h \
              Capacitor.h \
              CreateItem.h \ 
              ItemFactory.h \
              Clock.h    \
              Image.h   \
              Generator.h \
              GroundDisconnector.h \
              Bay.h  \
              Curve.h
                           
SOURCES	    = Bar.cpp    \
              DText.cpp   \
              Poke.cpp     \   
              Text.cpp      \
              ACLine.cpp  \
              ACLineEnd.cpp \
              Bus.cpp \
              CBreaker.cpp \
              ConnectLine.cpp \
              Sensitive.cpp \
              Transformer.cpp \
              Disconnector.cpp \
              Reactor.cpp \
              Capacitor.cpp \
              CreateItem.cpp \
              ItemFactory.cpp \
              Clock.cpp   \
              Image.cpp  \
              Generator.cpp  \
              GroundDisconnector.cpp \
              Bay.cpp  \
              Curve.cpp
               
                
RESOURCES *=	
	
INCLUDEPATH *= 
		
LIBS *= 

DESTDIR    = $$STONE_LIB_PATH 

DLLDESTDIR = $$STONE_BIN_PATH

debug{
	TARGET = itemlib_d   
}
release{
	TARGET = itemlib
}

debug{
	LIBS += \  
                 -lcommon_d 
           
}
release{
	LIBS += \
                -lcommon
}
