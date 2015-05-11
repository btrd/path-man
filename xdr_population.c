#include "include.h"
bool_t xdr_population(XDR *xdrs, struct population_struct *p) {
  bool_t res = 1;
  if (xdr_int(xdrs, &p->size) == 0) {
    res = 0;
  }
  if (xdr_int(xdrs, &p->id) == 0) {
    res = 0;
  }
  
  //Force XDR to allocate memory while decoding
  if((xdrs->x_op == XDR_DECODE) && (p->tab != NULL)) {
    free(p->tab);
    p->tab = NULL;
  }

  uint usize = (p->size * 2);
  if (xdr_array(xdrs, (char **)&p->tab, &usize, (p->size * 2), sizeof(int), (xdrproc_t)xdr_int) == 0) {
    res = 0;
  }
  return res;
}
