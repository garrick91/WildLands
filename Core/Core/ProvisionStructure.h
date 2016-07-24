#ifndef PROVISIONSTRUCTURE_H
#define PROVISIONSTRUCTURE_H

#include "Structure.h"
#include "Enviroment.h"
#include "Types.h"
#include <list>

//Структуры по добыче еды:
//Ферма - еда
//Хижина охотника - еда, кожа, мех
//Хижина Рыбака - еда
//Фруктовый сад - еда
//Огород - еда
//Пшеничное поле - пшеничные зёрна
//Плантация хмеля - хмель
//Колодец - вода

//************************************************************ ФЕРМА ********************************************************************//


template <typename SI>
class Farm : public Structure<SI> { //хижина охотника:  + еда
	int woodCost;
	int humanCost;
	std::list <FruitTree*> MainFruit;
public:
	Farm();
	Farm(std::string Filename, Graphics * _gfx);
	~Farm();
	bool CanBuild(SI* _obj);
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	void Find(SI *_obj);
	void Construction(SI* _obj);
	void Destruction(SI* _obj);
	void Action(SI* _obj, Graphics * _gfx);
	void InitBD(SI* _obj);
	void InitPosition(int _x, int _y) { this->coord.x = _x - 1; this->coord.y = _y - 1; };
	std::string Save();
	void Load(std::string _str);
	void Render(int _xPos, int _yPos);
};


template <typename SI>
Farm<SI>::Farm()
{
	sType = StFarm;
	structureResource = new Resource(0, Meal);
}

template <typename SI>
Farm<SI>::Farm(std::string FileName, Graphics * _gfx)
{
	sType = StFarm;
	structureResource = new Resource(0, Meal);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = false;
	//-------------------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	workAreaRadius = out["area"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Farm/farm.png", _gfx, 64, 70);
}


template <typename SI>
std::string Farm<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Farm<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Farm<SI> ::Find(SI *_obj)
{
	Find_T(this, FruitTrees, &MainFruit, _obj);
}

template <typename SI>
void Farm<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Farm<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void Farm<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (Action_T(this, &MainFruit, _gfx, &_obj->mealAmount->currentCount))
	{
			_obj->mealAmount->currentCount += resIncrease;
	}
}

template <typename SI>
bool Farm<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount && _obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount && _obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}


template <typename SI>
void Farm<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Farm<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos+32, ToScreenY(coord) + _yPos+48);
}

template <typename SI>
Farm<SI>::~Farm()
{
	delete texture;
	delete structureResource;
}

//************************************************************ ХИЖИНА ОХОТНИКА ********************************************************************//

template <typename SI>
class HunterHouse : public Structure<SI> { //хижина охотника:  + еда
	int woodCost;
	int humanCost;
	std::list <DeerEnv*> MainHerd;
	std::list <CowEnv*> MainCows;
public:
	HunterHouse();
	HunterHouse(std::string Filename, Graphics * _gfx);
	HunterHouse(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _increase, bool _status, int _area, int _woodCost, int _humanCost,  Graphics * _gfx);
	~HunterHouse();
	bool CanBuild(SI* _obj);
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	void Find(SI *_obj);
	void Construction(SI* _obj);
	void Destruction(SI* _obj);
	void Action(SI* _obj, Graphics * _gfx);
	void InitBD(SI* _obj);
	void InitPosition(int _x, int _y) { this->coord.x = _x-1; this->coord.y = _y-1; };
	std::string Save();
	void Load(std::string _str);
	void Render(int _xPos, int _yPos);
};


template <typename SI>
HunterHouse<SI>::HunterHouse()
{
	sType = StHunter;
	structureResource = new Resource(0, Meal);
}

template <typename SI>
HunterHouse<SI>::HunterHouse(std::string FileName, Graphics * _gfx)
{
	sType = StHunter;
	structureResource = new Resource(0, Meal);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = false;
	//-------------------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	workAreaRadius = out["area"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	switch (0 + rand() % 2)
	{
	case 0:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_0.png", _gfx, 128, 128);
		break;
	case 1:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_1.png", _gfx, 128, 128);
		break;
	case 2:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_2.png", _gfx, 128, 128);
		break;
	default:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_0.png", _gfx, 128, 128);
		break;
	}
}

