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
#include <math.h> 


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
	Map(int n, int m, int seed, int hardness);
	~Map();

	void display();
	Point* getStart();
	Point* getEnd();
	Point* change(Point* p, int direct, int steps);
	int getn();
	int getm();
	void displayWithPath(Genome *g);
	void displayWith(Point* p);
	vector<Point*> getPoints();
	vector<pair<int, int> > getPath(Genome *g);

private:
	int n;
	int m;
	Point *start;
	Point *end;
	vector<Point*> points;
	int seed;
	int hardness;

	void addObstacle(int row, int size, int nb, int seed);
};

#endif