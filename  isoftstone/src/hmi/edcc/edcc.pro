
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= app

DEFINES += QT_NO_OPENGL

HEADERS	    =   mainwindow.h \
                server.h \
                resource.h \
                task.h \
                view.h \
                scene.h \
                dcc-global.h
                
SOURCES	    =   main.cpp \
                mainwindow.cpp \
                server.cpp \
                resource.cpp \
                task.cpp \
                view.cpp \
                scene.cpp
                
RESOURCES   =	edcc.qrc              
	
INCLUDEPATH += $(STONEDIR)/src/common/commonwidget \
                $(STONEDIR)/src/common/common \
                $(STONEDIR)/src/common/pluginmgrlib \
                $(STONEDIR)/src/common/qtsolutions \
                $(STONEDIR)/src/hmi/extitem \
                $(STONEDIR)/src/hmi/itemlib  \
                $(STONEDIR)/src/hmi/contextmenu
                
     
		
LIBS *= 

debug{
	TARGET = edcc_d   
}
release{
	TARGET = edcc
}

debug{
	LIBS   += -lcommonwidget_d \
                  -lextitem_d \
                  -litemlib_d \
                  -lcommon_d  \
                  -lcontextmenu_d \
                  -lpluginmgrlib_d  \
                  -lqtsolutions    
           
}
release{
	LIBS   += -lcommonwidget \
                  -lextitem  \
                  -litemlib \ 
                  -lcommon   \
                  -lcontextmenu \
                  -lpluginmgrlib \
                  -lqtsolutions
}
