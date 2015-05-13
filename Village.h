#ifndef VILLAGE_H
#define VILLAGE_H

#include <vector>
#include "Person.h"
#include "Map.h"

class Village
{
public:
	Village(int id, int population);
	~Village();

	Map* getMap();
	int iteration();
	Person* getPersonTest();
	vector<Person*> getPeople();
	struct population_struct getPopulationStruct();
private:
	int id;
	int population;
	Map* map;
	std::vector<Person*> people;
};

#endif