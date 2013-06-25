#ifndef POSSALEDOCITEMLINE_H
#define POSSALEDOCITEMLINE_H

#include "posdocitemline.h"

class POSSaleDocItemLine : virtual public POSDocItemLine, virtual public IPOSSaleDocItemLine
{
    Q_OBJECT

public:
    POSSaleDocItemLine();

    virtual const QString ClassID() const
    {
        return _ClassID();
    }

    static const QString _ClassID()
    {
        return REG_POSTRANSACTION_SALESDOCITEMLINE;
    }
};

#endif // POSSALEDOCITEMLINE_H
