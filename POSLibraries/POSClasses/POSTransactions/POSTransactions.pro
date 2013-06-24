#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T00:50:31
#
#-------------------------------------------------

QT       -= gui

TARGET = POSTransactions
TEMPLATE = lib

DEFINES += POSTRANSACTIONS_LIBRARY

SOURCES += \
    ../../../POSLibraryImpl/poslibrary.cpp \
    posdocument.cpp \
    possalesdocument.cpp \
    ../../../POSCommon/POSSerializableImpl/POSTransactionImpl/postransaction.cpp \
    posdocitemline.cpp \
    possaledocitemline.cpp

HEADERS += \
    ../../../POSCommon/POSSerializableImpl/posserializable.h \
    ../../../POSLibraryImpl/poslibrary.h \
    posdocument.h \
    possalesdocument.h \
    ../../../POSCommon/POSSerializableImpl/POSTransactionImpl/postransaction.h \
    posdocitemline.h \
    possaledocitemline.h

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
            ../../../POSCommon/POSSerializableImpl \
            ../../../POSCommon/POSSerializableImpl/POSTransactionImpl \
            ../../../POSComponents

DESTDIR = /home/chriss/QtProjects/bin/Libraries
