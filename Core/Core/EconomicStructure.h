#ifndef ECONOMICSTRUCTURE_H
#define ECONOMICSTRUCTURE_H

#include "Structure.h"
#include <list>



//******************************************************************* ШАБЛОНЫ ****************************************************************//
template <typename T, typename SI, typename ENV> void Find_T(T _obj, EnviromentType type, std::list<ENV*>* _lst, SI* _SI)
{
	const std::vector<Block*> m_Map = _SI->map->ReturnGameMap();
	auto iter = m_Map.begin();
	while (iter != m_Map.end())
	{
		if (((*iter)->blockEnvType == type) &&
			((*iter)->GetPosition().x <= (_obj->coord.x + _obj->workAreaRadius+1)) &&
			((*iter)->GetPosition().x >= (_obj->coord.x - _obj->workAreaRadius+1)) &&
			((*iter)->GetPosition().y <= (_obj->coord.y + _obj->workAreaRadius+1)) &&
			((*iter)->GetPosition().y >= (_obj->coord.y - _obj->workAreaRadius+1)))
		{
			_lst->push_back((ENV*)(*iter)->ReturnEnviroment());
		}
		++iter;
	}
}

template <typename T, typename ENV> bool Action_T(T _obj, std::list<ENV*>* _lst, Graphics * gfx, int * _resAmount)
{
	if ((_obj->workStatus == true) && (!_lst->empty()))
	{
		auto iter = _lst->begin();
		while (iter != _lst->end())
		{
			if ((*iter)->resource->currentCount >= _obj->resIncrease)
			{
				(*iter)->InProgress(gfx);
				(*iter)->resource->currentCount -= _obj->resIncrease;
				_resAmount += _obj->resIncrease;
				return true;
				break;
			}
			else
			{
				(*iter)->ResOut(gfx);
				
				/*if (iter == _lst->end())
				{
					return false;
				}*/
			}
			++iter;
			
		}
		return false;
	}

}


//Здания для добычи ресурсов
//Шахта - уголь
//Хижина дровосека - дерево
//Каменоломня - камень
//Золотодобывающий рудник - золото
//Железодобывающий рудник - железо

//*******************************************************************  ХИЖИНА ДРОВОСЕКА *****************************************************************//


template <typename SI>
class WoodcutterHut : public Structure<SI> { //Хижина дровосека +дерево
	int woodCost; //prm
	int humanCost; //prm
	std::list <Tree*> MainTrees; //find
public:
	WoodcutterHut();
	WoodcutterHut(std::string Filename, Graphics * _gfx);
	WoodcutterHut(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _increase, bool _status, int _area, int _woodCost, int _humanCost, Graphics * _gfx);
	~WoodcutterHut();
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
//	std::string Out();
};


template <typename SI>
WoodcutterHut<SI>::WoodcutterHut()
{
	sType = StWoodCut;
	structureResource = new Resource(0, Wood);
}

template <typename SI>
WoodcutterHut<SI>::WoodcutterHut(std::string FileName, Graphics * _gfx)
{
	sType = StWoodCut;
	structureResource = new Resource(0, Wood);
	workStatus = false;
	this->coord.x = 0;
	this->coord.y = 0;
	//-------------------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>()+2;
	workAreaRadius = out["area"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/WoodcutterHut/WCH.png", _gfx, 128, 128);
}

template <typename SI>
WoodcutterHut<SI>::WoodcutterHut(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _increase, bool _status, int _area, int _woodCost, int _humanCost, Graphics * _gfx)
{
	sType = StWoodCut;
	MainTrees = new std::list <Tree*>;
	this->size = _size;
	this->coord.x = (float)_x;
	this->coord.y = (float)_y;
	this->structureResource = new Resource(_resCoutn, _type);
	this->resIncrease = _increase;
	this->workAreaRadius = _area;
	this->workStatus = _status;

	woodCost = _woodCost;
	humanCost = _humanCost;


	
	texture = new SpriteSheet(L"Textures/WoodcutterHut/WCH.png", _gfx, 128, 128);
}

template <typename SI> 
std::string WoodcutterHut<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void WoodcutterHut<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void WoodcutterHut<SI>::Find(SI *_obj)
{
	Find_T (this, Trees, &MainTrees, _obj);
}

template <typename SI> 
void WoodcutterHut<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void WoodcutterHut<SI>::Destruction(SI* _obj)
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
void WoodcutterHut<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (Action_T(this, &MainTrees, _gfx, &_obj->woodAmount->currentCount))
	{
		_obj->woodAmount->currentCount += resIncrease;
	}
}

template <typename SI>
bool WoodcutterHut<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount && _obj->woodAmount->currentCount >= woodCost)&& (_obj->humanAmount && _obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void WoodcutterHut<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void WoodcutterHut<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos);
}

