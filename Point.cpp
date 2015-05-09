#include "Point.h"

#include <cmath>

Point::Point(int x, int y, int value) : x(x), y(y), value(value)
{}

int Point::distance(const Point &P) const
{
	int dx = this->x - P.x;
	int dy = this->y - P.y;
	return sqrt(dx*dx + dy*dy);
}

int Point::getValue(){
	return this->value;
}