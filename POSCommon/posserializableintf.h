#ifndef POSSERIALIZABLEINTF_H
#define POSSERIALIZABLEINTF_H

#include "posbasecls.h"
#include "classserializer.h"

#include <QList>
#include <QSharedPointer>

class IPOSSerializable;

typedef QSharedPointer<IPOSSerializable> IPOSSerializable_Ptr;
typedef QList<IPOSSerializable_Ptr> IPOSSerializables;
typedef QSharedPointer<IPOSSerializables> IPOSSerializables_Ptr;

class IPOSSerializable : virtual public IPOSObject
{
public:
    virtual void Serialize() = 0;
    virtual void DeSerialize() = 0;

    virtual void GetChildren(IPOSSerializables* list) = 0;
    virtual void AddChild(IPOSSerializable_Ptr child) = 0;

    virtual int PropertyCount() const = 0;
    virtual const QString ClassName() const = 0;
    virtual const PropertyInformation PropertyInfo(int i) const = 0;
    virtual const QVariant PropertyValue(const QString propName) const = 0;
    virtual void SetProperty(const QString propName, const QVariant propValue) = 0;
};

#endif // POSSERIALIZABLEINTF_H
