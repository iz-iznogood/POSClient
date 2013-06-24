#ifndef POSSTORAGEMANAGER_H
#define POSSTORAGEMANAGER_H

#include <QMap>
#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include <QSqlDatabase>
#include <QObject>

#include "posstorageintf.h"

typedef QMap<QString, IPOSDataTable_Ptr> POSDataTables;
typedef QSharedPointer<POSDataTables> POSDataTables_Ptr;

class POSStorageManager : public QObject, public IPOSStorageManager
{
    Q_OBJECT
public:
    explicit POSStorageManager();
    ~POSStorageManager();

    void Initialize();
    void Finalize();

private slots:
    void classRegistered(const QString& classname, const QStringList& behaviours);

private:
    QSqlDatabase m_db;
    POSDataTables_Ptr m_datatables;
    QSharedPointer<QStringList> m_registeredtables_ptr;

    void OpenDB();
    void RegisterTable(const QString& classname);
};

#endif // POSSTORAGEMANAGER_H
