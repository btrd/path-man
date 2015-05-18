#include "Village.h"
#include "population_struct.h"

int SIZE_GENOME = 300;
int SIZE_STEP = 3;
int MUTATION_CHANCE = 1;

Village::Village(int id, int population)
{
	this->id = id;
	this->population = population;
	this->map = new Map();

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
		for(int  j=0;j<SIZE_GENOME; ++j){
			this->people.at(i).first->move(this->map);
		}
	}
	cout << this->people.at(0).first->getGenomePosition() << "\n";

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
		for(int j = 0; j < adn.size(); j++) {
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
	int pt1 = rand()%100;
	int pt2 = pt1+rand()%(100-pt1);
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
		note = -(p->getLocation()->distance(this->map->getEnd()) + (1000 * p->getArrived()) - (p->getGenomePosition() * p->getArrived()));
		p->reset(this->map); 
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