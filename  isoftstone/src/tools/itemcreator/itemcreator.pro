
include ($(STONEDIR)/proj/stone.pri)

INCLUDEPATH *= $$STONE_SRC_PATH/itemlib

HEADERS       =   
        
SOURCES       = main.cpp             

debug{
	TARGET = itemcreator_d   
}
release{
	TARGET = itemcreator
}

debug{
        LIBS += -lcommon_d \
                -litemlib_d
}
else{
        LIBS += -lcommon \
                -litemlib
}



