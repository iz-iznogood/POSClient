#-------------------------------------------------
#
# Project created by QtCreator 2013-05-07T14:58:50
#
#-------------------------------------------------

QT       += sql

QT       -= gui

TARGET = POSStorage
TEMPLATE = lib

DEFINES += POSSTORAGE_LIBRARY

SOURCES += positem.cpp \
    ../../../POSLibraryImpl/poslibrary.cpp \
    ../../../POSCommon/POSStorageImpl/posdatatable.cpp \
    ../../../POSCommon/POSStorageImpl/possqliteschemaupdater.cpp

HEADERS += positem.h\
    ../../../POSLibraryImpl/poslibrary.h \
    ../../../POSCommon/POSStorageImpl/posdatatable.h \
    ../../../POSCommon/POSStorageImpl/possqliteschemaupdater.h

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
            ../../../POSCommon \
            ../../../POSCommon/POSStorageImpl \
            ../../../POSComponents

