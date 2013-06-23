#ifndef POSBASECLS_H
#define POSBASECLS_H

#include <QStringList>

class IPOSObject
{
public:
    virtual ~IPOSObject() { }
};

class IFactory
{
public:
    virtual ~IFactory() { }
    virtual IPOSObject* create() const = 0;
    virtual void getBehaviours(QStringList* behaviours) = 0;
};

#endif // POSBASECLS_H
