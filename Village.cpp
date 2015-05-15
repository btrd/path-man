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
		this->people.push_back(p);
	}

	//this->reproduce();
}

Map* Village::getMap(){
	return this->map;
}

Person* Village::getPersonTest(){
	Person* p = this->people.at(0);
	p->getGenome()->PrintGenome();
	return p;
}

vector<Person*> Village::getPeople(){
	return this->people;
}

int Village::iteration(){
	for(int i=0;i<population;++i){
		this->people.at(i)->move(this->map);
	}

	return 1;
}

struct population_struct Village::getPopulationStruct() {
	struct population_struct res;
	res.id = this->id;
	res.size = this->population;
  res.tab = (struct adn_struct *)malloc(sizeof(struct adn_struct) * res.size);
  for(int i = 0; i < res.size; i++) {
  	vector<Gene> adn = this->people[i]->getGenome()->getAdn();
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
	this->ranking.clear();
	int pop = this->population;
	srand(time(NULL));
	int pt1 = rand()%100;
	int pt2 = pt1+rand()%(100-pt1);
	Genome *g;
	for(int i=0;i<pop;i=i+2){
		if(this->id%4 == 0)
			g = Genome::ChildRandom(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome());
		else if(this->id%4 == 1)
			g = Genome::ChildCrossOverOnePoint(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome(), pt1);
		else if(this->id%4 == 2)
			g = Genome::ChildCrossOverTwoPoint(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome(), pt1, pt2);
		else
			g = Genome::ChildCrossOverhalf(this->people.at(i)->getGenome(), this->people.at(i+1)->getGenome());

		Person *p = new Person(this->population, g, this->map->getStart());
		this->people.push_back(p);
		this->population++;
	}
}

void Village::evaluate(){
	int note = 0;
	Person *p;
	for(int i=0;i<this->population;++i){
		p = this->people.at(i);
		note = -(p->getLocation()->distance(this->map->getStart()) + (1000 * p->getArrived()) - (p->getGenomePosition() * p->getArrived())); 
		this->ranking.push_back(make_pair(i, note));
	}

	std::sort(this->ranking.begin(), this->ranking.end(), pairCompare);	
}

void Village::kill(){
	int pop = this->population;
	for(int i=pop*66/100; i<pop; ++i){
		this->people.erase(this->people.begin()+this->ranking.at(i).first);
		this->population--;
	}
}

static bool pairCompare(const std::pair<int, int>& firstElem, const std::pair<int, int>& secondElem){
  return firstElem.second < secondElem.second;
}