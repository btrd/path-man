#include "include.h"

int populations_size = 0;
struct population_struct *populations;

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
  printf("1\n");
  int adn_size = p->tab[0].size;
  static struct population_struct res;
  res.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct) * res.size);
  printf("RES_SIZE: %d\n", res.size);
  for(int i = 0; i < res.size; i++) {
    struct adn_struct *adn = &res.tab[i];
    adn->size = adn_size;
    printf("ADN_SIZE: %d\n", (adn->size * 2));
    adn->tab = (int *)malloc(sizeof(int) * adn->size * 2);
    for (int j = 0; j < adn->size * 2; j++) {
      adn->tab[j] = p->tab[i].tab[j];
    }
  }
  printf("2\n");

  res.id = p->id;
  res.size = p->size;
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
  printf("3\n");
  //Mélange last_population et p
  for (int i = 0; i < (p->size/2)-1; i++) {
    res.tab[i] = populations[current_i].tab[i];

  }
  printf("4\n");
  for (int i = (p->size/2)-1; i < p->size; i++) {
    res.tab[i] = populations[next_i].tab[i];
  }
  printf("5\n");
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
