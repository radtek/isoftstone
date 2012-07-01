CONFIG  += console

HEADERS       = func.h \
                printitem.h
        
SOURCES       = main.cpp \
                printimpl.cpp \
                printfactory.cpp \
                printclass.cpp \
                serialize.cpp  \
                printitem.cpp
                
QT           += xml

target.path = $$[QT_INSTALL_EXAMPLES]/xml/readg
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS readg.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/xml/readg
INSTALLS += target sources