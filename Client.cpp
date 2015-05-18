#include "Village.h"
#include "callRpc.h"
#include "population_struct.h"

#include <SFML/Graphics.hpp>

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

void drawmap(Village *v)
{
    int i, j;
    int TILE_SIZE = 15;
	Map *map = v->getMap();
	int m = map->getm();
    int n = map->getn();
    
    vector<Point*> points = map->getPoints();
    vector<sf::RectangleShape> pixels;
    Point * tmp_point;

    sf::RenderWindow window(sf::VideoMode(n * TILE_SIZE, m * TILE_SIZE), "Map Rendering Test");
    

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setOutlineThickness(1);
            tile.setOutlineColor(sf::Color(0, 0, 0));
            
            tmp_point = points.at(i*m+j);

            switch(tmp_point->getValue())
            {
            	case 0: //normal
            		tile.setFillColor(sf::Color::Green);
            		break;
            	case 1: //Wall
            		tile.setFillColor(sf::Color::White);
            		break;
            	case 2: //Start
            		tile.setFillColor(sf::Color::Red);
            		break;
            	case 3: //End
            		tile.setFillColor(sf::Color::Blue);
            		break;
            	default: //default (mmap invalid)
            		cout << "'" << tmp_point->getValue()<< "'" << endl;
            		tile.setFillColor(sf::Color::Magenta);
            		break;
            }
            tile.setPosition(tmp_point->getX()*TILE_SIZE, tmp_point->getY()*TILE_SIZE);
            
            pixels.push_back(tile);
        } 
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                window.draw(pixels.at(i*m+j));
            }
        }
        window.display();
    }
}

int main(int argc, char const *argv[])
{
	Village *v = new Village(atoi(argv[1]), 10);
	drawmap(v);
	struct population_struct pop = v->getPopulationStruct();
	struct population_struct new_pop = call_rpc(pop);
	// v->setPopulationStruct(new_pop);
	return 0;
}
