#include "Village.h"
#include "callRpc.h"
#include "population_struct.h"
#include "Genome.h"

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
    int x,y;
    
    vector<Point*> points = map->getPoints();
    vector<sf::RectangleShape> pixels;
    Point * tmp_point;
    Genome * best;
    Gene gene;
    sf::RenderWindow window(sf::VideoMode(n * TILE_SIZE, m * TILE_SIZE), "Map Rendering Test");
    	

    while (window.isOpen()) //Boucle principale
    {
    	//Close Event
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //---------Redraw Window
        //Prepare Map 
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
	            	default: //default (mmap invalid)é
	            		tile.setFillColor(sf::Color::White);
	            		break;
	            }
	            tile.setPosition(tmp_point->getX()*TILE_SIZE, tmp_point->getY()*TILE_SIZE);
	            
	            pixels.push_back(tile);
	        } 
	    }

        window.clear();
        
        best = v->getPersonTest()->getGenome();
        tmp_point = map->getStart();
        x = tmp_point->getX();
        y = tmp_point->getY();

        for (i = 0; i < best->getSize()-1; i++)
        {
        	gene = best->getAdn().at(i);
			for (j = 0; j < gene.steps; j++)
			{
				switch(gene.direct)
				{
					case NORTH:
						--y;
						break;
					case NORTH_EAST:
						--y;
						++x;
						break;
					case EAST:
						++x;
						break;
					case SOUTH_EAST:
						++y;
						++x;
						break;
					case SOUTH:
						++y;
						break;
					case SOUTH_WEST:
						++y;
						--x;
						break;
					case WEST:
						--x;
						break;
					case NORTH_WEST:
						--y;
						--x;
						break;
				}
				if (x <= 0 || y <= 0 || x >= m || y >=n)
				{
					i = best->getSize();
					break;
				}
				pixels.at(y*n+x).setFillColor(sf::Color::Magenta);
			}
        }


        for (i = 0; i < n; i++) //draw map
        {
            for (j = 0; j < m; j++)
            {
                window.draw(pixels.at(i*m+j));
            }
        }
        window.display();

        //----------End Redraw
    }
}

int main(int argc, char const *argv[])
{
	if(argc != 2)
	{
		cout << "Usage : ./Client <idvillage>" << endl;
		return -1;
	}
	Village *v = new Village(atoi(argv[1]), 10);
	drawmap(v);
	struct population_struct pop = v->getPopulationStruct();
	struct population_struct new_pop = call_rpc(pop);
	// v->setPopulationStruct(new_pop);
	return 0;
}