template <typename SI>
WoodcutterHut<SI>::~WoodcutterHut()
{
	delete texture;
	delete structureResource;
}








//******************************************************************* РУДНИК *****************************************************************//


template <typename SI>
class Quarry : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int humanCost;
	std::list <StoneEnv*> MainStone;
	std::list <IronEnv*> MainIron;
	std::list <GoldEnv*> MainGold;
public:
	Quarry();
	Quarry(std::string Filename, Graphics * _gfx);
	Quarry(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _increase, bool _status, int _area, int _woodCost, int _humanCost, Graphics * _gfx);
	~Quarry();
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
Quarry<SI>::Quarry()
{
	sType = StTQuarry;
	structureResource = new Resource(0, Stone);
}

template <typename SI>
Quarry<SI>::Quarry(std::string FileName, Graphics * _gfx)
{
	sType = StTQuarry;
	structureResource = new Resource(0, Stone);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = false;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	workAreaRadius = out["area"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Quarry/quarry_1.png", _gfx, 128, 128);
}

template <typename SI>
Quarry<SI>::Quarry(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _increase, bool _status, int _area, int _woodCost, int _humanCost, Graphics * _gfx)
{
	sType = StTQuarry;
	MainTrees = new std::list <Tree*>;
	this->size = _size;
	this->coord.x = (float)_x;
	this->coord.y = (float)_y;
	this->structureResource = new Resource(_resCoutn, _type);
	this->resIncrease = _increase;
	this->workAreaRadius = _area;
	this->workStatus = _status;

	woodCost = _woodCost;
	humanCost = _humanCost;



	texture = new SpriteSheet(L"Textures/Quarry/quarry_1.png", _gfx, 128, 128);
}

template <typename SI>
std::string Quarry<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Quarry<SI>::Load( std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Quarry<SI>::Find(SI *_obj)
{
	Find_T (this, Rock, &MainStone, _obj);
	Find_T(this, GoldDepo, &MainGold, _obj);
	Find_T(this, IronDepo, &MainIron, _obj);

}

template <typename SI>
void Quarry<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Quarry<SI>::Destruction(SI* _obj)
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
void Quarry<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (Action_T(this, &MainStone, _gfx, &_obj->stoneAmount->currentCount)) { _obj->stoneAmount->currentCount += resIncrease; }
	if (Action_T(this, &MainIron, _gfx, &_obj->ironAmount->currentCount)) { _obj->ironAmount->currentCount += resIncrease/2; }
	if (Action_T(this, &MainGold, _gfx, &_obj->goldAmount->currentCount)) { _obj->goldAmount->currentCount += resIncrease/2; }
}

template <typename SI>
bool Quarry<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount && _obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount && _obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Quarry<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Quarry<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos, ToScreenY(coord) + _yPos);
}

template <typename SI>
Quarry<SI>::~Quarry()
{
	delete texture;
	delete structureResource;
}



//*******************************************************************  Плавильня *****************************************************************//


template <typename SI>
class Smeltery : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int stoneCost;
	int humanCost;
	int sourceIncrease;
	
public:
	Smeltery();
	Smeltery(std::string Filename, Graphics * _gfx);
	~Smeltery();
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
Smeltery<SI>::Smeltery()
{
	sType = StSmeltery;
	structureResource = new Resource(0, None);,
}

template <typename SI>
Smeltery<SI>::Smeltery(std::string FileName, Graphics * _gfx)
{
	sType = StSmeltery;
	structureResource = new Resource(0, Empty);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = false;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	stoneCost = out["stonecost"].as<int>();
	texture = new SpriteSheet(L"Textures/Smeltery/smelt.png", _gfx, 96, 82);
}


template <typename SI>
std::string Smeltery<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Smeltery<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Smeltery<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Smeltery<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	_obj->stoneAmount->currentCount -= stoneCost;
	this->workStatus = true;
}

template <typename SI>
void Smeltery<SI>::Destruction(SI* _obj)
{
	_obj->humanAmount->currentCount += humanCost;
	if (_obj->sumWeek == buildDate)
	{
		_obj->stoneAmount->currentCount += (int)(0.75*stoneCost);
		_obj->woodAmount->currentCount += (int)(0.75*woodCost);
	}
	else
	{
		_obj->stoneAmount->currentCount += (int)(0.25*stoneCost);
		_obj->woodAmount->currentCount += (int)(0.25*woodCost);
	}
}

template <typename SI>
void Smeltery<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->ironAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->ironAmount->currentCount -= this->sourceIncrease;
		_obj->ironBarsAmount->currentCount += this->resIncrease;
	}

	if (_obj->goldAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->goldAmount->currentCount -= this->sourceIncrease;
		_obj->goldBarsAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Smeltery<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost) && (_obj->stoneAmount->currentCount >= this->stoneCost))
		return true;
	else return false;
}

