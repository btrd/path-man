#include "include.h"

int populations_size = 0;
struct population_struct *populations;
int adn_size = 0;
// Never shuffle the same village
int replacePopInPops(struct population_struct *p) {
  int res = -1;
  for (int g = 0; g < populations_size; g++) {
    if (p->id == populations[g].id) {
      res = g;
      populations[g].size = p->size;
      for (int k = 0; k < p->size; k++) {
        populations[g].tab[k].size = adn_size;
        for (int j = 0; j < adn_size * 2; j++) {
          populations[g].tab[k].tab[j] =  p->tab[k].tab[j];
        }
      }
    }
  }
  if (res == -1) {
    populations[populations_size].size = p->size;
    populations[populations_size].id = p->id;
    populations[populations_size].tab = (struct adn_struct *)malloc(sizeof(struct adn_struct)*p->size);
    for (int k = 0; k < p->size; k++) {
      populations[populations_size].tab[k].tab = (int *)malloc(sizeof(int)*adn_size*2);
      for (int j = 0; j < adn_size * 2; j++) {
        populations[populations_size].tab[k].tab[j] =  p->tab[k].tab[j];
      }
    }
    res = populations_size;
    populations_size++;
  }
  return res;
}

struct population_struct * shuffle(struct population_struct *p) {
  adn_size = p->tab[0].size;
  static struct population_struct res;
  res.id = p->id;
  res.size = p->size;
  res.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct) * res.size);
  for(int i = 0; i < res.size; i++) {
    res.tab[i].size = adn_size;
    res.tab[i].tab = (int *)malloc(sizeof(int) * adn_size * 2);
  }

  int current_i = replacePopInPops(p);
  if(populations_size <= 1) {
    return p;
  }
  int next_i;
  if (current_i == populations_size-1) {
    next_i = 0;
  } else {
    next_i = current_i + 1;
  }

  for (int i = 0; i < p->size/2; i++) {
    for (int j = 0; j < adn_size * 2; j++) {
      res.tab[i].tab[j] = populations[current_i].tab[i].tab[j];
    }
  }

  for (int i = p->size/2; i < p->size; i++) {
    for (int j = 0; j < adn_size * 2; j++) {
      res.tab[i].tab[j] = populations[next_i].tab[i].tab[j];
    }
  }
  
  return &res;
}

int main (void) {
  // 100 client/id au maximum
  populations = (struct population_struct *)malloc(sizeof(struct population_struct)*100);
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
