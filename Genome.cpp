#include "Genome.h"

using namespace std;

Gene mkGene(int direct, int steps)
{
	Gene res;
	res.direct = direct;
	res.steps = steps;
	return res;
}

Genome::Genome(int size, int maxsteps, int mutationchance)
{
	int i, direct, steps;
	this->maxsteps = maxsteps;
	this->size = size;
	this->mutationchance = mutationchance;
	for (i = 0 ; i < size; i++)
	{
		direct = rand() % 8;
		steps = (rand() % this->maxsteps) + 1;
		adn.push_back(mkGene(direct, steps));
	}
}

Genome::~Genome() {}

int Genome::getSize()
{
	return this->size;
}

void Genome::PrintGenome()
{
	cout << "----------" << endl << "Genome de taille " << this->size << ":" << endl;
	int i, j;
	for (i = 0; i < this->size; i++)
	{
		for(j = 0; j < adn.at(i).steps ;j++)
			cout << adn.at(i).direct;
		cout << endl;
	}
	cout << "----------" << endl;
}

//For test purpose
int main()
{
	int SIZE = 10;
	int MAXSTEPS = 5;
	Genome g = Genome(SIZE,MAXSTEPS, 20);
	g.PrintGenome();
}