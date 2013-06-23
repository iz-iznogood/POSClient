#include "poslibrarymanager.h"

#include <QDir>
#include <QApplication>
#include <QStringList>
#include <QDataStream>
#include <QBuffer>
#include <QByteArray>

#include "posconst.h"
#include "posglobals.h"
#include "posexception.h"

POSLibraryManager::POSLibraryManager()
    : IPOSLibraryManager(),
      m_poslibraries_ptr(new POSLibList()),
      m_classmap_ptr(new QMap<QString, POSLibraryProxy*>())
{
}

POSLibraryManager::~POSLibraryManager()
{
    m_poslibraries_ptr->FinalizeLibraries();
    m_poslibraries_ptr->UnLoadLibraries();
}

void POSLibraryManager::LoadLibraries()
{
    m_poslibraries_ptr->LoadLibraries();
    m_poslibraries_ptr->RegisterClasses(this, m_classmap_ptr.data());

    m_poslibraries_ptr->InitializeLibraries();
}

IPOSObject* POSLibraryManager::CreateObject(const QString& classname)
{
    if (m_classmap_ptr->contains(classname))
        return (*m_classmap_ptr)[classname]->CreateObject(classname);
    else
        return NULL;
}

POSLibraryManager::POSLibList::POSLibList()
{

    QString path = QApplication::applicationDirPath() + "/" + LibDir;
    QDir dir(path, LibFilter, QDir::SortFlags(QDir::Name | QDir::IgnoreCase), QDir::Files);

    QStringList list = dir.entryList();

    for (int i = 0; i < list.count(); ++i)
        append(new POSLibraryProxy(path + '/' + list[i]));
}

void POSLibraryManager::POSLibList::RemoveLibrary(const QString& libname)
{
    for(int i = 0; i < count(); ++i)
    {
        POSLibraryProxy* lib = at(i);
        if (lib->getLibName() == libname)
        {
            removeAt(i);
            delete lib;
            break;
        }
    }
}

void POSLibraryManager::POSLibList::LoadLibraries()
{
    QStringList badlibraries;

    for(const_iterator it = begin(); it != end(); ++it)
    {
        QT_TRY
        {
            (*it)->Load();
        }
        QT_CATCH(...)
        {
            QString libname = (*it)->getLibName();
            badlibraries.append(libname);
            Globals->ErrorManager->LogWarning(etSystem, 1, "Loading Library " + libname + " failed.");
        }
    }

    for (int i = 0; i < badlibraries.count(); ++i)
        RemoveLibrary(badlibraries[i]);
}

void POSLibraryManager::POSLibList::UnLoadLibraries()
{
    for(const_iterator it = begin(); it != end(); ++it)
        (*it)->UnLoad();
}

void POSLibraryManager::POSLibList::InitializeLibraries()
{
    for(const_iterator it = begin(); it != end(); ++it)
        (*it)->InitializeLibrary();
}

void POSLibraryManager::POSLibList::FinalizeLibraries()
{
    for(const_iterator it = begin(); it != end(); ++it)
        (*it)->FinalizeLibrary();
}

void POSLibraryManager::POSLibList::RegisterClasses(POSLibraryManager* manager, ClassMap* map)
{
    for(const_iterator it = begin(); it != end(); ++it)
        (*it)->RegisterClasses(manager, map);
}


POSLibraryManager::POSLibraryProxy::POSLibraryProxy(const QString& libname) :
    m_libname(libname)
{
    m_lib.setFileName(m_libname);
    m_lib.setLoadHints(QLibrary::ExportExternalSymbolsHint);
}

POSLibraryManager::POSLibraryProxy::~POSLibraryProxy()
{
    UnLoad();
}

bool POSLibraryManager::POSLibraryProxy::Load()
{
    if (m_lib.isLoaded())
        return true;
    else
    {
        bool res = m_lib.load();
        if (!res)
            QT_THROW(POSException(esError, etSystem, 1, "Unable to load library" + m_lib.fileName()));

        getLibraryProc proc = (getLibraryProc)(m_lib.resolve("getLibrary"));
        if (proc != NULL)
            library = proc();
        return res;
    }
}

bool POSLibraryManager::POSLibraryProxy::UnLoad()
{
    if (!m_lib.isLoaded())
        return true;
    else
    {
        library = NULL;
        return m_lib.unload();
    }
}

QString POSLibraryManager::POSLibraryProxy::getLibName() const
{
    return m_libname;
}

IPOSObject* POSLibraryManager::POSLibraryProxy::CreateObject(const QString& classname)
{
    return library->CreateObject(classname);
}

void POSLibraryManager::POSLibraryProxy::RegisterClasses(POSLibraryManager* manager, ClassMap* map)
{
    LibraryClassesDataRec classdata;

    library->GetClassList(&classdata);

    QByteArray array(classdata.data, classdata.size);
    delete classdata.data; // no longer needed since QByteArray does a deep copy
    QBuffer buf(&array);
    buf.open(QIODevice::ReadOnly);

    QDataStream stream(&buf);

    LibraryClassList classlist;
    stream >> classlist;

    for(LibraryClassList::const_iterator it = classlist.begin(); it != classlist.end(); ++it)
    {
        map->insert((*it).classname, this);

        emit manager->classRegistered((*it).classname, (*it).Behaviours);
    }
}

void POSLibraryManager::POSLibraryProxy::InitializeLibrary()
{
    library->Initialize();
}

void POSLibraryManager::POSLibraryProxy::FinalizeLibrary()
{
    library->Finalize();
}
