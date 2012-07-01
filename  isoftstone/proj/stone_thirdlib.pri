# LOG4CPLUS¿âµÄÒýÈë
LOG4CPLUSDIR = $(STONEDIR)/thirdparty/log4cplus-1.0.4-rc5-vc9
#$$LOG4CPLUSDIR/include 

INCLUDEPATH *=  $$LOG4CPLUSDIR/include
INCLUDEPATH *=  $(STONEDIR)/thirdparty/rapidxml 
                

LIBS *= -L$$LOG4CPLUSDIR/lib

debug{
	LIBS *= -llog4cplusD
}
release{
	LIBS *= -llog4cplus
}
