#include "Village.h"
#include "population_struct.h"

Village::Village(int id, int population)
{
	this->id = id;
	this->population = population;
	this->map = new Map();

	for(int i=0;i<population;++i){
		Genome *g = new Genome(100, 2, 50);
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
	p->getGenome()->PrintGenome();
	return p;
}

std::vector<Person*> Village::getPeople(){
	std::vector<Person*> p;
	for(int i=0;i<this->population;++i){
		p.push_back(this->people.at(i).first);
	}
	return p;
}

int Village::iteration(){
	for(int i=0;i<population;++i){
		this->people.at(i).first->move(this->map);
	}

	return 1;
}

struct population_struct Village::getPopulationStruct() {
	struct population_struct res;
	res.id = this->id;
	res.size = this->population;
  res.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct) * res.size);
  for(int i = 0; i < res.size; i++) {
  	vector<Gene> adn = this->people.at(i).first->getGenome()->getAdn();
    res.tab[i].size = adn.size();
    res.tab[i].tab = (int *)malloc(sizeof(int) * adn.size() * 2);
    int k = -1;
    for(int j = 0; j < adn.size(); j++) {
      res.tab[i].tab[k++] = adn[j].direct;
      res.tab[i].tab[k++] = adn[j].steps;
    }
  }
  return res;
}

void Village::reproduce(){
	int pop = this->population;
	srand(time(NULL));
	int pt1 = rand()%100;
	int pt2 = pt1+rand()%(100-pt1);
	Genome *g;
	for(int i=0;i<pop;i=i+2){
		// if(this->id%4 == 0)
		// 	g = Genome::ChildRandom(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome());
		// else if(this->id%4 == 1)
		// 	g = Genome::ChildCrossOverOnePoint(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome(), pt1);
		// else if(this->id%4 == 2)
		// 	g = Genome::ChildCrossOverTwoPoint(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome(), pt1, pt2);
		// else
		// 	g = Genome::ChildCrossOverhalf(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome());
		g = new Genome(100, 2, 50);

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
		note = (p->getLocation()->distance(this->map->getStart()) + (1000 * p->getArrived()) - (p->getGenomePosition() * p->getArrived()));
		p->reset(this->map); 
		this->people.at(i).second = note;
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