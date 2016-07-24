#pragma once
#ifndef SOCIALSTRUCTURE_H
#define SOCIALSTRUCTURE_H


#include "Structure.h"
#include "Types.h"
#include <vector>
#include <sstream>
#include <fstream>

using jsoncons::json;
using jsoncons::json_serializer;
using jsoncons::json_deserializer;


//***************************************************************** ЗЕМЛЯНКА (ПАЛАТКА) ********************************************************************//

template <typename SI>
class Dugout :  public Structure<SI> {
public:
	int numOfResidents; //количество жителей
	int firewood; //количество дров
	int pleasureMulct; //штраф
	FoodPortion portion; //порция еды
	int woodCost; //количестов дерева
	Dugout();
	Dugout(std::string FileName, Graphics * _gfx);
	Dugout(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _woodCost, int _firewood, int _mulct, FoodPortion _portion, int _increase, int _area, bool _status, int _relCount, ResourceType _rel, int _fearCount, ResourceType _fear, Graphics * _gfx);
	~Dugout();
	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	bool CanBuild(SI* _obj); //проверка на возможность строительства
	void Construction(SI* _obj); //постройка здания
	void Destruction(SI* _obj); //уничтожение здания
	void Action(SI * _obj, Graphics * _gfx);
	void InitBD(SI* _obj); //запомнить дату строительства
	void InitPosition(int _x, int _y) { this->coord.x = _x - 1; this->coord.y = _y - 1; };
	std::string Save(); //сохранение
	void Load(std::string); //загрузка
	void Render(int _xPos, int _yPos); //отрисовка
};


template <typename SI, typename ST> void ActionTemp(ST* t, SI* _obj)
{
	if (_obj->mealAmount  && _obj->mealAmount->currentCount > (int)(t->numOfResidents*t->portion))
	{
		_obj->mealAmount->currentCount -= t->numOfResidents*t->portion;
		_obj->totalPleasure->currentCount += t->numOfResidents*t->resIncrease*t->portion;

	}
	else
	{
		_obj->totalPleasure->currentCount -= t->pleasureMulct*t->numOfResidents;
	}

	if (_obj->woodAmount->currentCount > t->firewood)
	{
		_obj->totalPleasure->currentCount += t->numOfResidents*t->firewood;
	}
	else
	{
		_obj->totalPleasure->currentCount -= t->pleasureMulct*t->firewood;
	}
}


 //подгрузка исходных данных с диска

template <typename SI>
Dugout<SI>::Dugout()
{
	sType = StTents;
	structureResource = new Resource(0, Human);
}

template <typename SI>
Dugout<SI>::Dugout(std::string FileName, Graphics * _gfx)
{
	sType = StTents;
	//------------------------------------------
	
	structureResource = new Resource(0, Human);
	this->coord.x = 0;
	this->coord.y = 0;
	
	workStatus = false;
	workAreaRadius = 0;
	//-----------------------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	woodCost = out["woodcost"].as<int>();
	firewood = out["firewood"].as<int>();
	numOfResidents = out["resIncrease"].as<int>();
	pleasureMulct = out["mulct"].as<int>() - 6;
	portion = Normal;
	switch (0 + rand() % 3)
	{
	case 0:
		texture = new SpriteSheet(L"Textures/Dugout/tentS_1.png", _gfx, 128, 128);
		break;
	case 1:
		texture = new SpriteSheet(L"Textures/Dugout/tentS_2.png", _gfx, 128, 128);
		break;
	case 2:
		texture = new SpriteSheet(L"Textures/Dugout/tentS_3.png", _gfx, 128, 128);
		break;
	case 3:
		texture = new SpriteSheet(L"Textures/Dugout/tentS_4.png", _gfx, 128, 128);
		break;
	}
}

