
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= app

HEADERS	    =   mainwindow.h \
		diagramscene.h \
                mainwindow_view.h
                
SOURCES	    =   main.cpp \   
                mainwindow.cpp \
		diagramscene.cpp \
                mainwindow_view.cpp
                
RESOURCES   =	diagramscene.qrc              
	
INCLUDEPATH *= \
                $$STONE_SRC_PATH/element  \
                $$STONE_SRC_PATH/itemlib  \
                $$STONE_SRC_PATH/itemfactory       
		
LIBS *= 

debug{
	TARGET = draw_d   
}
release{
	TARGET = draw
}

debug{
	LIBS   +=            \
                -lcommon_d   \
                -lelement_d  \
                -litemlib_d
           
}
release{
	LIBS   +=            \
                -lcommon     \
                -lelement    \
                -litemlib 
}
