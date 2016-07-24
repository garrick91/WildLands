#ifndef ENVIROMENT_H
#define ENVIROMENT_H

#include "Coordinates.h"
#include "Resources.h"
#include "Graphics.h"
#include "SpriteSheet.h"
#include <string>
#include "jsoncons\json.hpp"
using jsoncons::json;
using jsoncons::json_serializer;
using jsoncons::json_deserializer;


class Enviroment
{
public:
	Coordinates V; //set !
	SpriteSheet *envTexture; //prm
	EnviromentType envType;  //prm
	Resource* resource; //prm/set
	int status; //set

	virtual std::string Save() { return ""; }
	virtual void Load(std::string _str, Graphics * _gfx) {}
	virtual void Render(int _xPos, int _yPos) {}
	virtual void Update() {}
	virtual void ChoosePosition(int _x, int _y) {}
	virtual void InProgress(Graphics * _gfx) {}
	virtual void ResOut(Graphics * _gfx) {}
	virtual Coordinates GetPos() { return V; }
};


class Tree : public Enviroment
{
public:
	Tree(std::string FileName, Graphics * _gfx);
	Tree(int _amount, Graphics * _gfx);
	~Tree();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void Update();
	void ChoosePosition(int _x, int _y) { V.x = _x; V.y = _y; };
	void InProgress(Graphics * _gfx);
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }
};


class FruitTree : public Enviroment
{
public:
	FruitTree(std::string FileName, Graphics * _gfx);
	FruitTree(int _amount, Graphics * _gfx);
	~FruitTree();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void Update();
	void ChoosePosition(int _x, int _y) { V.x = _x; V.y = _y; };
	void InProgress(Graphics * _gfx){}
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }

};

class StoneEnv : public Enviroment
{
public:
	StoneEnv(std::string FileName, Graphics * _gfx);
	StoneEnv(int _amount, Graphics * _gfx);
	~StoneEnv();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void ChoosePosition(int _x, int _y) { V.x = _x; V.y = _y; };
	void InProgress(Graphics * _gfx) {}
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }

};

class GoldEnv : public Enviroment
{
public:
	GoldEnv(std::string FileName, Graphics * _gfx);
	GoldEnv(int _amount, Graphics * _gfx);
	~GoldEnv();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void ChoosePosition(int _x, int _y) { V.x = _x; V.y = _y; };
	void InProgress(Graphics * _gfx) {}
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }

};

class IronEnv : public Enviroment
{
public:
	IronEnv(std::string FileName, Graphics * _gfx);
	IronEnv(int _amount, Graphics * _gfx);
	~IronEnv();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void ChoosePosition(int _x, int _y) { V.x = _x; V.y = _y; };
	void InProgress(Graphics * _gfx) {}
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }

};

class DeerEnv : public Enviroment
{
public:
	DeerEnv(std::string FileName, Graphics * _gfx);
	DeerEnv(int _amount, Graphics * _gfx);
	~DeerEnv();
	void Update();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void ChoosePosition(int _x, int _y) { V.x = _x+1; V.y = _y+1; };
	void InProgress(Graphics * _gfx);
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }

};

class CowEnv :public Enviroment
{
public:
	CowEnv(std::string FileName, Graphics * _gfx);
	CowEnv(int _amount, Graphics * _gfx);
	~CowEnv();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void Update();
	void ChoosePosition(int _x, int _y) { V.x = _x+1; V.y = _y+1; };
	void InProgress(Graphics * _gfx);
	void ResOut(Graphics * _gfx);
	Coordinates GetPos() { return V; }

};

class WolfEnv :public Enviroment
{
public:
	WolfEnv(std:: string _str,Graphics * _gfx);
	~WolfEnv();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void Render(int _xPos, int _yPos);
	void Update();
	void ChoosePosition(int _x, int _y) { V.x = _x; V.y = _y; };
	void InProgress(Graphics * _gfx) {}
	void ResOut(Graphics * _gfx) {}
	Coordinates GetPos() { return V; }

};

class FishEnv :public Enviroment
{
public:
	FishEnv(std::string FileName, Graphics * _gfx);
	FishEnv(int _amount, Graphics * _gfx);
	~FishEnv();
	std::string Save();
	void Load(std::string _str, Graphics * _gfx);
	void ChoosePosition(int _x, int _y) { V.x = _x + 1; V.y = _y + 1; };
	void InProgress(Graphics * _gfx){}
	void ResOut(Graphics * _gfx) {}
	Coordinates GetPos() { return V; }

};


inline std::string ChangedString(std::string _source) //Встраиваемая функция шифровки/дешифровки
{
	std::string _result;
	for (int n = 0; n < _source.length(); n++)
	{
		_result += _source[n] ^ 11;
	}
	return _result;
}


json InitData(std::string FileName);
template <typename Env>
std::string TemplateSave(Env * _obj)
{
	json j_in;
	std::string cipher, decipher;
	j_in["xPos"] = _obj->V.x;
	j_in["yPos"] = _obj->V.y;
	j_in["startCount"] = _obj->resource->currentCount;
	j_in["status"] = _obj->status;
	decipher = j_in.to_string();
	cipher = ChangedString(decipher);
	return  cipher;
}

template <typename Env>
void TemplateLoad(std::string _str, Env * _obj)
{
	json j_out;
	std::string cipher, decipher;
	cipher = _str;
	decipher = ChangedString(cipher);
	j_out = json::parse(decipher);
	_obj->status = j_out["status"].as<int>();
	_obj->resource->currentCount = j_out["startCount"].as<int>();
	_obj->V.x = j_out["xPos"].as<int>();
	_obj->V.y = j_out["yPos"].as<int>();
}

#endif // !ENVIROMENT_H
