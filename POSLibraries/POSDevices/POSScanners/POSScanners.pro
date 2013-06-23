#-------------------------------------------------
#
# Project created by QtCreator 2013-06-19T16:30:38
#
#-------------------------------------------------

QT       -= gui

TARGET = POSScanners
TEMPLATE = lib

DEFINES += POSSCANNERS_LIBRARY

SOURCES += \
    posbasescanner.cpp \
    ../../../POSLibraryImpl/poslibrary.cpp

HEADERS += \
    posbasescanner.h \
    ../../../POSLibraryImpl/poslibrary.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

INCLUDEPATH += \
            ../../../POSLibraryImpl \
            ../ \
            ../../../POSCommon \
            ../../../POSComponents \
