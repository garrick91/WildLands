#include "Enviroment.h"
#include <fstream>

json InitData(std::string FileName) //ïîäãğóçêà èñõîäíûõ äàííûõ ñ äèñêà
{
	json j_out;
	std::string cipher;
	std::ifstream fin(FileName);
	fin >> cipher;
	fin.close();
	j_out = json::parse(ChangedString(cipher));
	return j_out;
}




//**************************************************************************  ØÀÁËÎÍ  *****************************************************************************//




//************************************************************************  ÄÅĞÅÂÎ  *********************************************************************//
Tree::Tree(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = Trees;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Wood;
	switch (0 + rand() % 7)
	{
	case 0:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_1.png", _gfx, 128, 128);
		break;
	case 1:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_2.png", _gfx, 128, 128);
		resource->currentCount -= 10;
		break;
	case 2:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_3.png", _gfx, 128, 128);
		resource->currentCount -= 25;
		break;
	case 3:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_4.png", _gfx, 128, 128);
		break;
	case 4:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_5.png", _gfx, 128, 128);
		break;
	case 5:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_7.png", _gfx, 128, 128);
		resource->currentCount += 25;
		break;
	case 6:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_8.png", _gfx, 128, 128);
		resource->currentCount += 50;
		break;
	case 7:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_9.png", _gfx, 128, 128);
		resource->currentCount += 25;
		break;
	}
}

Tree::Tree(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = Trees;
	this->resource->currentCount = _amount;
	this->resource->type = Wood;
	switch (0 + rand() % 6)
	{
	case 0:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_1.png", _gfx, 128, 128);
		break;
	case 1:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_2.png", _gfx, 128, 128);
		break;
	case 2:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_3.png", _gfx, 128, 128);
		break;
	case 3:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_4.png", _gfx, 128, 128);
		break;
	case 4:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_5.png", _gfx, 128, 128);
		break;
	case 5:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_7.png", _gfx, 128, 128);
		break;
	case 6:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_8.png", _gfx, 128, 128);
		break;
	case 7:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_9.png", _gfx, 128, 128);
		break;
	default:
		envTexture = new SpriteSheet(L"Textures/Enviroment/treeS_1.png", _gfx, 128, 128);
		break;
	}
}

std::string Tree::Save()
{
	return TemplateSave(this);
}

void Tree::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str,this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

inline int ToScreenX(Coordinates _map)
{
	int screenX = (_map.x - _map.y) * 64;
	return screenX;
}

inline int ToScreenY(Coordinates _map)
{
	int screenY = (_map.x + _map.y) * 32;
	return screenY;
}

void Tree::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + _xPos, ToScreenY (V) - 64+_yPos);

}

void Tree::Update()
{
	envTexture->Update();
}

Tree::~Tree()
{
	delete envTexture;
	delete resource;
}

void Tree::InProgress(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/tree_ip.png", _gfx, 128, 128);
	status = 1;
}

void Tree::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/stump.png", _gfx, 128, 128);
	status = 2;

}

//************************************************************************ ÔĞÓÊÒÎÂÎÅ ÄÅĞÅÂÎ  *********************************************************************//

FruitTree::FruitTree(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = FruitTrees;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Meal;
	envTexture = new SpriteSheet(L"Textures/Enviroment/apple_1.png", _gfx, 128, 128);
}

FruitTree::FruitTree(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = FruitTrees;
	this->resource->currentCount = _amount;
	this->resource->type = Meal;
	envTexture = new SpriteSheet(L"Textures/Enviroment/apple_1.png", _gfx, 128, 128);
}

std::string FruitTree::Save()
{
	return TemplateSave(this);
}

void FruitTree::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void FruitTree::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + _xPos, ToScreenY(V) - 64 + _yPos);

}

void FruitTree::Update()
{
	envTexture->Update();
}

FruitTree::~FruitTree()
{
	delete envTexture;
	delete resource;
}

