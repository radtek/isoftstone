#########################################################################################
## ICE 3.4.2 的引入
#####################################################################################################

INCLUDEPATH += $(ICE_HOME)/include
INCLUDEPATH += $(ICE_HOME)/include/stlport

LIBS += -L$(ICE_HOME)/lib \
        -liced -liceutild -licessld
        
#附加的ICE lib库目录
unix {
	LIBS += -lXt -lX11
	contains( LCSH_QMAKESPEC, solaris.* ) {
		LIBS += -lposix4 -lthread 
	}
}
