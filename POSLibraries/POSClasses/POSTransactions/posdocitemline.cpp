#include "posdocitemline.h"

POSDocItemLine::POSDocItemLine() :
    POSTransaction(),
    IPOSDocItemLine(),
    m_itemcode(""),
    m_itemdescription(""),
    m_qty(0)
{
}
