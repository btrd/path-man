#include "Map.h"

using namespace std;

Map::Map()
{
	n = 100;
	m = 50;

	int j = 0;
	string line;

	ifstream map("map2");

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
				}
			}
			j++;
		}
		map.close();
	}
}

Map::Map(int n, int m, int seed, int hardness): n(n), m(m), seed(seed), hardness(hardness)
{
	int val = 0;
	srand(seed);
	int start_x = 1+rand()%3;
	int start_y = 1+rand()%(m-1);
	seed*=2;
	srand(seed);
	int end_x = n-2 - rand()%3;
	int end_y = 1+rand()%(m-1);

	for(int y=0;y<m;++y){
		for(int x=0;x<n;++x){
			if(y == 0 || y == m-1 || x == 0 || x == n-1) // wall
				val = 1;
			else
				val = 0;

			if(x == start_x && y == start_y) // start 
				val = 2;
			else if(x == end_x && y == end_y) // end
				val = 3;


			Point *p = new Point(x,y,val);
			if(val == 2)
				this->start = p;
			else if(val == 3)
				this->end = p;
			points.push_back(p);
		}
	}

	for(int i=1; i<=(n/10)-2; ++i){
		addObstacle(i*10, 6, hardness, seed+i);
	}
}

void Map::addObstacle(int row, int size, int nb, int seed){
	int ob_x = row+rand()%10;
	for(int i=1; i<=nb;++i){
		bool b = false;
		bool c = false;
		int j = 1;
		int k = 0;
		int ob_y = (i-1)*this->m/nb + rand()%(this->m/nb);
		int r = rand()%4;
		for(int y=0;y<m;++y){
			for(int x=0;x<n;++x){
				// if(r == 0){ // square
				// 	if( (y == ob_y && x == ob_x) || (y >= ob_y && y < ob_y+size && x >= ob_x && x < ob_x+size) )
				// 		this->points.at(y*n+x)->setValue(1);
				// }
				// else if(r == 1){ // triangle 
				// 	if( (y == ob_y && x == ob_x) || (y >= ob_y && y < ob_y+size && x >= ob_x && x < ob_x+j) ){
				// 		this->points.at(y*n+x)->setValue(1);
				// 		b = true;
				// 	}
				// }
				// else if(r == 2){ // line
				// 	if( (y == ob_y && x == ob_x) || (y >= ob_y && y < ob_y+size && x >= ob_x && x <= ob_x) )
				// 		this->points.at(y*n+x)->setValue(1);
				// }
				// else{ //circle
					if( (y == ob_y && x == ob_x) 
						|| (y >= ob_y && y < ob_y+size/2 && x >= ob_x && x <= ob_x+j) 
						|| (y >= ob_y && y < ob_y+size/2 && x <= ob_x && x >= ob_x-j)
						|| (y < ob_y+size && y >= ob_y+size/2 && x >= ob_x && x <= ob_x+k) 
						|| (y < ob_y+size && y >= ob_y+size/2 && x <= ob_x && x >= ob_x-k)
					){
						this->points.at(y*n+x)->setValue(1);
						if(y >= ob_y+size/2){
							c = true;
							b = false;
						}
						else
							b=true;
					}
				//}
			}
			if(b){
				k=j;
				j++;
			}
			if(c)
				k--;
		}
	}
}

void Map::display(){
	int val = 0;
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			val = points.at(i*n+j)->getValue();
			if(val == 0)
				cout << " ";
			else if(val == 2)
				cout << "\033[32m2\033[0m";
			else if(val == 3)
				cout << "\033[34m3\033[0m";
			else
				cout << val;
		}
		cout << "\n";
	}
}

Point* Map::getStart(){
	return this->start;
}

int Map::getn()
{
	return this->n;
}
int Map::getm()
{
	return this->m;
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

	return res;
}

vector<pair<int, int> > Map::getPath(Genome *g){
	vector<Gene> adn = g->getAdn();
	vector<pair<int, int> > res;
	int x = start->getX();
	int y = start->getY();
	bool c = true;

	for(int i=0;i<adn.size() && c;i++){
		for(int j=0;j<adn.at(i).steps && c;j++){
			switch(adn.at(i).direct)
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
			res.push_back(make_pair(x, y));
			if(this->points.at(x+y*n)->getValue() == 1 || this->points.at(x+y*n)->getValue() == 3){
				c = false;
			}
		}
	}

	return res;
}

void Map::displayWithPath(Genome *g){
	vector<pair<int, int> > path = getPath(g);
	int val = 0;
	bool flag = false;
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			val = points.at(i*n+j)->getValue();
			for(int k=0;k<path.size() && !flag;++k){
				if(i == path.at(k).second && j == path.at(k).first){
					cout << "\033[31mo\033[0m";
					flag = true;
				}
			}
			if(!flag){
				if(val == 0)
					cout << " ";
				else if(val == 2)
					cout << "\033[32m2\033[0m";
				else if(val == 3)
					cout << "\033[34m3\033[0m";
				else
					cout << val;
			}
			flag = false;
		}
		cout << "\n";
	}
}

void Map::displayWith(Point* p){
	int y = p->getY();
	int x = p->getX();
	int val = 0;
	for(int i=0;i<m;++i){
		for(int j=0;j<n;++j){
			val = points.at(i*n+j)->getValue();
			if(i == y && j == x)
				cout << "\033[31m@\033[0m";
			else if(val == 0)
				cout << " ";
			else if(val == 2)
				cout << "\033[32m2\033[0m";
			else if(val == 3)
				cout << "\033[34m3\033[0m";
			else
				cout << val;
		}
		cout << "\n";
	}
}

vector<Point*> Map::getPoints(){
	return this->points;
}

Point* Map::getEnd(){
	return this->end;
}