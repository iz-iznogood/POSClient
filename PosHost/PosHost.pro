SOURCES += \
    main.cpp \
    posapplication.cpp \
    ../POSComponents/logger.cpp \
    poserrormanager.cpp \
    posglobals.cpp \
    poslibrarymanager.cpp \
    posstoragemanager.cpp \
    posmainform.cpp \
    posdatainfomanager.cpp \
    posdevicemanager.cpp

HEADERS += \
    posapplication.h \
    ../POSComponents/logger.h \
    poserrormanager.h \
    posglobals.h \
    poslibrarymanager.h \
    posstoragemanager.h \
    posmainform.h \
    ../POSCommon/posstorageintf.h \
    ../POSCommon/posintf.h \
    ../POSCommon/posexception.h \
    ../POSCommon/posconst.h \
    ../POSCommon/posbasecls.h \
    ../POSCommon/posdatainfointf.h \
    posdatainfomanager.h \
    ../POSCommon/posserializableintf.h \
    ../POSCommon/postransactionintf.h \
    ../POSCommon/posdeviceintf.h \
    posdevicemanager.h

INCLUDEPATH += \
    ../POSCommon \
    ../POSComponents

QT       += core gui sql

FORMS += \
    posmainform.ui

DESTDIR = /home/chriss/QtProjects/bin
