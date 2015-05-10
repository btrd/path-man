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
	for (i = 0; i < size; i++)
	{
		for(j = 0; j < adn.at(i).steps ;j++)
			cout << adn.at(i).direct;
		cout << endl;
	}
	cout << "----------" << endl;
}

void Genome::Mutate(int nbgene)
{
	int i=0, j = 0;
	while (j < nbgene)
	{
		if(i == size)
			i = 0;
		if (rand()%100 <= mutationchance)
		{
			if (rand() % 2)
				adn.at(i).steps = (rand() % maxsteps) +1;
			else
				adn.at(i).direct = (rand() % 8);
			j++;
		}
		i++;
	}

}

Genome Genome::ChildRandom(Genome a, Genome b)
{
	int i;
	Genome res = CleanChild(a,b);
	for (i=0; i<a.size; i++)
	{
		if (rand() % 2)
			res.adn.push_back(a.adn.at(i));
		else
			res.adn.push_back(b.adn.at(i));
	}
	if (rand() < res.mutationchance) //Mutation on creation
		res.Mutate(5);
	return res;
}

Genome Genome::CleanChild(Genome a, Genome b)
{
	int newmaxsteps = (a.maxsteps + b.maxsteps)/2;
	int newprobamutation = (a.mutationchance + b.mutationchance)/2;
	Genome res = Genome(a.size, newmaxsteps, newprobamutation);
	res.adn.clear();
	return res;
}

Genome Genome::ChildCrossOverOnePoint(Genome a, Genome b, int p1)
{
	int i;
	Genome res = CleanChild(a,b);
	for (i=0; i<a.size; i++)
	{
		if (i < p1)
			res.adn.push_back(a.adn.at(i));
		else
			res.adn.push_back(b.adn.at(i));
	}
	if (rand() < res.mutationchance) //Mutation on creation
		res.Mutate(5);
	return res;
}

Genome Genome::ChildCrossOverTwoPoint(Genome a, Genome b, int p1, int p2)
{
	int i;
	Genome res = CleanChild(a,b);
	for (i=0; i<a.size; i++)
	{
		if (i < p1 || i > p2)
			res.adn.push_back(a.adn.at(i));
		else
			res.adn.push_back(b.adn.at(i));
	}
	if (rand() < res.mutationchance) //Mutation on creation
		res.Mutate(5);
	return res;
}

Genome Genome::ChildCrossOverhalf(Genome a, Genome b)
{
	return Genome::ChildCrossOverOnePoint(a,b, a.size/2);
}

//For test purpose
// int main()
// {
// 	srand(time(NULL));
// 	int SIZE = 10;
// 	int MAXSTEPS = 5;
// 	Genome g1 = Genome(SIZE,MAXSTEPS, 20);
// 	Genome g2 = Genome(SIZE,MAXSTEPS, 10);
// 	g1.PrintGenome();
// 	g2.PrintGenome();
// 	Genome g3 = Genome::ChildCrossOverhalf(g1, g2);
// 	g3.PrintGenome();
// }