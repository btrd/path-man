#ifndef VILLAGE_H
#define VILLAGE_H

#include <vector>
#include <algorithm>
#include <math.h>
#include "Person.h"
#include "Map.h"
#include "adn_exchange.grpc.pb.h"

using pathman::VillageP;
using pathman::PersonP;
using pathman::GeneP;

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
  VillageP getVillageP(int num);
  void setVillageP(VillageP vil);
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