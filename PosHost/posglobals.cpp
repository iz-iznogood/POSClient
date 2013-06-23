#include "posglobals.h"

#include <QSharedMemory>
#include <stdio.h>
#include <QDebug>

#include "posconst.h"
#include "poserrormanager.h"
#include "poslibrarymanager.h"
#include "posstoragemanager.h"
#include "posexception.h"
#include "posdatainfomanager.h"
#include "posdevicemanager.h"

static QSharedMemory* globalsmem = NULL;

POSGlobals* Globals = NULL;

void InitializeGlobals()
{
    IPOSErrorManager_Ptr tmp_errormanager = IPOSErrorManager_Ptr(new POSErrorManager());

    globalsmem = new QSharedMemory(GlobalsKey);

    if (!globalsmem->create(sizeof(POSGlobals)))
    {
        tmp_errormanager->LogInfo(etSystem, 1,
                                  QString("Unable to create shared memory area. Error: %1 ").
                                  arg(globalsmem->errorString()));
        if (!globalsmem->attach())
        {
            tmp_errormanager->LogInfo(etSystem, 1,
                                      QString("Unable to attach to shared memory area. Error: %1 ").
                                      arg(globalsmem->errorString()));
            QT_THROW(POSException(esError, etSystem, 1, "Unable to initialize global memory. Application Terminated"));
        }
    }

    memset(globalsmem->data(), 0, globalsmem->size());

    Globals = new(globalsmem->data()) POSGlobals();

    Globals->ErrorManager = tmp_errormanager;
    QT_TRY
    {
        Globals->LibraryManager = IPOSLibraryManager_Ptr(new POSLibraryManager());
        Globals->StorageManager = IPOSStorageManager_Ptr(new POSStorageManager());
        Globals->DataInfoManager = IPOSDataInfoManager_Ptr(new POSDataInfoManager());
        Globals->DeviceManager = IPOSDeviceManager_Ptr(new POSDeviceManager());

        Globals->LibraryManager->LoadLibraries();
        Globals->StorageManager->Initialize();
        Globals->DataInfoManager->Initialize();
        Globals->DeviceManager->Initialize();

        Globals->Document = IPOSDocument_Ptr(dynamic_cast<IPOSDocument*>(Globals->LibraryManager->CreateObject(REG_POSTRANSACTION_SALESDOCUMENT)));
    }
    QT_CATCH(std::exception &exception)
    {
        Globals->ErrorManager->LogError(etSystem, 1,
                                        QString("POS Initialization Error : ").arg(exception.what()));
        QT_RETHROW;
    }
}

void FinalizeGlobals()
{
    // order might be important

    Globals->DeviceManager->Finalize();
    Globals->StorageManager->Finalize();

    Globals->DeviceManager.clear();
    Globals->DataInfoManager.clear();
    Globals->StorageManager.clear();
    Globals->LibraryManager.clear();
    Globals->ErrorManager.clear();

    // the object is allocated with placement new so dont free it,
    //just call the destructor for proper clean up
    Globals->~POSGlobals();

    delete globalsmem;
}
