#include "possalesdocument.h"

#include "poslibrary.h"

static Registrator<POSSalesDocument> _register(POSSalesDocument::_ClassID());

POSSalesDocument::POSSalesDocument() :
    POSDocument(),
    IPOSSalesDocument()
{
}
