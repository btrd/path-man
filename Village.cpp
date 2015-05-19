#include "Village.h"
#include "population_struct.h"

int SIZE_GENOME = 200;
int SIZE_STEP = 2;
int MUTATION_CHANCE = 1;
int SIZE_N = 100;
int SIZE_M = 50;
int HARDNESS = 3;
int SEED = 12332;

Village::Village(int id, int population)
{
	this->id = id;
	this->population = population;
	//this->map = new Map();
	this->map = new Map(SIZE_N, SIZE_M, SEED, HARDNESS);

	for(int i=0;i<population;++i){
		Genome *g;
		if(i < 8)
			g = new Genome(SIZE_GENOME, SIZE_STEP, MUTATION_CHANCE, i);
		else
			g = new Genome(SIZE_GENOME, SIZE_STEP, MUTATION_CHANCE);

		Person *p = new Person(i, g, this->map->getStart());
		this->people.push_back(make_pair(p, 0));
	}
	this->reproduce();
}

Map* Village::getMap(){
	return this->map;
}

Person* Village::getPersonTest(){
	Person* p = this->people.at(0).first;
	//p->getGenome()->PrintGenome();
	return p;
}

std::vector<Person*> Village::getPeople(){
	std::vector<Person*> p;
	for(int i=0;i<this->population;++i){
		p.push_back(this->people.at(i).first);
	}
	return p;
}

int Village::iterate(){
	for(int i=0;i<this->population;++i){
		this->people.at(i).first->reset(this->map);
		for(int  j=0;j<SIZE_GENOME; ++j){
			this->people.at(i).first->move(this->map);
		}
	}

	return 1;
}

void Village::generate(){
	evaluate();
	kill();
	reproduce();
}

struct population_struct Village::getPopulationStruct() {
	struct population_struct res;
	res.id = this->id;
	res.size = 10;
 	res.tab = new adn_struct[res.size];
 	srand(time(NULL));
	for(int i = 0; i < res.size; i++) {
		int r = rand()%this->population-1;
		vector<Gene> adn = this->people.at(r).first->getGenome()->getAdn();
		res.tab[i].size = adn.size();
		res.tab[i].tab = new int[adn.size()*2];
		int k = -1;
		int size = adn.size();
		for(int j = 0; j < size; j++) {
			res.tab[i].tab[++k] = adn[j].direct;
			res.tab[i].tab[++k] = adn[j].steps;
		}

		this->people.erase(this->people.begin()+r);
		this->population--;
	}
	return res;
}

void Village::setPopulationStruct(struct population_struct pop){
	for(int i=0;i < pop.size; i++){
		Genome *g = new Genome(SIZE_GENOME, SIZE_STEP, MUTATION_CHANCE, pop.tab[i].tab);
		Person *p = new Person(this->population, g, this->map->getStart());
		this->people.push_back(make_pair(p,0));
		this->population++;
	}
}

void Village::reproduce(){
	int pop = this->population;
	srand(time(NULL));
	int pt1 = rand()%SIZE_GENOME;
	int pt2 = pt1+rand()%(SIZE_GENOME-pt1);
	//std::random_shuffle(this->people.begin(), this->people.end());
	//cout << this->people.at(0).first->getId() << "\n";
	Genome *g;
	for(int i=0;i<pop;i=i+2){
		if(i%4 == 0)
			g = Genome::ChildRandom(this->people.at(rand()%pop).first->getGenome(), this->people.at(rand()%pop).first->getGenome());
		else if(i%4 == 1)
			g = Genome::ChildCrossOverOnePoint(this->people.at(rand()%pop).first->getGenome(), this->people.at(rand()%pop).first->getGenome(), pt1);
		else if(i%4 == 2)
			g = Genome::ChildCrossOverTwoPoint(this->people.at(rand()%pop).first->getGenome(), this->people.at(rand()%pop).first->getGenome(), pt1, pt2);
		else
			g = Genome::ChildCrossOverhalf(this->people.at(rand()%pop).first->getGenome(), this->people.at(rand()%pop).first->getGenome());

		Person *p = new Person(this->population, g, this->map->getStart());
		this->people.push_back(make_pair(p,0));
		this->population++;
	}
}

void Village::evaluate(){
	int note = 0;
	Person *p;
	for(int i=0;i<this->population;++i){
		p = this->people.at(i).first;
		note = -p->getLocation()->distance(this->map->getEnd()) + (1000 * p->getArrived()) - (p->getGenomePosition() * p->getArrived());
		//p->reset(this->map); 
		this->people.at(i).second = note;
		//cout << note << "\n";
	}

	std::sort(this->people.begin(), this->people.end(), pairCompare);
}

void Village::kill(){
	int l= ceil(this->population/3);
	for(int i=0; i<l; ++i){
		this->people.pop_back();
		this->population--;
	}
}

static bool pairCompare(const std::pair<Person*, int>& firstElem, const std::pair<Person*, int>& secondElem){
  return firstElem.second > secondElem.second;
}

int Village::getBestNote(){
	return this->people.at(0).second;
}