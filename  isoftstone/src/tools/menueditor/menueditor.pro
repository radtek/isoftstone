
TEMPLATE = app


HEADERS  += mainwindow.h \
	    setting.h\
	    commandview.h\
	    treeview.h\
	    treewidget.h

SOURCES  += main.cpp\
            mainwindow.cpp \
	    setting.cpp\
	    commandview.cpp\
	    treeview.cpp\
	    treewidget.cpp
            
FORMS += menumgr.ui   

UIDIR += .ui
MOCDIR += .moc
         

