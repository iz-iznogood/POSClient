#ifndef POSSALESDOCUMENT_H
#define POSSALESDOCUMENT_H

#include "posdocument.h"
#include <QUuid>
#include <QDateTime>

class POSSalesDocument : virtual public POSDocument, virtual public IPOSSalesDocument
{

    Q_OBJECT

    Q_PROPERTY(const QUuid* UID READ UID)
    Q_PROPERTY(const QDateTime* DocDateTime READ DocDateTime)

public:
    POSSalesDocument();
};

#endif // POSSALESDOCUMENT_H
