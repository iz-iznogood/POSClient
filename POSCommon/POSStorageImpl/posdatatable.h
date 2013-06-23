#ifndef POSDATATABLE_H
#define POSDATATABLE_H

#include "posstorageintf.h"

#include <QString>
#include <QSqlRecord>

template <typename T_Metadata>
class POSDataTable : virtual public IPOSDataTable
{
protected:
    T_Metadata* Metadata() { return &m_metadata; }

    virtual void CheckSchema();

    virtual bool isEmpty() { return recCount() == 0; }
    virtual quint32 recCount();

private:
    T_Metadata m_metadata;
};

#include "posdatatable.cpp"

#endif // POSDATATABLE_H
