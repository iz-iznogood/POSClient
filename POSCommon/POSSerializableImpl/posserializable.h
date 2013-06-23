#ifndef POSSERIALIZABLE_H
#define POSSERIALIZABLE_H

#include "classserializer.h"
#include "posserializableintf.h"
#include "poslibrary.h"

#include <QObject>
#include <QMetaObject>
#include <QMetaProperty>


class PosSerializable : virtual public QObject, virtual public IPOSSerializable
{

    Q_OBJECT

public:
    PosSerializable() :
        QObject(NULL),
        IPOSSerializable()
        { }
    virtual ~PosSerializable() { }

private:

    class FactoryHelper
    {
    public:
        static IPOSSerializable_Ptr CreateObject(const QString* classname)
        {
            return IPOSSerializable_Ptr(dynamic_cast<IPOSSerializable*>(_Globals->LibraryManager->CreateObject(*classname)));
        }
    };

    typedef BinaryWriter<IPOSSerializable_Ptr> POSBinaryWriter;
    typedef BinaryReader<IPOSSerializable_Ptr, PosSerializable::FactoryHelper> POSBinaryReader;

    virtual void Serialize()
    {
        PosSerializable::POSBinaryWriter writer(IPOSSerializable_Ptr(this));
        writer.WriteObject();
    }

    virtual void DeSerialize()
    {
        PropertyBag_Ptr bag(new PropertyBag);
        PosSerializable::POSBinaryReader reader(bag, IPOSSerializable_Ptr(this));
        reader.ReadObject();
    }

    virtual int PropertyCount() const
    {
        return metaObject()->propertyCount();
    }

    virtual const QString ClassName() const
    {
        return QString(metaObject()->className());
    }

    virtual const PropertyInformation PropertyInfo(int i) const
    {
        QMetaProperty prop = metaObject()->property(i);
        return PropertyInformation(prop.isReadable(), prop.isWritable(), prop.name());
    }

    virtual const QVariant PropertyValue(const QString propName) const
    {
        return property(propName.toStdString().c_str());
    }

    virtual void SetProperty(const QString propName, const QVariant propValue)
    {
        setProperty(propName.toStdString().c_str(), propValue);
    }
};

#endif // POSSERIALIZABLE_H
