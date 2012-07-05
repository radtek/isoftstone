
# 全局设置
include ($(STONEDIR)/proj/stone.pri)

TEMPLATE	= app

HEADERS       = \
        
SOURCES       = main.cpp

debug{
	TARGET = dbi_d   
}
release{
	TARGET = dbi
}

debug{
	LIBS += \  
           
}
release{
	LIBS += \
}



