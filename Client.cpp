#include "Village.h"
#include "callRpc.h"
#include "Genome.h"
#include <unistd.h>
#include "adn_exchange.grpc.pb.h"

#include <SFML/Graphics.hpp>

using pathman::Adn;

void showMap(Village *v, int nb) {
	Map *map = v->getMap();
	map->display();

	for(int l=0; l<nb;++l){
		v->iterate();

		Person *p = v->getPersonTest();

		map->displayWith(p->getLocation());
		// cout << "--Generation : " << l << "\n";
		// cout << "Position : " << p->getGenomePosition() << "\n";
		// cout << "Alive : " << p->getAlive() << "\n";
		// cout << "Note : " << v->getBestNote() << "\n";
		// cout << "Distance to end : " << p->getLocation()->distance(v->getMap()->getEnd()) << "\n";
		// cout << "X : " << p->getLocation()->getX() << "\n";
		// cout << "Y : " << p->getLocation()->getY() << "\n\n";
		sleep(1);
		v->generate();
		if(p->getLocation()->distance(v->getMap()->getEnd()) == 0){
			l = nb;
			cout << "YEAH" << "\n";
		}
	}
}

void drawmap(Village *v, int nbGeneration)
{
  int i, j, k;
  int TILE_SIZE = 15;
  Map *map = v->getMap();
  int m = map->getm();
  int n = map->getn();
  int x, y;
  vector<Point*> points = map->getPoints();
  vector<sf::RectangleShape> pixels;
  Point * tmp_point;
  Genome * best;
  Gene gene;
  sf::RenderWindow window(sf::VideoMode(n * TILE_SIZE, m * TILE_SIZE), "Map Rendering Test");

  for (k = 0; k < nbGeneration; k++) //Start new Generation
  {
    srand(time(NULL) + k);
    cout << "Generation num : " << k << endl;
    v->iterate();
    //Close Event
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    //---------Redraw Window
    //Prepare Map
    pixels.clear();
    for (i = 0; i < n; i++)
    {
      for (j = 0; j < m; j++)
      {
        sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        tile.setOutlineThickness(1);
        tile.setOutlineColor(sf::Color(0, 0, 0));

        tmp_point = points.at(i * m + j);

        switch (tmp_point->getValue())
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
    //       Person *p = v->getPersonTest();
    // cout << "--Generation : " << k << "\n";
    // cout << "Position : " << p->getGenomePosition() << "\n";
    // cout << "Alive : " << p->getAlive() << "\n";
    // cout << "Note : " << v->getBestNote() << "\n";
    // cout << "Distance to end : " << p->getLocation()->distance(v->getMap()->getEnd()) << "\n";
    // cout << "X : " << p->getLocation()->getX() << "\n";
    // cout << "Y : " << p->getLocation()->getY() << "\n\n";

    tmp_point = map->getStart();
    x = tmp_point->getX();
    y = tmp_point->getY();

    for (i = 0; i < best->getSize() - 1; i++)
    {
      gene = best->getAdn().at(i);
      for (j = 0; j < gene.steps; j++)
      {
        switch (gene.direct)
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
        if (x <= 0 || y <= 0 || x >= m || y >= n
            || points.at(y * n + x)->getValue() == 1 //hit a wall
            || points.at(y * n + x)->getValue() == 3) //ended
        {
          i = best->getSize();
          break;
        }
        pixels.at(y * n + x).setFillColor(sf::Color::Magenta);
      }
    }
    pixels.at(y * n + x).setFillColor(sf::Color::Black);

    for (i = 0; i < n; i++) //draw map
    {
      for (j = 0; j < m; j++)
      {
        window.draw(pixels.at(i * m + j));
      }
    }
    window.display();

    //----------End Redraw
    v->generate();
  }//End Generation
  cout << "Finished" << endl;
  while (window.isOpen()) //Boucle principale
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
        window.close();
    }
  }
}

int main(int argc, char const *argv[])
{
  if (argc != 3)
  {
    cout << "Usage : ./Client <idvillage> <nbGeneration>" << endl;
    return -1;
  }
  Village *v = new Village(atoi(argv[1]), 100);
  //drawmap(v, atoi(argv[2]));
  //showMap(v, atoi(argv[2]));
  // std::vector<Adn> adn_list = v->getAdnVector(50);
  // std::vector<Adn> new_adn_list = callRpc(adn_list);
  // v->setAdnVector(adn_list);
  return 0;
}
