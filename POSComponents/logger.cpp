#include "logger.h"
#include <QMutexLocker>
#include <QFile>
#include <QDir>
#include <QString>
#include <QDate>
#include <QTextStream>

Logger::Logger(QObject *parent) :
    QObject(parent),
    m_list(new ErrorList()), m_lock(QMutex::Recursive),
    m_flushat(100), m_logdir("")
{
}

Logger::~Logger()
{
    Flush();
}

void Logger::LogError(const ErrorType type, const quint16 level, const QString& message)
{
    AddMessage(esError, type, level, message);
}

void Logger::LogWarning(const ErrorType type, const quint16 level, const QString& message)
{
    AddMessage(esWarning, type, level, message);
}

void Logger::LogInfo(const ErrorType type, const quint16 level, const QString& message)
{
    AddMessage(esInfo, type, level, message);
}

void Logger::LogMessage(const ErrorSeverity severity, const ErrorType type, const quint16 level, const QString& message)
{
    AddMessage(severity, type, level, message);
}

void Logger::AddMessage(const ErrorSeverity severity, const ErrorType type, const quint16 level, const QString& message)
{
    QMutexLocker locker(&m_lock);

    m_list->append(ErrorRec_Ptr(new ErrorRec(severity, type, level, message)));
    CheckFlushLog();
}

Logger::ErrorRec::ErrorRec(const ErrorSeverity severity, const ErrorType type, const quint16 level, const QString& message)
    : m_severity(severity), m_type(type), m_level(level),
      m_message(message), m_time(QDateTime::currentDateTime())
{

}

QString Logger::ErrorRec::message() const
{
    QString s_date =  m_time.toString("dd/MM/yyyy hh:mm:ss:zzz");

    QString s_severity;
    switch (m_severity)
    {
        case esError:
            s_severity = "Error Level ";
            break;
        case esWarning:
            s_severity = "Warning Level ";
            break;
        case esInfo:
            s_severity = "Info Level ";
            break;
    }

    s_severity.append(QString::number(m_level));

    return s_date.leftJustified(25, ' ') +
           s_severity.leftJustified(18, ' ') +
           m_message;
}

void Logger::Flush()
{
    QMutexLocker locker(&m_lock);

    QDir dir(QDir::cleanPath(LogDir()));

    if (!dir.exists() && !dir.mkpath(dir.absolutePath()))
        return;

    QFile file(dir.absolutePath() + '/' + QDate::currentDate().toString("ddMMyyyy") + ".log");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Append))
        return;

    QTextStream stream(&file);
    for(ErrorList::const_iterator it = m_list->begin(); it != m_list->end(); ++it)
        stream << (*it)->message() << "\r\n";

    m_list->clear();
}

void Logger::setFlushAt(const quint32 value)
{
    m_flushat = value;
}

quint32 Logger::FlushAt() const
{
    return m_flushat;
}

void Logger::setLogDir(const QString& value)
{
    m_logdir = value;
}

QString Logger::LogDir() const
{
    return m_logdir;
}

void Logger::CheckFlushLog()
{
    if ( (m_flushat > 0) && (m_list->count() >= (int)m_flushat) )
        Flush();
}
