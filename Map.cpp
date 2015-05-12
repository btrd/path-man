#include "Map.h"

using namespace std;

Map::Map()
{
	n = 100;
	m = 50;

	int j = 0;
	string line;

	ifstream map("map");

	if(map.is_open()){
		while(getline(map, line)){
			for(string::size_type i = 0; i < line.size(); ++i){
				char c = line[i];
				int val = atoi(&c);
				Point *p = new Point(i,j,val);
				points.push_back(p);
				if(val == 3){
					this->end = p;
				}
				else if(val == 2){
					this->start = p;
					cout << p->getX();
					cout << p->getY() << "\n";
				}
			}
			j++;
		}
		map.close();
	}

	// int seed = 1002;
	// int val = 0;
	// srand(seed++);
	// int rd_start = rand()%(n*m);
	// srand(seed++);
	// int rd_end = rand()%(n*m);
	// srand(seed++);
	// int size = 5;
	// int rd_x = rand()%n;
	// int rd_y = rand()%m;

	// cout << rd_start << " " << rd_end << "\n";

	// for(int i=0;i<m;++i){
	// 	for(int j=0;j<n;++j){
	// 		if(i == 0 || i == m-1 || j == 0 || j == n-1)
	// 			val = 1;
	// 		else
	// 			val = 0;

	// 		if(i == rd_y && j == rd_x){
	// 			val = 1;
	// 		}
	// 		else if(i >= rd_y && i <= rd_y+size && j >= rd_x && j <= rd_x+size)
	// 			val = 1;

	// 		if(i*n+j == rd_start)
	// 			val = 2;
	// 		else if(i*n+j == rd_end)
	// 			val = 3;


	// 		Point *p = new Point(j,i,val);
	// 		points.push_back(p);
	// 	}
	// }
}

void Map::display(){
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			cout << points.at(i*n+j)->getValue();
		}
		cout << "\n";
	}
}

Point* Map::getStart(){
	return this->start;
}

Point* Map::change(Point* p, int direct, int steps){
	int x = p->getX();
	int y = p->getY();
	Point* res = p;

	for(int i=0;i<steps;i++){
		switch(direct)
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

		res = this->points.at(x+y*n);
		if(res->getValue() == 1 || res->getValue() == 3)
			i=steps;
	}

	return this->points.at(x+y*n);
}

void Map::displayWith(Point* p){
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			if(i == p->getY() && j == p->getX())
				cout << "*";
			else
				cout << points.at(i*n+j)->getValue();
		}
		cout << "\n";
	}
}

vector<Point*> Map::getPoints(){
	return this->points;
}

// int main(int argc, char const *argv[])
// {
// 	Map *m = new Map();
// 	m->display();
// 	return 0;
// }