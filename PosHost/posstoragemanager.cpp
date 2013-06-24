#include "posstoragemanager.h"

#include <QDir>
#include <QApplication>

#include "posglobals.h"
#include "posexception.h"


const char* cDBDriverName = "QSQLITE";
const char* cDBFileName = "POSDB.db3";


POSStorageManager::POSStorageManager()
    : IPOSStorageManager(),
      m_db(QSqlDatabase::addDatabase(cDBDriverName)),
      m_datatables(new POSDataTables()),
      m_registeredtables_ptr(new QStringList())
{
    if (!m_db.isValid())
        QT_THROW(POSException(esError, etSystem, 1, "Database driver is Invalid"));

    QObject* other = dynamic_cast<QObject*>(Globals->LibraryManager.data());
    if (!QObject::connect(other, SIGNAL(classRegistered(const QString&, const QStringList&)),
                          this, SLOT(classRegistered(const QString&, const QStringList&))))
        QT_THROW(POSException(esError, etSystem, 1, "Unable to connect Storage Manager Signal"));
}

POSStorageManager::~POSStorageManager()
{

}

void POSStorageManager::Initialize()
{
    OpenDB();

    for(QStringList::const_iterator it = m_registeredtables_ptr->begin(); it != m_registeredtables_ptr->end(); ++it)
    {
        IPOSDataTable_Ptr table(dynamic_cast<IPOSDataTable*>(Globals->LibraryManager->CreateObject(*it)));
        if (table.isNull())
            QT_THROW(POSException(esError, etSystem, 1, "Unable to create database table " + *it));

        m_datatables->insert(*it, table);
    }

    QList<IPOSDataTable_Ptr> tables = m_datatables->values();
    if (!m_db.transaction())
        QT_THROW(POSException(esError, etSystem, 1, "Unable to begin transaction"));
    QT_TRY
    {
        for(QList<IPOSDataTable_Ptr>::const_iterator it = tables.begin(); it != tables.end(); ++it)
            (*it)->CheckSchema();
        m_db.commit();
    }
    QT_CATCH(...)
    {
        m_db.rollback();
        QT_RETHROW;
    }
}

void POSStorageManager::Finalize()
{
    m_datatables->clear();

    if (m_db.isOpen())
        m_db.close();
}

void POSStorageManager::OpenDB()
{
    QString filename = QApplication::applicationDirPath();
    filename.append(QDir::separator()).append(cDBFileName);
    filename = QDir::toNativeSeparators(filename);

    m_db.setDatabaseName(filename);

    if (!m_db.open())
        QT_THROW(POSException(esError, etSystem, 1, "Unable to open database"));
}

void POSStorageManager::RegisterTable(const QString& classname)
{
    m_registeredtables_ptr->append(classname);
}

void POSStorageManager::classRegistered(const QString& classname, const QStringList& behaviours)
{
    if (behaviours.contains(BEH_DATATABLE))
        RegisterTable(classname);
}
