#include "Person.h"

Person::Person(int id, Genome* genome, Point* location) : id(id), genome(genome), alive(true), location(location), iteration(0), arrived(false)
{}

int Person::move(Map* m){
	if(this->alive && !this->arrived){
		Gene g = genome->getAdn().at(iteration);
		location = m->change(location, g.direct, g.steps);

		int v = location->getValue();
		if(v == 1)
			this->alive = false;
		else if(v == 3)
			this->arrived = true;

		this->iteration++;
	}

	return this->iteration;
}

Genome* Person::getGenome(){
	return this->genome;
}

Point* Person::getLocation(){
	return this->location;
}

bool Person::getArrived(){
	return this->arrived;
}

int Person::getGenomePosition(){
	return this->iteration;
}

void Person::reset(Map* m){
	this->iteration=0;
	this->alive = true;
	this->arrived = false;
	this->location = m->getStart();
}

int Person::getId(){
	return this->id;
}

bool Person::getAlive(){
	return this->alive;
}