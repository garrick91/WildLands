#include "Map.h"


Map::Map(int N){
	mapSize = N;
	GameMap.reserve(pow(mapSize, 2));
}

Map::~Map(){
	GameMap.clear();
}

Block* Map::ReturnChoosen(int _xPos, int _yPos, Graphics * _gfx){
	Block * temp;
	for (auto iter = GameMap.begin(); iter != GameMap.end(); iter++){

		temp = *iter;
		if (temp->MyDot(_xPos, _yPos)){

			temp->Select(_gfx);
			return temp;
		}
	}
}

bool Map::GenerateEmpty(Graphics * _gfx){
	Block *b;
	Coordinates c;
	for (auto i = 0; i < mapSize; i++){

		for (auto j = 0; j < mapSize; j++){

			b = new Block(_gfx);
			c.x = i;
			c.y = j;
			b->AddBlock(c);
			GameMap.push_back(b);
		}
	}
	return true;
}