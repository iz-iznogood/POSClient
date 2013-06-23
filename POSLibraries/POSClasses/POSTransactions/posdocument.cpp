#include "posdocument.h"

POSDocument::POSDocument() :
    m_itemlines(new DocItemLines())
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

void POSDocument::GetChildren(IPOSSerializables* list)
{
    for(DocItemLines::const_iterator it = m_itemlines->begin(); it != m_itemlines->end(); ++it)
        list->append((*it).dynamicCast<IPOSSerializable>());
}

void POSDocument::AddChild(IPOSSerializable_Ptr child)
{
    IPOSDocItemLine_Ptr item = child.dynamicCast<IPOSDocItemLine>();
    if (item.isNull())
        m_itemlines->append(item);
    else
        throw POSException(esError, etBusiness, 1, "Attempt to add child to document which is not DocItemLine");
}
