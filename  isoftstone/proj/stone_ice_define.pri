#########################################################################################
## ICE 3.4.2 ������
#####################################################################################################

INCLUDEPATH += $(ICE_HOME)/include
INCLUDEPATH += $(ICE_HOME)/include/stlport

LIBS += -L$(ICE_HOME)/lib \
        -liced -liceutild -licessld
        
#���ӵ�ICE lib��Ŀ¼
unix {
	LIBS += -lXt -lX11
	contains( LCSH_QMAKESPEC, solaris.* ) {
		LIBS += -lposix4 -lthread 
	}
}
