#ifndef GENOME_H
#define GENOME_H

#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <vector>

/*
	Class handling the differents ADN and reproduction
	CAUTION: don't forget to initiate randomness with "srand(time(NULL));"
			 before using any of the reproduction fonction.
*/
using namespace std;

struct Gene
{
	int direct;
	int steps;
};

Gene mkGene(int direct, int steps);

class Genome
{
public:
	Genome();
	Genome(int size, int maxsteps, int mutationchance);
	Genome(int size, int maxsteps, int mutationchance, int direction); //Go in one direction only
	~Genome();

	int getSize();
	vector<Gene> getAdn();

	int ** toArrays();
	void Mutate(int nbgene);
	//For each gene, choose from father or mother randomly
	static Genome ChildRandom(Genome a, Genome b);
	//Take the first Gene until p1 is reach then take second Gene
	static Genome ChildCrossOverOnePoint(Genome a, Genome b, int p1); //TODO
	//Take the first Gene until p1 is reach then take second Gene until p2 then p1 again
	static Genome ChildCrossOverTwoPoint(Genome a, Genome b, int p1, int p2); //TODO
	//Take the first half of Gene a and second half of Gene b
	static Genome ChildCrossOverhalf(Genome a, Genome b); //TODO
	void PrintGenome();
private:
	//Return a Child of a and b with no adn
	static Genome CleanChild(Genome a, Genome b);
	int mutationchance; //chance of mutation of children in percent (0..100)
	int maxsteps; //max of steps a gene can do.
	int size;
	vector<Gene> adn; //(direction, steps)
};

#endif