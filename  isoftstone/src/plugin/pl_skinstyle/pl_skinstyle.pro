
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE      = lib

HEADERS       = \
                stylesheeteditor.h

SOURCES       = \
                stylesheeteditor.cpp
                                
FORMS         = stylesheet.ui

RESOURCES     = stylesheet.qrc

debug{
	TARGET = pl_skinstyle_d   
}
release{
	TARGET = pl_skinstyle
}
  
debug{
	LIBS   +=   -lcommon_d       
           
}
release{
	LIBS   +=  -lcommon
}



                
