#ifndef POSERRORMANAGER_H
#define POSERRORMANAGER_H

#include "posbasecls.h"
#include "posintf.h"
#include "posexception.h"
#include "logger.h"

#include <exception>

class POSErrorManager : public IPOSErrorManager
{
public:
    POSErrorManager();

    virtual void HandleException(std::exception* exception);

    virtual void LogError(const ErrorType type, const quint16 level, const QString& message);
    virtual void LogWarning(const ErrorType type, const quint16 level, const QString& message);
    virtual void LogInfo(const ErrorType type, const quint16 level, const QString& message);

private:
    Logger_Ptr m_logger;
};

#endif // POSERRORMANAGER_H
