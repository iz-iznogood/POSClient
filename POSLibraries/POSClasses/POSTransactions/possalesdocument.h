#ifndef POSSALESDOCUMENT_H
#define POSSALESDOCUMENT_H

#include "posdocument.h"
#include <QUuid>
#include <QDateTime>

class POSSalesDocument : virtual public POSDocument, virtual public IPOSSalesDocument
{

    Q_OBJECT

    Q_PROPERTY(const QUuid* UID READ UID)
    Q_PROPERTY(const QDateTime* DocDateTime READ DocDateTime)

public:
    POSSalesDocument();

    virtual const QString ClassID() const
    {
        return _ClassID();
    }

    static const QString _ClassID()
    {
        return REG_POSTRANSACTION_SALESDOCUMENT;
    }

};

#endif // POSSALESDOCUMENT_H
