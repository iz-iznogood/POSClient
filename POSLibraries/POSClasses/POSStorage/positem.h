#ifndef POSITEM_H
#define POSITEM_H

#include <QStringList>
#include <QString>

#include "posstorageintf.h"
#include "posdatatable.h"
#include "posdatainfointf.h"

class POSItemMetadata
{
public:
    POSItemMetadata();

    const QString* getTableName() const
    {
        return &m_tablename;
    }

    const QSqlRecord* getMetadataRec() const
    {
        return &m_metadatarec;
    }

private:
    QString m_tablename;
    QSqlRecord m_metadatarec;
};

class POSItemDataInfo : public IPOSItemDataInfo
{
public:
    POSItemDataInfo(const QString itemcode,
                    const QString itemdesc)
        : m_itemcode(itemcode),
          m_itemdescr(itemdesc)
    {

    }

    virtual const QString* itemCode() const { return &m_itemcode; }
    virtual const QString* itemDescr() const { return &m_itemdescr; }

private:
    QString m_itemcode;
    QString m_itemdescr;
};


class POSItem : virtual private POSDataTable<POSItemMetadata>, virtual public IPOSItem
{
public:
    static void getBehaviours(QStringList* behaviours)
    {
        behaviours->append(BEH_DATATABLE);
    }

    virtual IPOSItemDataInfo_Ptr GetItemInfo(const QString* itemcode);
};

#endif // POSITEM_H
