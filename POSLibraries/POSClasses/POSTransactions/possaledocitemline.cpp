#include "possaledocitemline.h"

static Registrator<POSSaleDocItemLine> _register(POSSaleDocItemLine::_ClassID());

POSSaleDocItemLine::POSSaleDocItemLine() :
    POSDocItemLine(),
    IPOSSaleDocItemLine()
{
}
