#ifndef POSEXCEPTION_H
#define POSEXCEPTION_H

#include <exception>
#include <QString>

#include "posbasecls.h"
#include "logger.h"

class POSException : public std::exception
{
public:
    POSException(const ErrorSeverity severity, const ErrorType type,
                 unsigned short level, const QString message) throw()
        : std::exception(),
          m_severity(severity),
          m_type(type),
          m_level(level),
          m_message(message) { }

    virtual ~POSException() throw() { }

    inline virtual const char* what() const throw()
    {
        return m_message.toStdString().c_str();
    }

    inline ErrorSeverity Severity() const
    {
        return m_severity;
    }

    inline ErrorType Type() const
    {
        return m_type;
    }

    inline unsigned short Level() const
    {
        return m_level;
    }

private:
    ErrorSeverity m_severity;
    ErrorType m_type;
    unsigned short m_level;
    QString m_message;
};

#endif // POSEXCEPTION_H
