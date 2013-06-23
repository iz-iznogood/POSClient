#ifndef POSSQLITESCHEMAUPDATER_H
#define POSSQLITESCHEMAUPDATER_H

#include <QString>
#include <QSqlRecord>

class POSSqliteSchemaUpdater
{
public:
    POSSqliteSchemaUpdater(const QString* tablename, const QSqlRecord* metadatarec);

    void UpdateSchema();

private:
    const QString* m_tablename;
    const QSqlRecord* m_metadatarec;

    QString GetFieldList(bool withtypes, const QSqlRecord* const rec);
    bool CheckFieldProps(const QSqlField* fmeta, const QSqlField* fdb);

    void DropTable(const QString tablename);
    void RenameTable(const QString from, const QString to);
    void GetDBMetadata(QSqlRecord* const dbrec);
    bool CalculateSchemaDiffs(QSqlRecord* const dbrec);
};

#endif // POSSQLITESCHEMAUPDATER_H
