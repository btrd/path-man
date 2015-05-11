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
				if(val == 3)
					end = p;
				else if(val == 2)
					start = p;
			}
		}
		j++;
		map.close();
	}
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


// int main(int argc, char const *argv[])
// {
// 	Map *m = new Map();
// 	m->display();
// 	return 0;
// }