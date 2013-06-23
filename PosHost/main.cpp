#include "posapplication.h"
#include "posmainform.h"

int main(int argc, char *argv[])
{
    POSApplication a(argc, argv);

    POSMainForm mainform;
    mainform.show();

    return a.exec();
}

