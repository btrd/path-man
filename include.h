#ifndef INCRPC
#define INCRPC  

#include <rpc/types.h>
#include <rpc/xdr.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define PROGNUM 0x20000100
#define VERSNUM 1
#define PROCNUM 1
bool_t xdr_village(XDR *, Village *);

struct population {
  int size;
  int **tab;
  int id;
};

#endif /* INCRPC */
