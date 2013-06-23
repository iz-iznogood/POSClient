#ifndef POSDOCUMENT_H
#define POSDOCUMENT_H

#include "postransactionintf.h"
#include "postransaction.h"
#include "posexception.h"


typedef QList<IPOSDocItemLine_Ptr> DocItemLines;
typedef QSharedPointer<DocItemLines> DocItemLines_Ptr;

class POSDocument : virtual public POSTransaction, virtual public IPOSDocument
{
    Q_OBJECT

public:
    POSDocument();

protected:
    virtual IPOSDocItemLine_Ptr itemLine(const int i) const;

    virtual void GetChildren(IPOSSerializables* list);
    virtual void AddChild(IPOSSerializable_Ptr child);

    virtual const QString* DocType() const
    {
        return &m_doctype;
    }

private:
    DocItemLines_Ptr m_itemlines;

    QString m_doctype;
};

#endif // POSDOCUMENT_H