
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE      = lib

DEFINES        += MENULIB

HEADERS       = \
                menumanager.h \
                menuloader.h \
                cmloader.h 

SOURCES       = \
                menumanager.cpp \
                menuloader.cpp \
                cmloader.cpp

DESTDIR    = $$STONE_LIB_PATH 
DLLDESTDIR = $$STONE_BIN_PATH

debug{
	TARGET = contextmenu_d   
}
release{
	TARGET = contextmenu
}

debug{
	LIBS   += -lcommon_d         
           
}
release{
	LIBS   += -lcommon
}

  



                
