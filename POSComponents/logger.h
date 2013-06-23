#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QString>
#include <QSharedPointer>
#include <QMutex>
#include <QList>
#include <QDateTime>

enum ErrorSeverity {esError, esWarning, esInfo};
enum ErrorType {etSystem, etBusiness, etOther};

class Logger : public QObject
{
    Q_OBJECT
public:
    explicit Logger(QObject *parent = 0);
    ~Logger();
    
    void LogError(const ErrorType type, const quint16 level, const QString& message);
    void LogWarning(const ErrorType type, const quint16 level, const QString& message);
    void LogInfo(const ErrorType type, const quint16 level, const QString& message);
    void LogMessage(const ErrorSeverity severity, const ErrorType type, const quint16 level, const QString& message);

    void Flush();

    void setFlushAt(const quint32 value);
    quint32 FlushAt() const;
    void setLogDir(const QString& value);
    QString LogDir() const;

signals:
    
public slots:

private:
    struct ErrorRec
    {
        ErrorSeverity m_severity;
        ErrorType m_type;
        quint16 m_level;
        QString m_message;
        QDateTime m_time;

        ErrorRec(const ErrorSeverity severity, const ErrorType type, const unsigned short level, const QString& message);

        QString message() const;
    };

    typedef QSharedPointer<ErrorRec> ErrorRec_Ptr;
    typedef QList<ErrorRec_Ptr> ErrorList;

    QSharedPointer<ErrorList> m_list;
    QMutex m_lock;

    quint32 m_flushat;
    QString m_logdir;

    void AddMessage(const ErrorSeverity severity, const ErrorType type, const quint16 level, const QString& message);
    void CheckFlushLog();
};

typedef QSharedPointer<Logger> Logger_Ptr;

#endif // LOGGER_H