template <typename SI>
HunterHouse<SI>::HunterHouse(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _increase, bool _status, int _area, int _woodCost, int _humanCost, Graphics * _gfx)
{
	type = Deer;
	sType = StHunter;
	MainHerd = new std::list <DeerEnv*>;
	this->size = _size;
	this->coord.x = (float)_x;
	this->coord.y = (float)_y;
	this->structureResource = new Resource(_resCoutn, _type);
	this->resIncrease = _increase;
	this->workAreaRadius = _area;
	this->workStatus = _status;

	woodCost = _woodCost;
	humanCost = _humanCost;

	switch (0 + rand() % 2)
	{
	case 0:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_0.png", _gfx, 128, 128);
		break;
	case 1:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_1.png", _gfx, 128, 128);
		break;
	case 2:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_2.png", _gfx, 128, 128);
		break;
	default:
		texture = new SpriteSheet(L"Textures/HunterHouse/hunter_0.png", _gfx, 128, 128);
		break;
	}
}

template <typename SI>
std::string HunterHouse<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void HunterHouse<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void HunterHouse<SI> ::Find(SI *_obj)
{
	Find_T (this, Deer, &MainHerd, _obj);
	Find_T(this, Cow, &MainCows, _obj);
}

template <typename SI>
void HunterHouse<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void HunterHouse<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void HunterHouse<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (Action_T(this, &MainHerd, _gfx, &_obj->mealAmount->currentCount)) { _obj->mealAmount->currentCount += resIncrease/2; }
	if (Action_T(this, &MainCows, _gfx, &_obj->mealAmount->currentCount)) { _obj->mealAmount->currentCount += resIncrease/2; }
}

template <typename SI>
bool HunterHouse<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount && _obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount && _obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}


template <typename SI>
void HunterHouse<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void HunterHouse<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord)+_xPos, ToScreenY(coord)+_yPos);
}

template <typename SI>
HunterHouse<SI>::~HunterHouse()
{
	delete texture;
	delete structureResource;
}


//************************************************************ ПОЛЕ ********************************************************************//


template <typename SI>
class Field : public Structure<SI> { 
	int woodCost;
	int humanCost;

public:
	Field();
	Field(std::string Filename, Graphics * _gfx);
	~Field();
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	bool CanBuild(SI* _obj);
	void Find(SI *_obj);
	void Construction(SI* _obj);
	void Destruction(SI* _obj);
	void Action(SI* _obj, Graphics * _gfx);
	void InitBD(SI* _obj);
	void InitPosition(int _x, int _y) { this->coord.x = _x - 1; this->coord.y = _y - 1; };
	std::string Save();
	void Load(std::string _str);
	void Render(int _xPos, int _yPos);
};


template <typename SI>
Field<SI>::Field()
{
	sType = StField;
	structureResource = new Resource(0, Meal);
}

template <typename SI>
Field<SI>::Field(std::string FileName, Graphics * _gfx)
{
	sType = StField;
	structureResource = new Resource(0, Meal);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Field/field.png", _gfx, 128, 128);
}


template <typename SI>
std::string Field<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Field<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Field<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Field<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Field<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void Field<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (workStatus)
	{
		_obj->wheatGrainsAmount->currentCount += this->resIncrease;
		_obj->humulusAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Field<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Field<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Field<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos);
}

template <typename SI>
Field<SI>::~Field()
{
	delete texture;
	delete structureResource;
}


//************************************************************ МЕЛЬНИЦА ********************************************************************//

template <typename SI>
class Mill : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int humanCost;
	int sourceIncrease;

public:
	Mill();
	Mill(std::string Filename, Graphics * _gfx);
	~Mill();
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	bool CanBuild(SI* _obj);
	void Find(SI *_obj);
	void Construction(SI* _obj);
	void Destruction(SI* _obj);
	void Action(SI* _obj, Graphics * _gfx);
	void InitBD(SI* _obj);
	void InitPosition(int _x, int _y) { this->coord.x = _x - 1; this->coord.y = _y - 1; };
	std::string Save();
	void Load(std::string _str);
	void Render(int _xPos, int _yPos);
};


