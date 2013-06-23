#ifndef POSDEVICEINTF_H
#define POSDEVICEINTF_H

#include <QByteArray>
#include <QSharedPointer>

#include "posbasecls.h"

enum DeviceType {dtBarcodeReader,
                 dtKeyboard,
                 dtPrinter,
                 dtDeviceCount};

class IPOSDevice : virtual public IPOSObject
{
public:
    virtual bool Active() const = 0;
    virtual void setActive(bool value) = 0;

    virtual void Reset() = 0;
    virtual void Clear() = 0;
};

typedef QSharedPointer<IPOSDevice> IPOSDevice_Ptr;

class IPOSInputDevice : virtual public IPOSDevice
{
public:
    virtual QByteArray readAll() = 0;
    virtual QByteArray read(int count) = 0;
};

class IPOSOutputDevice : virtual public IPOSDevice
{
public:
    virtual int writeData(const QByteArray* data) = 0;
    virtual int writeString(const QString* s) = 0;
};

class IPOSDeviceManager : public IPOSObject
{
public:
    virtual void Initialize() = 0;
    virtual void Finalize() = 0;

    virtual IPOSDevice_Ptr Device(DeviceType type) = 0;
};

typedef QSharedPointer<IPOSDeviceManager> IPOSDeviceManager_Ptr;

#endif // POSDEVICEINTF_H