template <typename SI>
void Smeltery<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Smeltery<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos +16, ToScreenY(coord) + _yPos + 40);
}

template <typename SI>
Smeltery<SI>::~Smeltery()
{
	delete texture;
	delete structureResource;
}



//*******************************************************************  ОРУЖЕЙНИК *****************************************************************//


template <typename SI>
class Armourer : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int humanCost;
	int sourceIncrease;

public:
	Armourer();
	Armourer(std::string Filename, Graphics * _gfx);
	~Armourer();
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
Armourer<SI>::Armourer()
{
	sType = StArmourer;
	structureResource = new Resource(0, Empty);,
}

template <typename SI>
Armourer<SI>::Armourer(std::string FileName, Graphics * _gfx)
{
	sType = StArmourer;
	structureResource = new Resource(0, Empty);
	this->coord.x = 0;
	this->coord.y = 0;
	workStatus = false;
	//------------------------
	json out = InitData(FileName);
	this->size = out["size"].as<int>();
	this->resIncrease = out["resIncrease"].as<int>();
	sourceIncrease = out["sourceIncrease"].as<int>();
	woodCost = out["woodcost"].as<int>();
	humanCost = out["humancost"].as<int>();
	texture = new SpriteSheet(L"Textures/Armourer/armor.png", _gfx, 96, 96);
}


template <typename SI>
std::string Armourer<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Armourer<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Armourer<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Armourer<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Armourer<SI>::Destruction(SI* _obj)
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
void Armourer<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->ironBarsAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->ironBarsAmount->currentCount -= this->sourceIncrease;
		_obj->aammunitionAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Armourer<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Armourer<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Armourer<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos + 16, ToScreenY(coord) + _yPos + 16);
}

template <typename SI>
Armourer<SI>::~Armourer()
{
	delete texture;
	delete structureResource;
}
	


//*******************************************************************  МОНЕТНЫЙ ДВОР  *****************************************************************//


template <typename SI>
class Mint : public Structure<SI> { //Каменоломня +камень
	int woodCost;
	int humanCost;
	int sourceIncrease;

public:
	Mint();
	Mint(std::string Filename, Graphics * _gfx);
	~Mint();
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
Mint<SI>::Mint()
{
	sType = StMint;
	structureResource = new Resource(0, Empty);,
}

template <typename SI>
Mint<SI>::Mint(std::string FileName, Graphics * _gfx)
{
	sType = StMint;
	structureResource = new Resource(0, Empty);
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
	texture = new SpriteSheet(L"Textures/Mint/mint.png", _gfx, 96, 96);
}


template <typename SI>
std::string Mint<SI>::Save()
{
	return TmpSave(this);
}

template <typename SI>
void Mint<SI>::Load(std::string _str)
{
	TmpLoad(this, _str);
}

template <typename SI>
void Mint<SI>::Find(SI *_obj)
{

}

template <typename SI>
void Mint<SI>::Construction(SI* _obj)
{
	_obj->woodAmount->currentCount -= woodCost;
	_obj->humanAmount->currentCount -= humanCost;
	this->workStatus = true;
}

template <typename SI>
void Mint<SI>::Destruction(SI* _obj)
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
void Mint<SI>::Action(SI* _obj, Graphics * _gfx)
{
	if (_obj->goldBarsAmount->currentCount >= this->sourceIncrease && workStatus)
	{
		_obj->goldBarsAmount->currentCount -= this->sourceIncrease;

		_obj->coinsAmount->currentCount += this->resIncrease;
	}
}

template <typename SI>
bool Mint<SI>::CanBuild(SI *_obj)
{
	if ((_obj->woodAmount->currentCount >= woodCost) && (_obj->humanAmount->currentCount >= this->humanCost))
		return true;
	else return false;
}

template <typename SI>
void Mint<SI>::InitBD(SI* _obj)
{
	this->buildDate = _obj->sumWeek;
}

template <typename SI>
void Mint<SI>::Render(int _xPos, int _yPos)
{
	this->texture->Draw(ToScreenX(coord) + _xPos + 16, ToScreenY(coord) + _yPos+32);
}

template <typename SI>
Mint<SI>::~Mint()
{
	delete texture;
	delete structureResource;
}








//
//
////Здания для обработки ресурсов 2 уровня:
////Оруженик - железные слитки -> оружие и броню
////Монетный двор - золотые слитки -> монеты
//
//
//class Armourer : private Structure<SI> { //Оруженик +оружие и броня
//	int sourceAmount;
//public:
//	void MakeAction();
//};

#endif // !ECONOMICSTRUCTURE_H