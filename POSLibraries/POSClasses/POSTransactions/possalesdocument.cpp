#include "possalesdocument.h"

#include "poslibrary.h"

static Registrator<POSSalesDocument> _register(REG_POSTRANSACTION_SALESDOCUMENT);

POSSalesDocument::POSSalesDocument() :
    POSDocument(),
    IPOSSalesDocument()
{
}
