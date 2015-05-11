#ifndef VILLAGE_H
#define VILLAGE_H

#include <vector>

class Population
{
public:
  Population();
  ~Population();
private:
  int id;
  Map* map;
  std::vector<Person*> people;
};

#endif