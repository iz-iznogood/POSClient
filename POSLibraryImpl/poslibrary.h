#ifndef POSLIBRARY_H
#define POSLIBRARY_H

#include <QObject>
#include <QtAlgorithms>
#include <QMap>
#include <QString>
#include <QStringList>
#include <QSharedPointer>
#include <QSharedMemory>
#include <QDebug>

#include "posbasecls.h"
#include "posintf.h"

template<typename T>
struct ClassFactory : public IFactory
{
public:
    IPOSObject* create() const { return new T(); }
    virtual void getBehaviours(QStringList* behaviours) { T::getBehaviours(behaviours); }
};

class POSLibrary : public IPOSLibrary
{
public:
    POSLibrary();
    virtual ~POSLibrary() { }

    virtual IPOSObject* CreateObject(const QString& classname)
    {
        return m_instantiator_ptr->CreateObject(classname);
    }

    virtual void GetClassList(LibraryClassesDataRec* const rec);

    template<typename T>
    void RegisterClass(const QString& classname)
    {
        m_instantiator_ptr->RegisterClass<T>(classname);
    }

    virtual void Initialize();
    virtual void Finalize();

private:
    class Instantiator
    {
    private:
        QMap<QString, IFactory*> m_map;

    public:
        ~Instantiator()
        {
            qDeleteAll(m_map.values());
        }

        template<typename T>
        void RegisterClass(const QString& classname)
        {
            m_map[classname] = new ClassFactory<T>();
        }

        IPOSObject* CreateObject(const QString& className)
        {
            if (m_map.contains(className))
                return m_map[className]->create();

            return NULL;
        }

        LibraryClassList GetRegisteredClasses() const
        {
            LibraryClassList list;
            for(int i = 0; i < m_map.keys().count(); ++i)
            {
                ClassRec rec;
                rec.classname = m_map.keys()[i];
                m_map[rec.classname]->getBehaviours(&(rec.Behaviours));
                list.append(rec);
            }
            return list;
        }
    };

    QSharedPointer<Instantiator> m_instantiator_ptr;
    QSharedMemory m_globalsmem;
};

extern POSGlobals* _Globals;

extern "C" IPOSLibrary* getLibrary();

template<class T>
struct Registrator
{
    Registrator(const QString& classname)
    {
        dynamic_cast<POSLibrary*>(getLibrary())->RegisterClass<T>(classname);
    }
};

#endif // POSLIBRARY_H
