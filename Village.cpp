#include "Village.h"

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