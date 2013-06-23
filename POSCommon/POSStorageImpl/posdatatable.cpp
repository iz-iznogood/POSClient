#include "posdatatable.h"

#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>

#include "posexception.h"
#include "possqliteschemaupdater.h"

template<typename T_Metadata>
void POSDataTable<T_Metadata>::CheckSchema()
{
    POSSqliteSchemaUpdater updater(Metadata()->getTableName(), Metadata()->getMetadataRec());

    updater.UpdateSchema();
}

template<typename T_Metadata>
quint32 POSDataTable<T_Metadata>::recCount()
{
    QSqlQuery query("SELECT COUNT(*) FROM" + *(Metadata()->getTableName()));

    QSqlError error = query.lastError();
    if (error.isValid())
        QT_THROW(POSException(esError, etSystem, 1, error.text()));

    return query.record().field(0).value().toULongLong();
}
