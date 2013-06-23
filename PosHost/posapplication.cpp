#include "posapplication.h"

#include <exception>

#include "posglobals.h"

POSApplication::POSApplication(int &argc, char **argv) :
    QApplication(argc, argv)

{
    InitializeGlobals();
}

POSApplication::~POSApplication()
{
    FinalizeGlobals();
}

bool POSApplication::notify(QObject * receiver, QEvent * event)
{
    QT_TRY
    {
        return QApplication::notify(receiver, event);
    }
    QT_CATCH(std::exception& e)
    {
        Globals->ErrorManager->HandleException(&e);
        return false;
    }
}
