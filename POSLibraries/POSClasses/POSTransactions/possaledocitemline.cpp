#include "possaledocitemline.h"

static Registrator<POSSaleDocItemLine> _register(REG_POSTRANSACTION_SALESDOCITEMLINE);

POSSaleDocItemLine::POSSaleDocItemLine() :
    POSDocItemLine(),
    IPOSSaleDocItemLine()
{
}
