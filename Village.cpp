#include "Village.h"
#include "population_struct.h"

Village::Village(int id, int population)
{
	this->id = id;
	this->population = population;
	this->map = new Map();

	for(int i=0;i<population;++i){
		Genome *g = new Genome(100, 2, 50);
		Person *p = new Person(i, g, this->map->getStart());
		this->people.push_back(p);
	}
}

Map* Village::getMap(){
	return this->map;
}

Person* Village::getPersonTest(){
	Person* p = this->people.at(0);
	p->getGenome()->PrintGenome();
	return p;
}

vector<Person*> Village::getPeople(){
	return this->people;
}

int Village::iteration(){
	for(int i=0;i<population;++i){
		this->people.at(i)->move(this->map);
	}

	return 1;
}

struct population_struct Village::getPopulationStruct() {
	struct population_struct res;
	res.id = this->id;
	res.size = this->population;
  res.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct) * res.size);
  for(int i = 0; i < res.size; i++) {
  	vector<Gene> adn = this->people[i]->getGenome()->getAdn();
    res.tab[i].size = adn.size();
    res.tab[i].tab = (int *)malloc(sizeof(int) * adn.size() * 2);
    int k = -1;
    for(int j = 0; j < adn.size(); j++) {
      res.tab[i].tab[k++] = adn[j].direct;
      res.tab[i].tab[k++] = adn[j].steps;
    }
  }
  return res;
}