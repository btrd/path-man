#include "include.h"

// Never shuffle the same village
// static int positionPopInPops(population *p) {
//   int res = -1;
//   for (int i = 0; i < populations.size(); ++i) {
//     if (v->getId() == populations.at(i).getId()) {
//       res = i;
//     }
//   }
//   return res;
// }

population last_population = void;
population * shuffle(population *p) {
  static population res = *p;
  if(last_population == void) {
    return *p;
  }
  //Mélange last_population et p
  for (int i = 0; i < p->s/2; i++) {
    res[i] = last_population[i];
  }
  for (int i = p->s/2; i < p->s; i++) {
    res[i] = p[i];
  }
  last_population = *p;
  return &res;
}

int main (void) {
  bool_t stat;
  stat = registerrpc(
    /* prognum */ PROGNUM,
    /* versnum */ VERSNUM,
    /* procnum */ PROCNUM,
    /* pointeur sur fonction */ shuffle,
    /* decodage arguments */ (xdrproc_t)xdr_population,
    /* encodage retour de fonction */ (xdrproc_t)xdr_population
  );
  if (stat != 0) {
    fprintf(stderr,"Echec de l'enregistrement\n");
    exit(1);
  }
  svc_run(); /* le serveur est en attente de clients eventuels */
  return(0); /* on y passe jamais ! */
}
