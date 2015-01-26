#ifndef __MEMORY_TEST__H__
#define __MEMORY_TEST__H__

#include <stdlib.h>

extern unsigned int speicherAlloc;
extern unsigned int speicherFree;

#define free(m)((speicherFree++,free(m)))
#define malloc(m)((speicherAlloc++,malloc(m)))

#endif
