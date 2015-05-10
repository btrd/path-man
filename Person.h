#ifndef PERSON_H
#define PERSON_H

#include "Genome.h"
#include "Point.h"

class Person
{
public:
	Person(int id, Genome* genome, Point* location);
	~Person();

private:
	int id;
	Genome* genome;
	bool state;
	Point* location;
};

#endif