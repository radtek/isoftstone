include ($(STONEDIR)/proj/stone.pri)

QT              += sql

TEMPLATE	= app

HEADERS       += \
		modelwindow.h \
		modelcomm.h \
		modelctrl.h \
		modeldata.h \
		nodefind.h \
		dommodel.h \
		domitem.h

SOURCES       +=  main.cpp \
		modelwindow.cpp \
		modelcomm.cpp \
		modelctrl.cpp \
		modeldata.cpp \
		nodefind.cpp \
		dommodel.cpp \
		domitem.cpp


FORMS 	     += finddialog.ui \
		modelwindow.ui 


debug{
	TARGET = modeleditor_d   
}
release{
	TARGET = modeleditor
}

debug{
	LIBS += -lcommon_d \
                -lrtdb_api_d  
           
}
release{
	LIBS += -lcommon \
                -lrtdb_api 
}
