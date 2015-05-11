#include "Village.h"

int main(int argc, char const *argv[])
{
	Village *v = new Village(1, 100);
	Map *m = v->getMap();
	m->display();

	Person *p = v->getPersonTest();
	cout << p->getLocation()->getX() << "\n";
	cout << p->getLocation()->getY() << "\n";
	for(int i=0; i<100;++i){
		m->displayWith(p->getLocation());
		v->iteration();
	}

	return 0;
}