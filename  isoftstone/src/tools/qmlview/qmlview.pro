
# 全局设置

TEMPLATE	= app

QT              += declarative

DEFINES += QT_NO_OPENGL

HEADERS	    =   \
                qmlmainwindow.h
                
SOURCES	    =   main.cpp \
                qmlmainwindow.cpp
                
#RESOURCES   =	qmlview.qrc              

     
		
LIBS *= 

debug{
	TARGET = qmlview_d   
}
release{
	TARGET = qmlview
}
