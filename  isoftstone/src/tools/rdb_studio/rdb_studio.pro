
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= app

HEADERS       = \
        
SOURCES       = main.cpp

debug{
	TARGET = rdb_studio_d   
}
release{
	TARGET = rdb_studio
}

debug{
	LIBS += \  
           
}
release{
	LIBS += \
}



