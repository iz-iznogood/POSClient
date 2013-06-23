#include "poslibrary.h"
#include <QBuffer>
#include <QByteArray>
#include <QDataStream>

#include "posconst.h"
#include "posexception.h"

IPOSLibrary* getLibrary()
{
    static POSLibrary _library;

    return &_library;
}

POSGlobals* _Globals = NULL;


POSLibrary::POSLibrary()
    : IPOSLibrary(),
      m_instantiator_ptr(new Instantiator()),
      m_globalsmem(GlobalsKey)
{

}

void POSLibrary::GetClassList(LibraryClassesDataRec* const rec)
{
    QBuffer buf;
    buf.open(QIODevice::WriteOnly);

    QDataStream stream(&buf);

    LibraryClassList list = m_instantiator_ptr->GetRegisteredClasses();
    stream << list;

    rec->size = buf.size();
    rec->data = new char[rec->size];
    memcpy(rec->data, buf.buffer().constData(), rec->size);
}

void POSLibrary::Initialize()
{
    if (!m_globalsmem.attach(QSharedMemory::ReadOnly))
        QT_THROW(POSException(esError, etSystem, 1, "Can not attach to shared memory"));

    _Globals = (POSGlobals*)m_globalsmem.constData();
}

void POSLibrary::Finalize()
{
    if (m_globalsmem.isAttached() && !m_globalsmem.detach())
        _Globals->ErrorManager->LogWarning(etSystem, 1, "Unable to detach from shared memory");

    _Globals = NULL;
}
