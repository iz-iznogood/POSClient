#ifndef POSBASESCANNER_H
#define POSBASESCANNER_H

#include "posdeviceintf.h"
#include "posdevice.h"

class POSBaseScanner : virtual public IPOSInputDevice, virtual public POSInputDevice
{
public:
    POSBaseScanner();
};

#endif // POSBASESCANNER_H
