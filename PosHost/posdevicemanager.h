#ifndef POSDEVICEMANAGER_H
#define POSDEVICEMANAGER_H

#include <posdeviceintf.h>

class POSDeviceManager : public IPOSDeviceManager
{
public:
    POSDeviceManager();

private:
    virtual void Initialize();
    virtual void Finalize();

    virtual IPOSDevice_Ptr Device(DeviceType type)
    {
        return m_device[type];
    }

    IPOSDevice_Ptr m_device[dtDeviceCount];
};

#endif // POSDEVICEMANAGER_H
