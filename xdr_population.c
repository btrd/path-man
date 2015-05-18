#include "include.h"

bool_t xdr_adn(XDR *xdrs, struct adn_struct *adn) {
  u_int usize;
  bool_t res = 1;
  if (xdr_int(xdrs, &adn->size) == 0) {
    res = 0;
  }

  /*Force XDR to allocate memory while decoding
  // if((xdrs->x_op == XDR_DECODE) && (adn->tab != NULL)) {
  //   printf("Free?1\n");
  //   free(adn->tab);
  //   adn->tab = NULL;
  // }*/
  usize = (adn->size * 2);
  if (xdr_array(xdrs, (char **)&adn->tab, &usize, (adn->size * 2), sizeof(int), (xdrproc_t)xdr_int) == 0) {
    res = 0;
  }
  return res;
}

bool_t xdr_population(XDR *xdrs, struct population_struct *p) {
  u_int usize;
  bool_t res = 1;
  if (xdr_int(xdrs, &p->size) == 0) {
    res = 0;
  }
  if (xdr_int(xdrs, &p->id) == 0) {
    res = 0;
  }
  
  /*Force XDR to allocate memory while decoding
  // if((xdrs->x_op == XDR_DECODE) && (p->tab != NULL)) {
  //   free(p->tab);
  //   p->tab = NULL;
  //   printf("xdr2bis\n");
  // }*/
  usize = p->size;
  if (xdr_array(xdrs, (char **)&p->tab, &usize, p->size, sizeof(struct adn_struct), (xdrproc_t)xdr_adn) == 0) {
    res = 0;
  }
  return res;
}
