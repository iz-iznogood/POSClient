#ifndef POSTRANSACTIONINTF_H
#define POSTRANSACTIONINTF_H

#include <QSharedPointer>
#include <QUuid>
#include <QDateTime>
#include <QString>

#include "posbasecls.h"
#include "posserializableintf.h"

const char* const REG_POSTRANSACTION_SALESDOCUMENT = "POS.TRANSACTION.SALESDOCUMENT";
const char* const REG_POSTRANSACTION_SALESDOCITEMLINE = "POS.TRANSACTION.SALESDOCITEMLINE";


class IPOSTransaction : virtual public IPOSObject
{
public:
    virtual void Initialize() = 0;

    virtual const QUuid* UID() const = 0;
    virtual const QDateTime* DocDateTime() const = 0;
};

class IPOSDocItemLine : virtual public IPOSTransaction
{
public:
    virtual const QString* itemCode() const = 0;
    virtual const QString* itemDescription() const = 0;
    virtual float qty() const = 0;
};

typedef QSharedPointer<IPOSDocItemLine> IPOSDocItemLine_Ptr;

class IPOSDocument : virtual public IPOSTransaction
{
public:
    virtual IPOSDocItemLine_Ptr itemLine(const int i) const = 0;

    virtual const QString* DocType() const = 0;
};

class IPOSSalesDocument : virtual public IPOSDocument
{
public:
};

class IPOSSaleDocItemLine : virtual public IPOSDocItemLine
{
public:
};

typedef QSharedPointer<IPOSDocument> IPOSDocument_Ptr;

#endif // POSTRANSACTIONINTF_H
