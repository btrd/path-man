#include "Village.h"
#include "callRpc.h"
#include "population_struct.h"

extern "C" struct population_struct call_rpc(struct population_struct);

void showMap(Village *v) {
	Map *map = v->getMap();
	map->display();

	// Person *p = v->getPersonTest();
	// cout << p->getLocation()->getX() << "\n";
	// cout << p->getLocation()->getY() << "\n";
	vector<Person*> people = v->getPeople();
	int n = 100;
	int m = 50;
	bool b = false;
	int val;

	for(int l=0; l<100;++l){
		if(l==99){
			v->iteration();

			for(int i=0;i<m;++i){
				for(int j=0;j<n;++j){
					for(unsigned int k=0;k<people.size() && !b;++k){
						if(i == people.at(k)->getLocation()->getY() && j == people.at(k)->getLocation()->getX())
							b = true;
					}
					val = map->getPoints().at(i*n+j)->getValue();
					if(b)
						cout << "*";
					else if(val == 0)
						cout << " ";
					else
						cout << val;

					if(b && val == 3)
						l = 100;
					b = false;
				}
				cout << "\n";
			}

			v->evaluate();
			v->kill();
			v->reproduce();

			l=0;
		}
		else{
			v->iteration();
		}
	}
}

int main(int argc, char const *argv[]) {
	Village *v = new Village(1, 10);
	struct population_struct pop = v->getPopulationStruct();
	struct population_struct new_pop = call_rpc(pop);
	// v->setPopulationStruct(new_pop);
	//showMap(v);
	return 0;
}