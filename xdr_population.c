#include "include.h"

bool_t xdr_adn(XDR *xdrs, struct adn_struct *adn) {
  printf("xdr5\n");
  bool_t res = 1;
  if (xdr_int(xdrs, &adn->size) == 0) {
    res = 0;
  }

  //Force XDR to allocate memory while decoding
  if((xdrs->x_op == XDR_DECODE) && (adn->tab != NULL)) {
    printf("Free?1\n");
    free(adn->tab);
    adn->tab = NULL;
    printf("Free?2\n");
  }
  printf("xdr6\n");
  printf("%d\n", adn->size);
  uint usize = (adn->size * 2);
  printf("xdr7\n");
  if (xdr_array(xdrs, (char **)&adn->tab, &usize, (adn->size * 2), sizeof(int), (xdrproc_t)xdr_int) == 0) {
    res = 0;
  }
  printf("xdr8\n");
  return res;
}

bool_t xdr_population(XDR *xdrs, struct population_struct *p) {
  printf("xdr1\n");
  bool_t res = 1;
  if (xdr_int(xdrs, &p->size) == 0) {
    res = 0;
  }
  if (xdr_int(xdrs, &p->id) == 0) {
    res = 0;
  }
  printf("xdr2\n");
  
  //Force XDR to allocate memory while decoding
  if((xdrs->x_op == XDR_DECODE) && (p->tab != NULL)) {
    free(p->tab);
    p->tab = NULL;
    printf("xdr2bis\n");
  }
  printf("xdr3\n");
  uint usize = p->size;
  if (xdr_array(xdrs, (char **)&p->tab, &usize, p->size, sizeof(struct adn_struct), (xdrproc_t)xdr_adn) == 0) {
    res = 0;
  }
  return res;
}
