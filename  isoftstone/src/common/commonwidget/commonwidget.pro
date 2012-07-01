
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

DEFINES += QT_NO_OPENGL COMMON_WIDGET

HEADERS	    =   customdef.h \
                util.h \
                filetree.h \
                lineedit.h \
                listwidget.h \
                progress.h \
                renamedlg.h \
                toolbar.h \
                colorwidget.h \
                createdockdialog.h \
                colordockwidget.h \
                colorframe.h  \
                mainwindow_dock.h  \
                tipframe.h

                
SOURCES	    =   filetree.cpp \
                lineedit.cpp \
                listwidget.cpp \
                progress.cpp \
                renamedlg.cpp \
                toolbar.cpp  \
                colorwidget.cpp \
                colordockwidget.cpp \
                mainwindow_dock.cpp \
                colorframe.cpp \
                tipframe.cpp
                
                          
	
INCLUDEPATH *= \

DESTDIR    = $$STONE_LIB_PATH 
DLLDESTDIR = $$STONE_BIN_PATH     
		
LIBS *= 

debug{
	TARGET = commonwidget_d   
}
release{
	TARGET = commonwidget
}

debug{
	LIBS   +=   -lcommon_d       
           
}
release{
	LIBS   +=  -lcommon
}
