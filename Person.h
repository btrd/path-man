#ifndef PERSON_H
#define PERSON_H

#include "Genome.h"
#include "Point.h"
#include "Map.h"

class Person
{
public:
	Person(int id, Genome* genome, Point* location);
	~Person();

	int move(Map* m);
	Genome* getGenome();
	Point* getLocation();
	bool getArrived();
	bool getAlive();
	int getGenomePosition();
	void reset(Map* m);
	int getId();
	int getIteration();

private:
	int id;
	Genome* genome;
	bool alive;
	Point* location;
	int iteration;
	bool arrived;
};

#endif