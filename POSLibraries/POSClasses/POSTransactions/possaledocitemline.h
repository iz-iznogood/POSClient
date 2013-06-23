#ifndef POSSALEDOCITEMLINE_H
#define POSSALEDOCITEMLINE_H

#include "posdocitemline.h"

class POSSaleDocItemLine : virtual public POSDocItemLine, virtual public IPOSSaleDocItemLine
{
    Q_OBJECT

public:
    POSSaleDocItemLine();
};

#endif // POSSALEDOCITEMLINE_H
