#include "positem.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QVariant>

#include "poslibrary.h"
#include "posexception.h"

static Registrator<POSItem> _register(REG_POSSTORAGE_ITEM);

const char* const cItemTable = "ITEM";

POSItemMetadata::POSItemMetadata()
    : m_tablename(cItemTable)
{
    QSqlField field("ITEMCODE", QVariant::String);
    field.setLength(20);
    m_metadatarec.append(field);

    QSqlField field1("ITEMDESCRIPTION", QVariant::String);
    field1.setLength(50);
    m_metadatarec.append(field1);

    QSqlField field2("ACTIVE", QVariant::Int);
    field2.setLength(50);
    field2.setDefaultValue(0);
    m_metadatarec.append(field2);
}

IPOSItemDataInfo_Ptr POSItem::GetItemInfo(const QString* itemcode)
{
    QSqlQuery query;

    query.prepare("SELECT * FROM " + *(Metadata()->getTableName()) + " WHERE ITEMCODE=:ITEMCODE");
    query.bindValue("ITEMCODE", QVariant(*itemcode));

    query.exec();
    QSqlError error = query.lastError();
    if (error.isValid())
        throw POSException(esError, etSystem, 1, QString("Get Item Method failed for Item %1").arg(*itemcode));

    QSqlRecord rec = query.record();
    if (rec.isEmpty())
        throw POSException(esError, etBusiness, 1, QString("Item not found for code %1").arg(*itemcode));

    return IPOSItemDataInfo_Ptr(new POSItemDataInfo(rec.field("ITEMCODE").value().toString(),
                                                    rec.field("ITEMDESCRIPTION").value().toString()));
}
