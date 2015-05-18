#ifndef VILLAGE_H
#define VILLAGE_H

#include <vector>
#include <algorithm>
#include <math.h>
#include "Person.h"
#include "Map.h"
#include "population_struct.h"

static bool pairCompare(const std::pair<Person*, int>& firstElem, const std::pair<Person*, int>& secondElem);

class Village
{
public:
	Village(int id, int population);
	~Village();

	Map* getMap();
	int iterate();
	void generate();
	Person* getPersonTest();
	vector<Person*> getPeople();
	struct population_struct getPopulationStruct();
	void setPopulationStruct(struct population_struct pop);
	void reproduce();
	void evaluate();
	void kill();
	int getBestNote();
private:
	int id;
	int population;
	Map* map;
	std::vector<std::pair<Person*, int> > people;
};

#endif