#include "include.h"

struct population_struct call_rpc(struct population_struct p) {
  int stat;
  struct population_struct res;
  /*struct population_struct pop;
  pop.size = 2;
  pop.id = 1;
  pop.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct)*pop.size);
  for(i = 0; i < pop.size; i++) {
    pop.tab[i].size = 4;
    pop.tab[i].tab = (int *)malloc(sizeof(int)*pop.tab[i].size*2);
    for(j = 0; j < pop.tab[i].size * 2; j++) {
      pop.tab[i].tab[j] = j + pop.id;
    }
  }*/

  /*for(int i = 0; i < p.size; i++) {
    struct adn_struct *adn = &p.tab[i];
    printf("Size %d\n", adn->size);
    for(int j = 0; j < adn->size * 2; j++) {
      printf("%d-", adn->tab[j]);
    }
    printf("\n");
  }*/
  stat = callrpc(
    /* host */ "localhost",
    /* prognum */ PROGNUM,
    /* versnum */ VERSNUM,
    /* procnum */ PROCNUM,
    /* encodage argument */ (xdrproc_t)xdr_population,
    /* argument */ (char *)&p,
    /* decodage retour */ (xdrproc_t)xdr_population,
    /* retour de la fonction distante */(char *)&res
  );
  if (stat != RPC_SUCCESS) { 
    fprintf(stderr, "Echec de l'appel distant\n");
    clnt_perrno(stat);
    fprintf(stderr, "\n");
  }
  printf("Client id res %d\n", res.id);
  return res;
}
