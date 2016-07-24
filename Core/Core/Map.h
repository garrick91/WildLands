#ifndef MAP_H
#define MAP_H


#include "Block.h"
#include <vector>
#include <list>
#include <cmath>


class Map {
	int mapSize; //розмір ігровох мапи
	std::vector <Block*> GameMap; //вектор вказівників на блоки
public:
	Map(int N);
	~Map();
	//генерация заповненної мапи
	template <typename SI> bool GenerateMap(Graphics * _gfx, SI * _settlement); 

	//генерація пустої мапи
	bool GenerateEmpty(Graphics * _gfx); 

	//рендеринг мапи
	template <typename SI> void RenderMap(int _xPos, int _yPos, SI * _obj); 

	//выбір блоку
	Block * ReturnChoosen(int _xPos, int _yPos, Graphics * _gfx); 

	//повернення вектору блоків
	std::vector<Block*> & ReturnGameMap() { return GameMap; } 
	
	// отримання розміру мапи
	int GetSize() { return mapSize; }; 
};




template <typename SI>
bool Map::GenerateMap(Graphics * _gfx, SI * _settlement){
	Block *b;

	int blockCount = pow(mapSize, 2), //кількість блоків
		treeCount = 0.5*blockCount, //приблизна кількість дерев
		stoneCount = 0.035*blockCount, //приблизна кількість каменів
		ironCount = 0.03*blockCount, //приблизна кількість заліза
		goldCount = 0.01*blockCount, //приблизна кількість золота
		deerCount = 0.02*blockCount, //приблизна кількість оленів
		cowCount = 0.02*blockCount, //приблизна кількість коров
		wolfCount = 0.002*blockCount, //приблизна кількість вовків
		fishCount = 0.01*blockCount, //приблизна кількість ставків
		fruitCount = 0.02*blockCount; // приблизна кількість фруктових дерев

	Tree* t;
	FruitTree *ft;
	StoneEnv *s;
	IronEnv *ir;
	GoldEnv *g;
	DeerEnv *d;
	CowEnv *cw;
	WolfEnv * wf;
	FishEnv *fsh;
	Coordinates c;

	for (auto i = 0; i < mapSize; i++){

		for (auto j = 0; j < mapSize; j++){

			b = new Block(_gfx);

			c.x = i;
			c.y = j;
			b->AddBlock(c);
			GameMap.push_back(b);

			if ((1 + rand() % 500) == 1 && wolfCount){

				wf = new WolfEnv("",_gfx);
				wf->ChoosePosition(i, j);
				b->LocateEnviroment(wf, _gfx);
				_settlement->wolfDepos.push_back(wf);
				wolfCount--;
			}
			else if ((1 + rand() % 50) == 1 && fruitCount){

				ft = new FruitTree("Parameters/Fruit.prm", _gfx);
				ft->ChoosePosition(i, j);
				b->LocateEnviroment(ft, _gfx);
				_settlement->fruitDepos.push_back(ft);
				fruitCount--;
			}
			else if ((1 + rand() % 100) == 1 && fishCount){

				fsh = new FishEnv("Parameters/Fish.prm", _gfx);
				fsh->ChoosePosition(i, j);
				b->LocateEnviroment(fsh, _gfx);
				_settlement->fishDepos.push_back(fsh);
				fishCount--;
			}
			else if ((1 + rand() % 100) == 1 && goldCount){

				g = new GoldEnv("Parameters/Gold.prm", _gfx);
				g->ChoosePosition(i, j);
				b->LocateEnviroment(g, _gfx);
				_settlement->goldDepos.push_back(g);
				goldCount--;
			}
			else if ((1 + rand() % 33) == 1 && ironCount){

				ir = new IronEnv("Parameters/Iron.prm", _gfx);
				ir->ChoosePosition(i, j);
				b->LocateEnviroment(ir, _gfx);
				_settlement->ironDepos.push_back(ir);
				ironCount--;
			}
			else if ((1 + rand() % 29) == 1 && stoneCount)	{

				s = new StoneEnv("Parameters/Rocks.prm", _gfx);
				s->ChoosePosition(i, j);
				b->LocateEnviroment(s, _gfx);
				_settlement->rockDepos.push_back(s);
				stoneCount--;
			}
			else if ((1 + rand() % 50) == 1 && deerCount){

				d = new DeerEnv("Parameters/Deer.prm", _gfx);
				d->ChoosePosition(i, j);
				b->LocateEnviroment(d, _gfx);
				_settlement->deerDepos.push_back(d);
				deerCount--;
			}
			else if ((1 + rand() % 50) == 1 && cowCount){

				cw = new CowEnv("Parameters/Cow.prm", _gfx);
				cw->ChoosePosition(i, j);
				b->LocateEnviroment(cw, _gfx);
				_settlement->cowDepos.push_back(cw);
				cowCount--;
			}
			else if ((1 + rand() % 2) == 1 && treeCount){

				t = new Tree("Parameters/Trees.prm", _gfx);
				t->ChoosePosition(i, j);
				b->LocateEnviroment(t, _gfx);
				_settlement->trees.push_back(t);
				treeCount--;
			}
			else{

				continue;
			}
		}
	}
	return true;
}


