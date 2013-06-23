#ifndef POSSTORAGEINTF_H
#define POSSTORAGEINTF_H

#include "posbasecls.h"
#include "posdatainfointf.h"

#include <QString>
#include <QSharedPointer>

const char* const BEH_DATATABLE = "BEHAVIOUR_DATATABLE";

const char* const REG_POSSTORAGE_ITEM = "POS.STORAGE.ITEM";

class IPOSDataTable : virtual public IPOSObject
{
public:
    virtual void CheckSchema() = 0;
    virtual bool isEmpty() = 0;
    virtual quint32 recCount() = 0;
};

class IPOSItem : virtual public IPOSDataTable
{
public:
    virtual IPOSItemDataInfo_Ptr GetItemInfo(const QString* itemcode) = 0;
};

class IPOSStorageManager : public IPOSObject
{
public:
    virtual void RegisterTable(const QString& classname) = 0;

    virtual void Initialize() = 0;
    virtual void Finalize() = 0;
};

typedef QSharedPointer<IPOSStorageManager> IPOSStorageManager_Ptr;

#endif // POSSTORAGEINTF_H
