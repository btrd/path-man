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
				points.push_back(new Point(i, j, atoi(&c)));
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


// int main(int argc, char const *argv[])
// {
// 	Map *m = new Map();
// 	m->display();
// 	return 0;
// }