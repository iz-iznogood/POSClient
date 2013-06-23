#ifndef POSTRANSACTION_H
#define POSTRANSACTION_H

#include <QUuid>
#include <QDateTime>

#include "postransactionintf.h"
#include "posserializable.h"

class POSTransaction : virtual public PosSerializable, virtual public IPOSTransaction
{

    Q_OBJECT

public:
    POSTransaction();

    static void getBehaviours(QStringList* ) { }

protected:
    virtual void Initialize();

    virtual const QUuid* UID() const;
    virtual const QDateTime* DocDateTime() const;

private:
    QUuid m_uid;
    QDateTime m_docdatetime;
};

#endif // POSTRANSACTION_H
