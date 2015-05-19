#ifndef POINT_H
#define POINT_H

class Point
{
public:
	Point(int x, int y, int value);
	~Point();

	int distance(Point *p);	
	int getValue();
	int getY();
	int getX();
	void setValue(int v);

private:
	int x;
	int y;
	int value; // 0 = normal, 1 = obstacle, 2 = door
};

#endif