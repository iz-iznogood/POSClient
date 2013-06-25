#ifndef POSDOCITEMLINE_H
#define POSDOCITEMLINE_H

#include <QString>

#include "postransactionintf.h"
#include "postransaction.h"
#include "posexception.h"

class POSDocItemLine : virtual public POSTransaction, virtual public IPOSDocItemLine
{

    Q_OBJECT

public:
    POSDocItemLine();

protected:
    virtual void GetChildren(IPOSSerializables* )
    {

    }

    virtual void AddChild(IPOSSerializable* )
    {
        throw POSException(esError, etBusiness, 1, "DocItemLine does not support child records");
    }

    virtual const QString* itemCode() const
    {
        return &m_itemcode;
    }

    virtual const QString* itemDescription() const
    {
        return &m_itemdescription;
    }

    virtual float qty() const
    {
        return m_qty;
    }

private:
    QString m_itemcode;
    QString m_itemdescription;
    float m_qty;
};

#endif // POSDOCITEMLINE_H
