CONFIG  += console debug

HEADERS       = vcimdbdata.h \
                Logger.h     \
                vcimdata_common.h
        
SOURCES       = main.cpp  \
                vcimdbdata.cpp \
                Logger.cpp
                
                
QT           += xml

win32{
        HEADERS += rtdb_api_sim.h 
        
        SOURCES += rtdb_api_sim.cpp 
}
unix{        
	INCLUDEPATH += . \
                $(D5000_HOME)/src/include/wams
                  
				
        LIBS +=                          \
                -lwams_dbi               \
                -lwhdb_pnapi             \
                -lservices               \
                -lwamstransid
}


unix{
	INCLUDEPATH += . \
	    		$(D5000_HOME)/src/include \
                        $(D5000_HOME)/src/include/wams \
                        $(D5000_HOME)/src/include/whdb/whdb_api \
                        $(D5000_HOME)/src/include/whdb/whdb_pnapi 
				
        LIBS += -L$(D5000_HOME)/src/lib \
                -L$(D5000_HOME)/lib \
                -L/usr/X11R6/lib64

	LIBS += -lrtdb_api
}
     