//Рендеринг будівель
template <typename T> 
inline void LetsRenderStructure(std::list<T> * _lst, std::vector <Block*>::iterator ptr, int _xPos, int _yPos){
	auto iter = _lst->begin();
	while (iter != _lst->end()){

		if (((*ptr)->GetPosition().x == (*iter)->GetPos().x+1 && (*ptr)->GetPosition().y == (*iter)->GetPos().y+1 ) || (*ptr)->ReturnEnviroment()==(*iter)){

			(*iter)->Render(_xPos, _yPos);
		}
		iter++;
	}
}

//Рендеринг об'єктів оточення
template <typename T> 
inline void LetsRenderEnviroment(std::list<T> * _lst, std::vector <Block*>::iterator ptr, int _xPos, int _yPos){
	auto iter = _lst->begin();
	while (iter != _lst->end()){

		if (((*ptr)->GetPosition().x == (*iter)->GetPos().x && (*ptr)->GetPosition().y == (*iter)->GetPos().y) || (*ptr)->ReturnEnviroment() == (*iter)){

			(*iter)->Render(_xPos, _yPos);
		}
		++iter;
	}
}

//Рендеринг окремих об'єктів оточення
template <typename T> 
inline void LetsRenderAnimals(std::list<T> * _lst, std::vector <Block*>::iterator ptr, int _xPos, int _yPos){
	auto iter = _lst->begin();
	while (iter != _lst->end()){

		if (((*ptr)->GetPosition().x == (*iter)->GetPos().x-1 && (*ptr)->GetPosition().y == (*iter)->GetPos().y-1) || (*ptr)->ReturnEnviroment() == (*iter)){

			(*iter)->Render(_xPos, _yPos);
		}
		iter++;
	}
}




template <typename SI>
void Map::RenderMap(int _xPos, int _yPos, SI * _obj){

	for (auto iter = GameMap.begin(); iter != GameMap.end(); iter++){

		(*iter)->RenderBlock(_xPos, _yPos);

		switch ((*iter)->structureType){

		case StWoodCut:
			LetsRenderStructure(&_obj->lstWoodCut, iter, _xPos, _yPos);
			break;
		case StTQuarry:
			LetsRenderStructure(&_obj->lstQuarries, iter, _xPos, _yPos);
			break;
		case StSmeltery:
			LetsRenderStructure(&_obj->lstSmelts, iter, _xPos, _yPos);
			break;
		case StArmourer:
			LetsRenderStructure(&_obj->lstArmors, iter, _xPos, _yPos);
			break;
		case StMint:
			LetsRenderStructure(&_obj->lstMints, iter, _xPos, _yPos);
			break;
		case StHunter:
			LetsRenderStructure(&_obj->lstHunterHouses, iter, _xPos, _yPos);
			break;
		case StFarm:
			LetsRenderStructure(&_obj->lstFarms, iter, _xPos, _yPos);
			break;
		case StMill:
			LetsRenderStructure(&_obj->lstMills, iter, _xPos, _yPos);
			break;
		case StField:
			LetsRenderStructure(&_obj->lstFields, iter, _xPos, _yPos);
			break;
		case StBaker:
			LetsRenderStructure(&_obj->lstBakerys, iter, _xPos, _yPos);
			break;
		case StBrewer:
			LetsRenderStructure(&_obj->lstBrewerys, iter, _xPos, _yPos);
			break;
		case StTents:
			LetsRenderStructure(&_obj->lstTents, iter, _xPos, _yPos);
			break;
		case StChurch:
			LetsRenderStructure(&_obj->lstChurchs, iter, _xPos, _yPos);
			break;
		case StOutpost:
			LetsRenderStructure(&_obj->lstOutposts, iter, _xPos, _yPos);
			break;
		case StTavern:
			LetsRenderStructure(&_obj->lstTaverns, iter, _xPos, _yPos);
			break;
		case StGrave:
			LetsRenderStructure(&_obj->lstGraves, iter, _xPos, _yPos);
			break;
		}

		switch ((*iter)->blockEnvType){

		case Trees:
			LetsRenderEnviroment(&_obj->trees, iter, _xPos, _yPos);
			break;
		case Rock:
			LetsRenderEnviroment(&_obj->rockDepos, iter, _xPos, _yPos);
			break;
		case GoldDepo:
			LetsRenderEnviroment(&_obj->goldDepos, iter, _xPos, _yPos);
			break;
		case IronDepo:
			LetsRenderEnviroment(&_obj->ironDepos, iter, _xPos, _yPos);
			break;
		case Deer:
			LetsRenderAnimals(&_obj->deerDepos, iter, _xPos, _yPos);
			break;
		case Cow:
			LetsRenderAnimals(&_obj->cowDepos, iter, _xPos, _yPos);
			break;
		case Wolf:
			LetsRenderEnviroment(&_obj->wolfDepos, iter, _xPos, _yPos);
			break;
		case FruitTrees:
			LetsRenderEnviroment(&_obj->fruitDepos, iter, _xPos, _yPos);
			break;	
		}
		
	}
}


#endif // !MAP_H