template <typename SI>
Dugout<SI>::Dugout(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _woodCost, int _firewood, int _mulct, FoodPortion _portion, int _increase, int _area, bool _status, int _relCount, ResourceType _rel, int _fearCount, ResourceType _fear, Graphics * _gfx)
{
	sType = StTents;
	this->size = _size;
	this->coord.x = (float)_x;
	this->coord.y = (float)_y;
	this->structureResource = new Resource(_resCoutn, _type);
	numOfResidents = structureResource->currentCount;
	woodCost = _woodCost;
	firewood = _firewood;
	pleasureMulct = _mulct;
	portion = _portion;
	this->resIncrease = _increase;
	this->workAreaRadius = _area;
	this->workStatus = _status;
	MainReligion = new Resource(_relCount, _rel);
	MainFear = new Resource(_fearCount, _fear);
	switch (0 + rand() % 3)
	{
	case 0:
		texture = new SpriteSheet(L "Textures/Dugout/tentS_1.png", _gfx, 128, 128);
			break;
	case 1:
		texture = new SpriteSheet(L "Textures/Dugout/tentS_2.png", _gfx, 128, 128);
		break;
	case 2:
		texture = new SpriteSheet(L "Textures/Dugout/tentS_3.png", _gfx, 128, 128);
		break;
	case 3:
		texture = new SpriteSheet(L "Textures/Dugout/tentS_4.png", _gfx, 128, 128);
		break;
	default:
		texture = new SpriteSheet(L "Textures/Dugout/tentS_1.png", _gfx, 128, 128);
		break;
	}
}

template <typename SI>
Dugout<SI>::~Dugout()
{
	delete structureResource;
	delete texture;
}


template <typename SI>
void Dugout<SI>::Action(SI* _obj, Graphics * _gfx)
{
	ActionTemp(this, _obj);
}

template <typename SI>
void Dugout<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount += numOfResidents;
	_obj->totalHumans->currentCount += numOfResidents;
	this->workStatus = true;
}

template <typename SI>
void Dugout<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount -= numOfResidents;
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
bool Dugout<SI>::CanBuild(SI* _obj)
{
	if (_obj->woodAmount && _obj->woodAmount->currentCount >= woodCost)
		return true;
	else return false;
}

template <typename SI>
std::string Dugout<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Dugout<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Dugout<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Dugout<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos);
}

//************************************************************ ЦЕРКОВЬ ********************************************************************//

template <typename SI>
class Church : public Structure<SI> { //Каменоломня +камень
	int stoneCost;
	int humanCost;
	int sourceIncrease;
public:
	Church();
	Church(std::string Filename, Graphics * _gfx);
	~Church();
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
Church<SI>::Church()
{
	sType = StChurch;
	structureResource = new Resource(0, Religion);
}

template <typename SI>
Church<SI>::Church(std::string FileName, Graphics * _gfx)
{
	sType = StChurch;
	structureResource = new Resource(0, Religion);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	stoneCost = out["stonecost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Church/church.png", _gfx, 128, 128);
}


template <typename SI>
std::string Church<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Church<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Church<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Church<SI>::Construction(SI* _obj)
{
	_obj->stoneAmount->currentCount -= stoneCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Church<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->stoneAmount->currentCount += (int)(0.75*stoneCost);
	}
	else
	{
		_obj->stoneAmount->currentCount += (int)(0.25*stoneCost);
	}
}

template <typename SI>
void Church<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->AlcoholAmount->currentCount >= (this->sourceIncrease/2) && workStatus && _obj->coinsAmount->currentCount >= this->sourceIncrease)
	{
		_obj->coinsAmount->currentCount -= this->sourceIncrease;
		_obj->AlcoholAmount->currentCount -= this->sourceIncrease;
		_obj->totalReligion->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Church<SI>::CanBuild(SI *_obj)
{
	if ((_obj->stoneAmount->currentCount >= stoneCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Church<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Church<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos+10);
}

template <typename SI>
Church<SI>::~Church()
{
	delete texture;
	delete structureResource;
}

//************************************************************ СТОРОЖЕВОЙ ПОСТ ********************************************************************//

template <typename SI>
class Outpost : public Structure<SI> {
	int stoneCost;
	int humanCost;
	int sourceIncrease;
public:
	Outpost();
	Outpost(std::string Filename, Graphics * _gfx);
	~Outpost();
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
Outpost<SI>::Outpost()
{
	sType = StOutpost;
	structureResource = new Resource(0, Fear);
}

template <typename SI>
Outpost<SI>::Outpost(std::string FileName, Graphics * _gfx)
{
	sType = StOutpost;
	structureResource = new Resource(0, Fear);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	stoneCost = out["stonecost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Outpost/0.png", _gfx, 128, 128);
}


template <typename SI>
std::string Outpost<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Outpost<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Outpost<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Outpost<SI>::Construction(SI* _obj)
{
	_obj->stoneAmount->currentCount -= stoneCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Outpost<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->stoneAmount->currentCount += (int)(0.75*stoneCost);
	}
	else
	{
		_obj->stoneAmount->currentCount += (int)(0.25*stoneCost);
	}
}

template <typename SI>
void Outpost<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->aammunitionAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->aammunitionAmount->currentCount -= this->sourceIncrease;
		_obj->totalFear->currentCount -= this->resIncrease;
	}
}

