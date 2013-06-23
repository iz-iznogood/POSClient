#ifndef POSDATAINFOMANAGER_H
#define POSDATAINFOMANAGER_H

#include "posdatainfointf.h"

class POSDataInfoManager : public IPOSDataInfoManager
{
public:
    POSDataInfoManager();

    virtual void Initialize();
};

#endif // POSDATAINFOMANAGER_H
