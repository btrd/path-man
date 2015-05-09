#ifndef MAP_H
#define MAP_H

#include "Point.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

class Map
{
public:
	Map();
	~Map();

	void display();

private:
	int n;
	int m;
	Point *start;
	Point *end;
	vector<Point*> points;
};

#endif