void FruitTree::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/apple_out.png", _gfx, 128, 128);
	status = 2;
}


//************************************************************************  ÊÀÌÅÍÜ *********************************************************************//

StoneEnv::StoneEnv(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = Rock;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Stone;
	envTexture = new SpriteSheet(L"Textures/Enviroment/rock_1.png", _gfx, 128, 128);

}

StoneEnv::StoneEnv(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = Rock;
	this->resource->currentCount = _amount;
	this->resource->type = Stone;
	envTexture = new SpriteSheet(L"Textures/Enviroment/rock_1.png", _gfx, 128, 128);
}

std::string StoneEnv::Save()
{
	return TemplateSave(this);
}

void StoneEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void StoneEnv::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + _xPos, ToScreenY(V) - 64 + _yPos);
}

StoneEnv::~StoneEnv()
{
	delete envTexture;
	delete resource;
}

void StoneEnv::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/rock_out.png", _gfx, 128, 128);
	status = 2;
}
//************************************************************************  ÇÎËÎÒÎ *********************************************************************//

GoldEnv::GoldEnv(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = GoldDepo;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Gold;
	envTexture = new SpriteSheet(L"Textures/Enviroment/gold_1.png", _gfx, 128, 128);

}

GoldEnv::GoldEnv(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = GoldDepo;
	this->resource->currentCount = _amount;
	this->resource->type = Gold;
	envTexture = new SpriteSheet(L"Textures/Enviroment/gold_1.png", _gfx, 128, 128);
}

std::string GoldEnv::Save()
{
	return TemplateSave(this);
}

void GoldEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void GoldEnv::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + _xPos, ToScreenY(V) - 64 + _yPos);
}

GoldEnv::~GoldEnv()
{
	delete envTexture;
	delete resource;
}


void GoldEnv::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/rock_out.png", _gfx, 128, 128);
	status = 2;
}

//************************************************************************  ÆÅËÅÇÎ *********************************************************************//

IronEnv::IronEnv(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = IronDepo;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Iron;
	envTexture = new SpriteSheet(L"Textures/Enviroment/iron_1.png", _gfx, 128, 128);

}

IronEnv::IronEnv(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = IronDepo;
	this->resource->currentCount = _amount;
	this->resource->type = Iron;
	envTexture = new SpriteSheet(L"Textures/Enviroment/iron_1.png", _gfx, 128, 128);
}

std::string IronEnv::Save()
{
	return TemplateSave(this);
}

void IronEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void IronEnv::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + _xPos, ToScreenY(V) - 64 + _yPos);
}

IronEnv::~IronEnv()
{
	delete envTexture;
	delete resource;
}

void IronEnv::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/rock_out.png", _gfx, 128, 128);
	status = 2;
}


//************************************************************************  ÎËÅÍ² - ÎËÅÍ² (ÍÅ ÁĞÈÒ² ² ÍÅ ÃÎËÅÍ²) *********************************************************************//
DeerEnv::DeerEnv(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = Deer;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Meal;
	switch (0 + rand() % 2)
	{
	case 0:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_1.png", _gfx, 64, 64);
		break;
	case 1:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_2.png", _gfx, 64, 64);
		break;
	case 2:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_3.png", _gfx, 64, 64);
		break;
	default:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_1.png", _gfx, 64, 64);
		break;
	}
}

DeerEnv::DeerEnv(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = Deer;
	this->resource->currentCount = _amount;
	this->resource->type = Meal;
	switch (0 + rand() % 2)
	{
	case 0:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_1.png", _gfx, 64, 64);	
		break;
	case 1:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_2.png", _gfx, 64, 64);	
		break;
	case 2:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_3.png", _gfx, 64, 64);
		break;
	default:
		envTexture = new SpriteSheet(L"Textures/Enviroment/deer_1.png", _gfx, 64, 64);
		break;
	}
}