template <typename SI>
bool Outpost<SI>::CanBuild(SI *_obj)
{
	if ((_obj->stoneAmount->currentCount >= stoneCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Outpost<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Outpost<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos+5);
}

template <typename SI>
Outpost<SI>::~Outpost()
{
	delete texture;
	delete structureResource;
}

//************************************************************ ТАВЕРНА ********************************************************************//

template <typename SI>
class Tavern : public Structure<SI> {
	int stoneCost;
	int humanCost;
	int sourceIncrease;
public:
	Tavern();
	Tavern(std::string Filename, Graphics * _gfx);
	~Tavern();
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
Tavern<SI>::Tavern()
{
	sType = StTavern;
	structureResource = new Resource(0, Pleasure);
}

template <typename SI>
Tavern<SI>::Tavern(std::string FileName, Graphics * _gfx)
{
	sType = StTavern;
	structureResource = new Resource(0, Pleasure);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	stoneCost = out["stonecost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Tavern/0.png", _gfx, 128, 151);
}


template <typename SI>
std::string Tavern<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Tavern<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Tavern<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Tavern<SI>::Construction(SI* _obj)
{
	_obj->stoneAmount->currentCount -= stoneCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Tavern<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->stoneAmount->currentCount += (int)(0.75*stoneCost);
	}
	else
	{
		_obj->stoneAmount->currentCount += (int)(0.25*stoneCost);
	}
}

template <typename SI>
void Tavern<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->AlcoholAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->AlcoholAmount->currentCount -= this->sourceIncrease;
		_obj->totalPleasure->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Tavern<SI>::CanBuild(SI *_obj)
{
	if ((_obj->stoneAmount->currentCount >= stoneCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Tavern<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Tavern<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos -20);
}

template <typename SI>
Tavern<SI>::~Tavern()
{
	delete texture;
	delete structureResource;
}



//************************************************************ КЛАДБИЩЕ ********************************************************************//

template <typename SI>
class Grave : public Structure<SI> {
	int stoneCost;
	int humanCost;
public:
	Grave();
	Grave(std::string Filename, Graphics * _gfx);
	~Grave();
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
Grave<SI>::Grave()
{
	sType = StGrave;
	structureResource = new Resource(0, Religion);
}

template <typename SI>
Grave<SI>::Grave(std::string FileName, Graphics * _gfx)
{
	sType = StGrave;
	structureResource = new Resource(0, Religion);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = true;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	stoneCost = out["stonecost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Grave/0.png", _gfx, 64, 81);
}


template <typename SI>
std::string Grave<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Grave<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Grave<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Grave<SI>::Construction(SI* _obj)
{
	_obj->stoneAmount->currentCount -= stoneCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Grave<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->stoneAmount->currentCount += (int)(0.75*stoneCost);
	}
	else
	{
		_obj->stoneAmount->currentCount += (int)(0.25*stoneCost);
	}
}

template <typename SI>
void Grave<SI>::Action(SI* _obj, Graphics * _gfx)
{

	_obj->totalReligion->currentCount += this->resIncrease;
	_obj->totalFear->currentCount += (this->resIncrease/2);

}

template <typename SI>
bool Grave<SI>::CanBuild(SI *_obj)
{
	if ((_obj->stoneAmount->currentCount >= stoneCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Grave<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Grave<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos + 32, ToScreenY(coord) + _yPos + 45);
}

template <typename SI>
Grave<SI>::~Grave()
{
	delete texture;
	delete structureResource;
}

#endif // !SOCIALSTRUCTURE_H