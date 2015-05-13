#ifndef VILLAGE_H
#define VILLAGE_H

#include <vector>
#include "Person.h"
#include "Map.h"
#include "Genome.h"

class Village
{
public:
	Village(int id, int population);
	~Village();

	Map* getMap();
	int iteration();
	Person* getPersonTest();
	vector<Person*> getPeople();
	//struct population_struct getPopulationStruct();
	void reproduce();
	void evaluate();
	void kill();
private:
	int id;
	int population;
	Map* map;
	std::vector<Person*> people;
	std::vector<std::pair<int, int> > ranking;

	bool pairCompare(const std::pair<int, int>& firstElem, const std::pair<int, int>& secondElem);
};

#endif