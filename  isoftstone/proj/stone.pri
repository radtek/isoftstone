
DEVHOME = $$(STONEDIR)
isEmpty(DEVHOME) {
	error('STONEDIR'�����������뱻����.)
}
# ����ͨ���������� LCSHHOME ָ��ϵͳ����Ŀ¼
STONEHOME = $$(STONEDIR)
isEmpty(STONEHOME) {
	error('STONEDIR'�����������뱻����.)
}
# ����ϵͳִ���ļ�·�������ļ�·����ͷ�ļ�����·������
STONE_BIN_PATH = $$(STONEDIR)/bin
STONE_LIB_PATH = $$(STONEDIR)/lib
STONE_OBJ_PATH = $$(STONEDIR)/obj
STONE_SRC_PATH = $$(STONEDIR)/src
STONE_PRI_PATH = $$(STONEDIR)/proj

QT      += xml

CONFIG	+= qt warn_on thread xml ordered

CONFIG  -= debug release

LANGUAGE = C++

LIBS *= -L$$STONE_LIB_PATH

DEPENDPATH *= .\
	    $$STONE_SRC_PATH/include \
            $$STONE_SRC_PATH/common/common \
            $$STONE_SRC_PATH/hmi/auto_element

INCLUDEPATH *= $$DEPENDPATH

MOC_DIR = .moc

UI_DIR  = .ui

RCC_DIR = .rcc
    
BUILDTYPE *= debug

DESTDIR = $$STONE_BIN_PATH    
    
STONE_OBJ_PATH = $$STONE_OBJ_PATH/$$BUILDTYPE

OBJECTS_DIR = $$STONE_OBJ_PATH/$$TARGET

equals(BUILDTYPE,debug){
	CONFIG *= debug
	DEFINES *= STONE_DEBUG
}
equals(BUILDTYPE,release){
	CONFIG *= release
	DEFINES *= STONE_NO_DEBUG
}

# ���ظ���ĵ�������
include ($$STONE_PRI_PATH/stone_thirdlib.pri)
