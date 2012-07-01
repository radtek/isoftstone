
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= lib

DEFINES += QT_NO_OPENGL    EXTITEM

HEADERS	    =   extitem.h \
                roundrectitem.h \
                roundbutton.h  \
                tooltipitem.h \
                menupixmapitem.h  \
                pipetimeitem.h \
                meter1.h \
                meter2.h \
                thermometer.h \
                toolbaritem.h \
                contextmenu.h \
                menuitem.h \
                logobutton.h \
                progressbar1.h \
                scale2.h \
                scale1.h \
                indicator.h \
                lcdnumber.h \
                sounditem.h \
                lightitem.h \
                batteryitem.h \
                gifitem.h   \
                singlechart.h

                
SOURCES	    =   roundrectitem.cpp \
                roundbutton.cpp  \
                tooltipitem.cpp \
                menupixmapitem.cpp  \
                pipetimeitem.cpp  \
                meter1.cpp \
                meter2.cpp \
                thermometer.cpp \
                toolbaritem.cpp \
                contextmenu.cpp \
                menuitem.cpp  \
                logobutton.cpp \
                progressbar1.cpp \
                scale2.cpp \
                scale1.cpp \
                indicator.cpp \
                lcdnumber.cpp \
                sounditem.cpp \
                lightitem.cpp \
                batteryitem.cpp \
                gifitem.cpp  \
                singlechart.cpp
                          
	
INCLUDEPATH *= \
     
DESTDIR    = $$STONE_LIB_PATH 
DLLDESTDIR = $$STONE_BIN_PATH
		
LIBS *= 

debug{
	TARGET = extitem_d   
}
release{
	TARGET = extitem
}

debug{
	LIBS   +=          
           
}
release{
	LIBS   += 
}
