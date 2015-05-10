#ifndef GENOME_H
#define GENOME_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

using namespace std;

enum direction
{
	NORTH, NORTH_EAST, EAST, SOUTH_EAST,
	SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

struct Gene
{
	int direct;
	int steps;
};

Gene mkGene(int direct, int steps);

class Genome
{
public:
	Genome(int size, int maxsteps, int mutationchance);
	~Genome();

	int getSize();

	void Mutate(int nbgene); //TODO
	//For each gene, choose from father or mother randomly
	Genome ChildRandom(Genome a, Genome b); //TODO
	//Take the first Gene until p1 is reach then take second Gene
	Genome ChildCrossOverOnePoint(Genome a, Genome b, int p1); //TODO
	//Take the first Gene until p1 is reach then take second Gene until p2 then p1 again
	Genome ChildCrossOverTwoPoint(Genome a, Genome b, int p1, int p2); //TODO
	//Take the first half of Gene a and second half of Gene b
	Genome ChildCrossOverhalf(Genome a, Genome b); //TODO

	void PrintGenome();
private:
	int mutationchance; //chance of mutation of children in percent (0..100)
	int maxsteps; //max of steps a gene can do.
	int size;
	vector<Gene> adn; //(direction, steps)
};

#endif