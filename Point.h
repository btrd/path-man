#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point(int x, int y, int value);
	~Point();

	int distance(const Point &P) const;	

private:
	int x;
	int y;
	int value; // 0 = normal, 1 = obstacle, 2 = door
};

#endif