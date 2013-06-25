#ifndef CLASSSERIALIZER_H
#define CLASSSERIALIZER_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <QSharedPointer>
#include <QVariantList>

typedef QMap<QString, QVariant> PropertyBag;
typedef QSharedPointer<PropertyBag> PropertyBag_Ptr;

const QString _classid = "_CLASSID";
const QString _children = "_CHILDREN";

class PropertyInformation
{
public:
    PropertyInformation(bool isreadable, bool iswritable, QString name) :
        m_isReadable(isreadable),
        m_isWritable(iswritable),
        m_name(name)
    { }

    bool isReadable() const { return m_isReadable; }
    bool isWritable() const { return m_isWritable; }
    const QString Name() const { return m_name; }
private:
    bool m_isReadable;
    bool m_isWritable;
    QString m_name;
};

template<typename T_Serializable_Ptr>
class BinaryWriter
{
public:
    explicit BinaryWriter(const T_Serializable_Ptr obj) :
        m_root(obj),
        m_bag(new PropertyBag())
    { }

    BinaryWriter(const T_Serializable_Ptr obj, PropertyBag_Ptr bag) :
        m_root(obj),
        m_bag(bag)
    { }

    void WriteObject()
    {
        if (m_root->PropertyCount() != 0)
        {
            (*m_bag)[_classid] = m_root->ClassID();
            for (int i = 0; i < m_root->PropertyCount(); ++i)
            {
                PropertyInformation prop = m_root->PropertyInfo(i);
                if (prop.isReadable())
                    (*m_bag)[prop.Name()] = m_root->PropertyValue(prop.Name());
            }
        }

        WriteChildren();
    }

    const PropertyBag_Ptr Bag() const { return m_bag; }

private:
    typedef QList<T_Serializable_Ptr> Serializable_List;

    void WriteChildren()
    {
        QScopedPointer<QVariantList> list(new QVariantList());
        Serializable_List children;

        m_root->GetChildren(&children);
        for(int i = 0; i < children.count(); ++i)
        {
            T_Serializable_Ptr child = children[i];
            BinaryWriter<T_Serializable_Ptr> writer(child);
            writer.WriteObject();
            if (!writer.Bag()->isEmpty())
                list->append(QVariant(*(writer.Bag())));
        }
        if (!list->isEmpty())
            (*m_bag)[_children] = QVariant(*list);
    }

    T_Serializable_Ptr m_root;
    PropertyBag_Ptr m_bag;
};

template<typename T_Serializable_Ptr, typename T_Factory>
class BinaryReader
{
public:
    explicit BinaryReader(PropertyBag_Ptr bag) :
        m_bag(bag),
        m_root(NULL)
    { }

    BinaryReader(PropertyBag_Ptr bag, T_Serializable_Ptr obj) :
        m_bag(bag),
        m_root(obj)
    { }

    void ReadObject()
    {
        if (!m_bag->contains(_classid))
            throw "Invalid ClassID";
        QString classid = (*m_bag)[_classid].toString();
        if (classid.isEmpty() || classid.isNull())
            throw "Invalid ClassID";

        if (m_root == NULL)
            m_root = CreateObject(&classid);
        else if (m_root->ClassID() != classid)
            throw "Root Object Has Different ClassID from Stream Object";

        if (m_root->PropertyCount() != 0)
        {
            for (int i = 0; i < m_root->PropertyCount(); ++i)
            {
                PropertyInformation prop = m_root->PropertyInfo(i);
                if (prop.isWritable() && m_bag->contains(prop.Name()))
                    m_root->SetProperty(prop.Name(), (*m_bag)[prop.Name()]);
            }
        }

        ReadChildren();
    }

    const T_Serializable_Ptr Object() const { return m_root; }

private:
    T_Serializable_Ptr CreateObject(const QString* classid)
    {
        return T_Factory::CreateObject(classid);
    }

    void ReadChildren()
    {
        if (!m_bag->contains(_children))
            return;

        QScopedPointer<QVariantList> list(new QVariantList((*m_bag)[_children].toList()));
        if (!list->isEmpty())
        {
            for(QVariantList::const_iterator it = list->begin(); it != list->end(); ++it)
            {
                PropertyBag_Ptr childprops(new PropertyBag(it->toMap()));
                BinaryReader<T_Serializable_Ptr, T_Factory> reader(childprops);
                reader.ReadObject();
                m_root->AddChild(reader.Object());
            }
        }
    }

    PropertyBag_Ptr m_bag;
    T_Serializable_Ptr m_root;
};

#endif // CLASSSERIALIZER_H
