#ifndef POSLIBRARYMANAGER_H
#define POSLIBRARYMANAGER_H

#include <QFileInfoList>
#include <QLibrary>
#include <QtAlgorithms>
#include <QList>
#include <QString>
#include <QMap>
#include <QSharedPointer>
#include <QObject>

#include "posbasecls.h"
#include "posintf.h"

class POSLibraryManager : public QObject, public IPOSLibraryManager
{
    Q_OBJECT
public:
    explicit POSLibraryManager();
    ~POSLibraryManager();

    void LoadLibraries();

    IPOSObject* CreateObject(const QString& classname);

signals:
    void classRegistered(const QString& classname, const QStringList& behaviours);

private:
    class POSLibraryProxy;
    typedef QMap<QString, POSLibraryProxy*> ClassMap;

    class POSLibraryProxy
    {
    public:
        explicit POSLibraryProxy(const QString& libname);
        ~POSLibraryProxy();

        bool Load();
        bool UnLoad();

        QString getLibName() const;

        IPOSObject* CreateObject(const QString& classname);
        void RegisterClasses(POSLibraryManager* manager, ClassMap* map);

        void InitializeLibrary();
        void FinalizeLibrary();

    private:
        QString m_libname;

        QLibrary m_lib;

        IPOSLibrary* library;
    };

    class POSLibList : private QList<POSLibraryProxy*>
    {
    public:
        explicit POSLibList();
        ~POSLibList() { qDeleteAll(this->begin(), this->end()); }

        void RemoveLibrary(const QString& libname);

        void LoadLibraries();
        void UnLoadLibraries();
        void RegisterClasses(POSLibraryManager* manager, ClassMap* map);

        void InitializeLibraries();
        void FinalizeLibraries();
    };

    QSharedPointer<POSLibList> m_poslibraries_ptr;
    QSharedPointer< QMap<QString, POSLibraryProxy*> > m_classmap_ptr;
};

#endif // POSLIBRARYMANAGER_H
