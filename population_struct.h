#ifndef POPULATION_STRUCT_H
#define POPULATION_STRUCT_H

struct population_struct {
  int size;
  struct adn_struct *tab;
  int id;
};

struct adn_struct {
  int size;
  int *tab;
};

#endif
