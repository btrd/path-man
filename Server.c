#include "include.h"

int populations_size = 0;
struct population_struct populations[100];
int init = 0;

// Never shuffle the same village
int replacePopInPops(struct population_struct *p) {
  int res = -1;
  for (int i = 0; i < populations_size; ++i) {
    if (p->id == populations[i].id) {
      res = i;
      populations[i] = *p;
    }
  }
  if (res == -1) {
    populations[populations_size] = *p;
    res = populations_size;
    populations_size++;
  }
  return res;
}

struct population_struct * shuffle(struct population_struct *p) {
  static struct population_struct res;
  res.tab = (int *)malloc(sizeof(int)*p->size*2);
  for(int i = 0; i < p->size * 2; i++) {
    res.tab[i] = i+10;
  }
  res.id = p->id;
  res.size = p->size;
  int current_i = replacePopInPops(p);
  if(init == 0) {
    init = 1;
    return p;
  }
  int next_i;
  if (current_i < populations_size-1) {
    next_i = current_i + 1;
  } else {
    next_i = 0;
  }
  //Mélange last_population et p
  for (int i = 0; i < (p->size/2)-1; i++) {
    res.tab[i] = p->tab[i];
    i++;
    res.tab[i] = p->tab[i];
  }
  for (int i = (p->size/2)-1; i < p->size; i++) {
    res.tab[i] = populations[next_i].tab[i];
    i++;
    res.tab[i] = populations[next_i].tab[i];
  }
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
