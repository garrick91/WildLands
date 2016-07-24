#ifndef STRUCTURE_H
#define STRUCTURE_H


#include <list>
#include "Enviroment.h"


template <typename SI>
class Structure
{
public:
	SpriteSheet *texture;
	int size; //prm
    int	buildDate; //set   ! 
	Coordinates coord; //set   !
	EnviromentType type; //prm
	StructureType sType; //prm
	Resource* structureResource; //prm
	int resIncrease; //prm
	bool workStatus; //set    !
	int workAreaRadius; //prm
	Structure() {};
	~Structure() {};

	StructureType ReturnType() { return sType; }
	Coordinates GetPos() { return coord; }
	virtual bool CanBuild(SI* _obj) { return true; }
	virtual void Find(SI *_obj) {}
	virtual void Construction(SI* _obj) {}
	virtual void Destruction(SI* _obj) {}
	virtual void Action(SI* _obj, Graphics * _gfx) {}
	virtual void InitBD(SI* _obj) {}
	virtual void InitPosition(int _x, int _y) {}
	virtual std::string Save() { return ""; }
	virtual void Load(std::string _str) {}
	virtual void Render(int _xPos, int _yPos) {}

};

inline int ToScreenX(Coordinates _map);

inline int ToScreenY(Coordinates _map);


template <typename ST>
std::string TmpSave(ST * _obj)
{
	json j_in;
	j_in["xPos"] = _obj->coord.x;
	j_in["yPos"] = _obj->coord.y;
	j_in["status"] = _obj->workStatus;
	j_in["buildDate"] = _obj->buildDate;
	std::string decipher = j_in.to_string();
	std::string cipher = ChangedString(decipher);
	return cipher;
}

template <typename ST>
void TmpLoad(ST * _obj, std::string _str)
{
	json j_out;
	std::string cipher, decipher;
	cipher = _str;
	decipher = ChangedString(cipher);
	j_out = json::parse(decipher);
	_obj->workStatus = j_out["status"].as<bool>();
	_obj->coord.x = j_out["xPos"].as<int>();
	_obj->coord.y = j_out["yPos"].as<int>();
	_obj->buildDate = j_out["buildDate"].as<int>();
}

#endif // !STRUCTURE_H