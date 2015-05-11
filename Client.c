#include "include.h"

int main(int argc, char const *argv[]) {
  struct population_struct p;
  struct population_struct res;
  p.size = 5;
  p.id = 1;
  p.tab = (int *)malloc(sizeof(int)*p.size*2);
  for(int i = 0; i < p.size * 2; i++) {
    p.tab[i] = i;
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
  if (stat != RPC_SUCCESS) { 
    fprintf(stderr, "Echec de l'appel distant\n");
    clnt_perrno(stat);
    fprintf(stderr, "\n");
  } else {
    printf("Retour\n");
    for(int i = 0; i < res.size * 2; i++) {
      printf("%d\n", res.tab[i]);
    }
  }
}
