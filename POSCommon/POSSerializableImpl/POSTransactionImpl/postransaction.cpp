#include "postransaction.h"

#include <QUuid>

POSTransaction::POSTransaction()
{
}

void POSTransaction::Initialize()
{
    m_uid = QUuid::createUuid();
    m_docdatetime = QDateTime::currentDateTime();
}

const QUuid* POSTransaction::UID() const
{
    return &m_uid;
}

const QDateTime* POSTransaction::DocDateTime() const
{
    return &m_docdatetime;
}
