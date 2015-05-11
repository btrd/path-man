#ifndef MAP_H
#define MAP_H

#include "Point.h"
#include "Genome.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>


using namespace std;

enum direction
{
	NORTH, NORTH_EAST, EAST, SOUTH_EAST,
	SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

class Map
{
public:
	Map();
	~Map();

	void display();
	Point* getStart();
	Point* change(Point* p, int direct, int steps);
	void displayWith(Point* p);
	vector<Point*> getPoints();

private:
	int n;
	int m;
	Point *start;
	Point *end;
	vector<Point*> points;
};

#endif