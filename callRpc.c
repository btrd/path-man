#include "include.h"

struct population_struct call_rpc(struct population_struct p) {
  struct population_struct res;
  struct population_struct p;
  p.size = 2;
  p.id = atoi(argv[1]);
  p.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct)*p.size);
  for(int i = 0; i < p.size; i++) {
    p.tab[i].size = 4;
    p.tab[i].tab = (int *)malloc(sizeof(int)*p.tab[i].size*2);
    for(int j = 0; j < p.tab[i].size * 2; j++) {
      p.tab[i].tab[j] = j + p.id;
    }
  }

  for(int i = 0; i < p.size; i++) {
    struct adn_struct *adn = &p.tab[i];
    printf("Size %d\n", adn->size);
    for(int j = 0; j < adn->size * 2; j++) {
      printf("%d-", adn->tab[j]);
    }
    printf("\n");
  }

  int stat = callrpc(
    /* host */ "localhost",
    /* prognum */ PROGNUM,
    /* versnum */ VERSNUM,
    /* procnum */ PROCNUM,
    /* encodage argument */ (xdrproc_t)xdr_population,
    /* argument */ (char *)&p,
    /* decodage retour */ (xdrproc_t)xdr_population,
    /* retour de la fonction distante */(char *)&res
  );
  for(int i = 0; i < p.size; i++) {
    free(p.tab[i].tab);
  }
  free(p.tab);
  if (stat != RPC_SUCCESS) { 
    fprintf(stderr, "Echec de l'appel distant\n");
    clnt_perrno(stat);
    fprintf(stderr, "\n");
  } else {
    return res;
  }
}
