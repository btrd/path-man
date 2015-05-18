#include <SFML/Graphics.hpp>
#include <vector>

#define TILE_SIZE 15

/* compile with :

g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o TestMap
./TestMap

 */

using namespace std;

int main()
{
    int m = 50;
    int n = 100;

    int x = 50; // 0 < x < n
    int y = 25; // 0 < y < m
    
    int i, j;

    sf::RenderWindow window(sf::VideoMode(n * TILE_SIZE, m * TILE_SIZE), "Map Rendering Test");
    
    vector<sf::RectangleShape> pixels;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            tile.setOutlineThickness(1);
            tile.setFillColor(sf::Color::Green);
            tile.setOutlineColor(sf::Color(0, 0, 0));
            tile.setPosition(i*TILE_SIZE, j*TILE_SIZE);
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

    return 0;
}