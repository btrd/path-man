#include "Point.h"

#include <cmath>

Point::Point(int x, int y, int value) : x(x), y(y), value(value)
{}

int Point::distance(Point *p)
{
	int dx = this->x - p->x;
	int dy = this->y - p->y;
	return sqrt(dx*dx + dy*dy);
}

int Point::getValue(){
	return this->value;
}

int Point::getX(){
	return this->x;
}

int Point::getY(){
	return this->y;
}

void Point::setValue(int v){
	this->value = v;
}