std::string DeerEnv::Save()
{
	return TemplateSave(this);
}

void DeerEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void DeerEnv::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + 32 + _xPos, ToScreenY(V) - 64 + _yPos);
}

void DeerEnv::Update()
{
	envTexture->Update();
}

DeerEnv::~DeerEnv()
{
	delete envTexture;
	delete resource;
}

void DeerEnv::InProgress(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/deer_dead.png", _gfx, 64, 64);
	status = 1;
}

void DeerEnv::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/anim_dead.png", _gfx, 64, 64);
	status = 2;
}

//************************************************************************  Êîğîâû *********************************************************************//
CowEnv::CowEnv(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = Cow;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Meal;
	
	switch (0 + rand() % 1)
	{
	case 0:
		envTexture = new SpriteSheet(L"Textures/Enviroment/cow_1.png", _gfx, 64, 64);
		break;
	case 1:
		envTexture = new SpriteSheet(L"Textures/Enviroment/cow_2.png", _gfx, 64, 64);
		break;
	}

}

CowEnv::CowEnv(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = Cow;
	this->resource->currentCount = _amount;
	this->resource->type = Meal;
	envTexture = new SpriteSheet(L"Textures/Enviroment/cow_1.png", _gfx, 64, 64);
}

std::string CowEnv::Save()
{
	return TemplateSave(this);
	
}

void CowEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void CowEnv::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + 32 + _xPos, ToScreenY(V) - 64 + _yPos);
}

void CowEnv::Update()
{
	envTexture->Update();
}

CowEnv::~CowEnv()
{
	delete envTexture;
	delete resource;
}

void CowEnv::InProgress(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/cow_dead.png", _gfx, 64, 64);
	status = 1;
}

void CowEnv::ResOut(Graphics * _gfx)
{
	delete envTexture;
	envTexture = new SpriteSheet(L"Textures/Enviroment/anim_dead.png", _gfx, 64, 64);
	status = 2;
}


//************************************************************************  Âîëêè *********************************************************************//
WolfEnv::WolfEnv(std::string _str, Graphics * _gfx)
{
	resource = new Resource(0, Fear);
	this->envType = Wolf;
	switch (0 + rand() % 1)
	{
	case 0:
		envTexture = new SpriteSheet(L"Textures/Enviroment/wolf_1.png", _gfx, 64, 64);
		break;
	case 1:
		envTexture = new SpriteSheet(L"Textures/Enviroment/wolf_2.png", _gfx, 64, 64);
		break;
	}
}

std::string WolfEnv::Save()
{
	return TemplateSave(this);
}

void WolfEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

void WolfEnv::Render(int _xPos, int _yPos)
{
	envTexture->Draw(ToScreenX(V) + 32 + _xPos, ToScreenY(V) - 64 + _yPos);
}

void WolfEnv::Update()
{
	envTexture->Update();
}

WolfEnv::~WolfEnv()
{
	delete envTexture;
	resource = nullptr;
}

//************************************************************************  Ğûáà *********************************************************************//
FishEnv::FishEnv(std::string FileName, Graphics * _gfx)
{
	resource = new Resource();
	json out = InitData(FileName);
	this->envType = Fish;
	this->resource->currentCount = out["startCount"].as<int>();
	this->resource->type = Meal;
}

FishEnv::FishEnv(int _amount, Graphics * _gfx)
{
	resource = new Resource();
	this->envType = Fish;
	this->resource->currentCount = _amount;
	this->resource->type = Meal;
}

std::string FishEnv::Save()
{
	return TemplateSave(this);
}

void FishEnv::Load(std::string _str, Graphics * _gfx)
{
	TemplateLoad(_str, this);
	switch (this->status)
	{
	case 1:
		this->InProgress(_gfx);
		break;
	case 2:
		this->ResOut(_gfx);
		break;
	}
}

FishEnv::~FishEnv()
{
	envTexture = nullptr;
	delete resource;
}