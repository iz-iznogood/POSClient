#include "poserrormanager.h"
#include "posexception.h"

#include <QApplication>
#include <QDir>
#include "logger.h"

POSErrorManager::POSErrorManager()
    : IPOSErrorManager(),
      m_logger(new Logger())
{
    QString filename = QApplication::applicationDirPath();
    filename.append(QDir::separator()).append("Logs");
    filename = QDir::toNativeSeparators(filename);

    m_logger->setLogDir(filename);
}

void POSErrorManager::HandleException(std::exception* exception)
{
    POSException* posexception = dynamic_cast<POSException*>(exception);
    if (posexception != NULL)
        m_logger->LogMessage(posexception->Severity(), posexception->Type(), posexception->Level(), posexception->what());
    else
        m_logger->LogError(etSystem, 1, exception->what());
}

void POSErrorManager::LogError(const ErrorType type, const quint16 level, const QString& message)
{
    m_logger->LogError(type, level, message);
}

void POSErrorManager::LogWarning(const ErrorType type, const quint16 level, const QString& message)
{
    m_logger->LogWarning(type, level, message);
}

void POSErrorManager::LogInfo(const ErrorType type, const quint16 level, const QString& message)
{
    m_logger->LogWarning(type, level, message);
}
