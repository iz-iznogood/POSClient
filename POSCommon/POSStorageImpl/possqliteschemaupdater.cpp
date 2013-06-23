#include "possqliteschemaupdater.h"

#include <QSqlQuery>
#include <QSqlField>
#include <QSqlError>
#include <QStringList>

#include "posexception.h"
#include "poslibrary.h"

POSSqliteSchemaUpdater::POSSqliteSchemaUpdater(const QString* tablename, const QSqlRecord* metadatarec)
    : m_tablename(tablename),
      m_metadatarec(metadatarec)
{
}

bool POSSqliteSchemaUpdater::CheckFieldProps(const QSqlField* fmeta, const QSqlField* fdb)
{
    return (
            ((fmeta->length() != fdb->length()) && (fdb->length() != -1)) ||
            (fmeta->name() != fdb->name()) ||
            ((fmeta->requiredStatus() != fdb->requiredStatus()) && (fdb->requiredStatus() != QSqlField::Unknown)) ||
            (fmeta->type() != fdb->type())
           );
}

QString POSSqliteSchemaUpdater::GetFieldList(bool withtypes, const QSqlRecord* const rec)
{
    QStringList fields;

    QString fieldvalue;
    QString defvalue;

    for(qint32 i = 0; i < rec->count(); ++i)
    {
        QSqlField field = rec->field(i);
        fieldvalue.clear();
        defvalue.clear();

        if (withtypes)
        {
            if (field.defaultValue().isValid() && !field.defaultValue().isNull())
                defvalue = QString("DEFAULT '%1'").arg(field.defaultValue().toString());

            switch (field.type())
            {
                case QVariant::Int:
                    fieldvalue = QString("%1 %2 %3").
                            arg(field.name(), "INTEGER", defvalue);
                    break;
                case QVariant::String:
                    fieldvalue = QString("%1 %2 %3").
                            arg(field.name(), QString("VARCHAR(%1)").arg(field.length()), defvalue);
                    break;
                default:
                QT_THROW("invalid field type value");
            }
        }
        else
            fieldvalue = field.name();

        fields.append(fieldvalue);
    }

    QString res;
    for (QStringList::const_iterator it = fields.begin(); it != fields.end(); ++it)
        if (res.isEmpty())
            res = *it;
        else
            res.append(',').append(*it);

    return res;
}

void POSSqliteSchemaUpdater::DropTable(const QString tablename)
{
    const char* cDropTableSQL = "DROP TABLE IF EXISTS %1";

    _Globals->ErrorManager->LogInfo(etSystem, 1, QString("Dropping Table %1").arg(tablename));
    QSqlQuery query;
    query.exec(QString(cDropTableSQL).arg(tablename));
    QSqlError error = query.lastError();
    if (error.isValid())
        QT_THROW(POSException(esError, etSystem, 1,
                            QString("Error Dropping Table %1 Error: %2").arg(tablename, error.text())));
    else
        _Globals->ErrorManager->LogInfo(etSystem, 1, QString("Table Dropped %1").arg(tablename));
}

void POSSqliteSchemaUpdater::RenameTable(const QString from, const QString to)
{
    const char* cAlterTableSQL = "ALTER TABLE %1 RENAME TO %2";

    _Globals->ErrorManager->LogInfo(etSystem, 1, QString("Rename Table %1 to %2").arg(from, to));
    QSqlQuery query;
    query.exec(QString(cAlterTableSQL).arg(from, to));
    QSqlError error = query.lastError();
    if (error.isValid())
        QT_THROW(POSException(esError, etSystem, 1,
                            QString("Error Renaming Table %1 Error: %2").arg(from, error.text())));
    else
        _Globals->ErrorManager->LogInfo(etSystem, 1, QString("Table Renamed to %1").arg(to));
}


void POSSqliteSchemaUpdater::GetDBMetadata(QSqlRecord* const dbrec)
{
    const char* cMetaSQL = "SELECT * FROM %1 WHERE 1 = 0";

    dbrec->clear();

    QSqlQuery query(QString(cMetaSQL).arg(*m_tablename));
    QSqlError error = query.lastError();
    if (error.isValid())
        return;

    QSqlRecord rec = query.record();
    for(qint32 i = 0; i < rec.count(); ++i)
        dbrec->append(rec.field(i));
}

bool POSSqliteSchemaUpdater::CalculateSchemaDiffs(QSqlRecord* const dbrec)
{
    GetDBMetadata(dbrec);

    if (dbrec->isEmpty())
        return  true;

    for(qint32 i = 0; i < m_metadatarec->count(); ++i)
    {
        QSqlField metafield = m_metadatarec->field(i);
        if (!dbrec->contains(metafield.name()))
            return true;
        else
        {
            QSqlField recfield = dbrec->field(metafield.name());
            if (CheckFieldProps(&metafield, &recfield))
                return true;
        }
    }

    return false;
}

void POSSqliteSchemaUpdater::UpdateSchema()
{
    const char* cCreateTableSQL = "CREATE TABLE %1 (%2)";
    const char* cCopyDataSQL = "INSERT INTO %1 (%2) SELECT %2 FROM TMP_%1";
    const char* cCreateVersionIndexSQL = "CREATE INDEX VERSION_IDX ON %1 (VERSION)";

    QSqlRecord dbrec;

    if (CalculateSchemaDiffs(&dbrec))
    {
        QString newfields(GetFieldList(true, m_metadatarec));
        QString dbfields(GetFieldList(false, &dbrec));

        QT_TRY
        {
            RenameTable(*m_tablename, QString("TMP_%1").arg(*m_tablename));
        }
        QT_CATCH(POSException& e)
        {
            _Globals->ErrorManager->LogError(e.Type(), e.Level(), e.what());
        }

        QSqlQuery query;
        query.exec(QString(cCreateTableSQL).arg(*m_tablename, newfields));
        QSqlError error = query.lastError();
        if (error.isValid())
            QT_THROW(POSException(esError, etSystem, 1,
                                QString("Create Table %1 failed.Error: %2").
                                arg(*m_tablename, error.text())));

        if (dbrec.count() != 0)
        {
            query.exec(QString(cCopyDataSQL).arg(*m_tablename, dbfields));
            QSqlError error = query.lastError();
            if (error.isValid())
                QT_THROW(POSException(esError, etSystem, 1,
                                    QString("Copy Data Failed. Error: %1").arg(error.text())));
        }

        if (dbrec.contains("VERSION"))
        {
            query.exec(QString(cCreateVersionIndexSQL).arg(*m_tablename));
            QSqlError error = query.lastError();
            if (error.isValid())
                QT_THROW(POSException(esError, etSystem, 1,
                                    QString("Create Version Index on %1 failed.Error: %2").
                                    arg(*m_tablename, error.text())));
        }

        DropTable(QString("TMP_%1").arg(*m_tablename));
    }
}
