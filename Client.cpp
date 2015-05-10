#include "Village.h"

int main(int argc, char const *argv[])
{
	Village *v = new Village(1, 100);
	Map *m = v->getMap();
	m->display();

	return 0;
}