template <typename SI>
Mill<SI>::Mill()
{
	sType = StMill;
	structureResource = new Resource(0, Flour);
}

template <typename SI>
Mill<SI>::Mill(std::string FileName, Graphics * _gfx)
{
	sType = StMill;
	structureResource = new Resource(0, Flour);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Mill/mill.png", _gfx, 32, 83);
}


template <typename SI>
std::string Mill<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Mill<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Mill<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Mill<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Mill<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void Mill<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->wheatGrainsAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->wheatGrainsAmount->currentCount -= this->sourceIncrease;
		_obj->flourAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Mill<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Mill<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Mill<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos + 48, ToScreenY(coord) + _yPos + 30);
}

template <typename SI>
Mill<SI>::~Mill()
{
	delete texture;
	delete structureResource;
}


//************************************************************ ПЕКАРНЯ ********************************************************************//

template <typename SI>
class Bakery : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int humanCost;
	int sourceIncrease;

public:
	Bakery();
	Bakery(std::string Filename, Graphics * _gfx);
	~Bakery();
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	bool CanBuild(SI* _obj);
	void Find(SI *_obj);
	void Construction(SI* _obj);
	void Destruction(SI* _obj);
	void Action(SI* _obj, Graphics * _gfx);
	void InitBD(SI* _obj);
	void InitPosition(int _x, int _y) { this->coord.x = _x - 1; this->coord.y = _y - 1; };
	std::string Save();
	void Load(std::string _str);
	void Render(int _xPos, int _yPos);
};


template <typename SI>
Bakery<SI>::Bakery()
{
	sType = StBaker;
	structureResource = new Resource(0, Meal);
}

template <typename SI>
Bakery<SI>::Bakery(std::string FileName, Graphics * _gfx)
{
	sType = StBaker;
	structureResource = new Resource(0, Meal);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Bakery/baker.png", _gfx, 96, 109);
}


template <typename SI>
std::string Bakery<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Bakery<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Bakery<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Bakery<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Bakery<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void Bakery<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->flourAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->flourAmount->currentCount -= this->sourceIncrease;
		_obj->mealAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Bakery<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Bakery<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Bakery<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos + 16, ToScreenY(coord) + _yPos + 10);
}

template <typename SI>
Bakery<SI>::~Bakery()
{
	delete texture;
	delete structureResource;
}


//************************************************************ ПИВОВАРНЯ ********************************************************************//

template <typename SI>
class Brewery : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int humanCost;
	int sourceIncrease;

public:
	Brewery();
	Brewery(std::string Filename, Graphics * _gfx);
	~Brewery();
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	bool CanBuild(SI* _obj);
	void Find(SI *_obj);
	void Construction(SI* _obj);
	void Destruction(SI* _obj);
	void Action(SI* _obj, Graphics * _gfx);
	void InitBD(SI* _obj);
	void InitPosition(int _x, int _y) { this->coord.x = _x - 1; this->coord.y = _y - 1; };
	std::string Save();
	void Load(std::string _str);
	void Render(int _xPos, int _yPos);
};


template <typename SI>
Brewery<SI>::Brewery()
{
	sType = StBrewer;
	structureResource = new Resource(0, Alcohol);
}

template <typename SI>
Brewery<SI>::Brewery(std::string FileName, Graphics * _gfx)
{
	sType = StBrewer;
	structureResource = new Resource(0, Alcohol);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Brewery/brewer.png", _gfx, 96, 126);
}


template <typename SI>
std::string Brewery<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Brewery<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Brewery<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Brewery<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Brewery<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void Brewery<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->humulusAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->humulusAmount->currentCount -= this->sourceIncrease;
		_obj->AlcoholAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Brewery<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Brewery<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Brewery<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos + 16, ToScreenY(coord) + _yPos);
}

template <typename SI>
Brewery<SI>::~Brewery()
{
	delete texture;
	delete structureResource;
}

#endif // !PROVISIONSTRUCTURE_H