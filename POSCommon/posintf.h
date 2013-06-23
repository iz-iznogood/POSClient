#ifndef POSINTF_H
#define POSINTF_H

#include "posbasecls.h"
#include "logger.h"
#include "posstorageintf.h"
#include "posdatainfointf.h"
#include "postransactionintf.h"
#include "posdeviceintf.h"

#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include <QDataStream>

class IPOSLibraryManager : public IPOSObject
{
public:
    virtual void LoadLibraries() = 0;
    virtual IPOSObject* CreateObject(const QString& classname) = 0;
};

typedef QSharedPointer<IPOSLibraryManager> IPOSLibraryManager_Ptr;

struct LibraryClassesDataRec
{
    quint32 size;
    char* data;
};

struct ClassRec
{
    QStringList Behaviours;
    QString classname;
};

inline QDataStream& operator<<(QDataStream& s, const ClassRec& rec)
{
    s << rec.Behaviours;
    s << rec.classname;

    return s;
}

inline QDataStream& operator>>(QDataStream& s, ClassRec& rec)
{
    s >> rec.Behaviours;
    s >> rec.classname;

    return s;
}

typedef QList<ClassRec> LibraryClassList;

class IPOSLibrary : public IPOSObject
{
public:
    virtual IPOSObject* CreateObject(const QString& classname) = 0;
    virtual void GetClassList(LibraryClassesDataRec* const rec) = 0;

    virtual void Initialize() = 0;
    virtual void Finalize() = 0;
};

typedef IPOSLibrary* (*getLibraryProc)();

class IPOSErrorManager : public IPOSObject
{
public:
    virtual void HandleException(std::exception* exception) = 0;

    virtual void LogError(const ErrorType type, const quint16 level, const QString& message) = 0;
    virtual void LogWarning(const ErrorType type, const quint16 level, const QString& message) = 0;
    virtual void LogInfo(const ErrorType type, const quint16 level, const QString& message) = 0;
};

typedef QSharedPointer<IPOSErrorManager> IPOSErrorManager_Ptr;

struct POSGlobals
{
public:
    IPOSErrorManager_Ptr ErrorManager;
    IPOSLibraryManager_Ptr LibraryManager;
    IPOSStorageManager_Ptr StorageManager;
    IPOSDataInfoManager_Ptr DataInfoManager;
    IPOSDeviceManager_Ptr DeviceManager;
    IPOSDocument_Ptr Document;
};

#endif // POSINTF_H
