#include "posdocument.h"

#include "posexception.h"

POSDocument::POSDocument() :
    POSTransaction(),
    IPOSDocument(),
    m_itemlines(new DocItemLines()),
    m_doctype(""),
    m_active(false)
{
}

IPOSDocItemLine_Ptr POSDocument::itemLine(const int i) const
{
    if (i >= 0 && i < m_itemlines->count())
        return m_itemlines->at(i);
    else
        throw POSException(esError, etBusiness, 1, QString("Item Lines Out of Range %s").
                           arg(QString::number(i)));
}

void POSDocument::addItemLine(const IPOSDocItemLine_Ptr itemline)
{
    m_itemlines->append(itemline);
}

void POSDocument::GetChildren(IPOSSerializables* list)
{
    for(DocItemLines::const_iterator it = m_itemlines->begin(); it != m_itemlines->end(); ++it)
        list->append(dynamic_cast<IPOSSerializable*>((*it).data()));
}

void POSDocument::AddChild(IPOSSerializable* child)
{
    IPOSDocItemLine_Ptr item(dynamic_cast<IPOSDocItemLine*>(child));
    if (item.isNull())
        m_itemlines->append(item);
    else
        throw POSException(esError, etBusiness, 1, "Attempt to add child to document which is not DocItemLine");
}

void POSDocument::Open()
{
    if (m_active)
        throw POSException(esError, etBusiness, 1, "Document is already open");

    m_active = true;
}
