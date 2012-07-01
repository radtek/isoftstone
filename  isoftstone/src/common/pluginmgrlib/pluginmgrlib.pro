
TEMPLATE = lib
DEFINES += PLUGINMGR_LIB


INCLUDEPATH += . \
	    	
include ($(STONEDIR)/proj/stone.pri)

HEADERS += pluginmanager.h \
	   pluginwindow.h  \
	   tablewidget.h	   	   

SOURCES += pluginmanager.cpp \
	   pluginwindow.cpp  \
	   tablewidget.cpp

RESOURCES += app.qrc

DESTDIR    = $$STONE_LIB_PATH 
DLLDESTDIR = $$STONE_BIN_PATH
		
LIBS *= 

debug{
	TARGET = pluginmgrlib_d   
}
release{
	TARGET = pluginmgrlib
}








