#ifndef POSDATAINFOINTF_H
#define POSDATAINFOINTF_H

#include <QString>
#include <QSharedPointer>

#include "posbasecls.h"

class IPOSItemDataInfo : public IPOSObject
{
public:
    virtual const QString* itemCode() const = 0;
    virtual const QString* itemDescr() const = 0;
};

typedef QSharedPointer<IPOSItemDataInfo> IPOSItemDataInfo_Ptr;
typedef QList<IPOSItemDataInfo_Ptr> POSItemDataInfoList;

class IPOSDataInfoManager : public IPOSObject
{
public:
    virtual void Initialize() = 0;
};

typedef QSharedPointer<IPOSDataInfoManager> IPOSDataInfoManager_Ptr;

#endif // POSDATAINFOINTF_H
