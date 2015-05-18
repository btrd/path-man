#ifndef INCRPC
#define INCRPC  

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include "population_struct.h"
#define PROGNUM 0x20000101
#define VERSNUM 1
#define PROCNUM 1
bool_t xdr_population(XDR *, struct population_struct *);
#endif /* INCRPC */
