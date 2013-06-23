#ifndef POSCONST_H
#define POSCONST_H

#include<QtCore/QtGlobal>

const char * const LibDir = "Libraries";
#if defined(Q_OS_WIN)
const char * const LibFilter = "POS*.dll";
#else
const char * const LibFilter = "libPOS*.so";
#endif

const char * const GlobalsKey = "POSGLOBALS";

#endif // POSCONST_H
