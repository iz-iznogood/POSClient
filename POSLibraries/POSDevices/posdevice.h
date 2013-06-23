#ifndef POSDEVICE_H
#define POSDEVICE_H

#include "posdeviceintf.h"

class POSDevice : virtual public IPOSDevice
{
protected:
    virtual bool Active() const
    {
        return m_active;
    }

    virtual void setActive(bool value)
    {
        m_active = value;
    }

    virtual void Reset()
    {

    }

    virtual void Clear()
    {

    }

private:
    bool m_active;
};

class POSInputDevice : virtual public IPOSInputDevice, virtual public POSDevice
{
protected:
    virtual QByteArray readAll()
    {
        return NULL;
    }

    virtual QByteArray read(int)
    {
        return NULL;
    }
};


class POSOutputDevice : virtual public IPOSOutputDevice, virtual public POSDevice
{
protected:
    virtual int writeData(const QByteArray* )
    {
        return 0;
    }

    virtual int writeString(const QString* )
    {
        return 0;
    }
};

#endif // POSDEVICE_H
