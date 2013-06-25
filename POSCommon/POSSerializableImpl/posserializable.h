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
        static IPOSSerializable* CreateObject(const QString* classname)
        {
            return dynamic_cast<IPOSSerializable*>(_Globals->LibraryManager->CreateObject(*classname));
        }
    };

    typedef BinaryWriter<IPOSSerializable*> POSBinaryWriter;
    typedef BinaryReader<IPOSSerializable*, PosSerializable::FactoryHelper> POSBinaryReader;

    virtual void Serialize(PropertyBag_Ptr bag)
    {
        POSBinaryWriter writer(this, bag);
        writer.WriteObject();
    }

    virtual void Deserialize(PropertyBag_Ptr bag)
    {
        POSBinaryReader reader(bag, this);
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
