#ifndef POSAPPLICATION_H
#define POSAPPLICATION_H

#include <QApplication>

#include "posintf.h"

class POSApplication : public QApplication
{
    Q_OBJECT
public:
    explicit POSApplication(int &argc, char **argv);
    ~POSApplication();

    virtual bool notify(QObject * receiver, QEvent * event);

signals:
    
public slots:
    
};

#endif // POSAPPLICATION_H
