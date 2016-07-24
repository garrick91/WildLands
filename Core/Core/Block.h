#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <string>
#include <typeinfo>
#include "Types.h"
#include "Coordinates.h"
#include "SpriteSheet.h"
#include "Graphics.h"
#include <string>

#include "jsoncons\json.hpp"
using jsoncons::json;
using jsoncons::json_serializer;
using jsoncons::json_deserializer;

class  Block{
	Coordinates coordinates; //координати блоку на мапі
	void* structure; //вказівник на будівлю
	void* resourceSource; //вказівник на об'єкт оточення
	BlockBackground Background; //тип текстури
	SpriteSheet *blockTexture; //текстура блоку
	bool accessibility; //змінна для перевірки блоку на доступність
public:
	bool isSelected; //змінна для перевірки стану блоку (обраний чи ні)
	EnviromentType blockEnvType; //типо оточення, що містить блок
	StructureType structureType; //тип будівлі, що містить блок
	Coordinates screen; //екранні координати блоку
	Block(Graphics * _gfx);
	void Select(Graphics * _gfx);
	void Deselect(Graphics * _gfx);
	~Block();

	//перевірка на можливість будівництва
	bool Check (); 

	//повертає тип об'єкту оточення
	EnviromentType GetResourcesType(); 

	//повертає у вигляді строки тип будівлі
	std::string GetStructureType(); 

	//повертає позицію блоку на мапі
	Coordinates GetPosition();

	//задає позицію блоку на мапі
	void AddBlock(Coordinates newPosition); 

	//рендеринг блоку
	void RenderBlock(int _xPos, int _yPos);

	//встановити об'єкт оточення на блок
	template <typename ENV> void LocateEnviroment(ENV *_env, Graphics * _gfx);

	//повернути на блок будівлю
	template <typename STR> void BackStructure(STR *_str);

	//встановити будівлю на блок
	template <typename STR> void LocateStructure(STR *_str);

	//повернути вказівник на об'єкт оточення
	void* ReturnEnviroment() { return this->resourceSource; }

	//повернути вказівник на структуру
	void* ReturnStructure() { return this->structure; }

	//перевірити, чи належить точка блоку
	bool MyDot(int _xPos, int _yPos);

	//очистити блок
	void Clear();

	//зберегти дані блоку
	std::string SaveBlock();
};



template <typename ENV>
void  Block ::LocateEnviroment(ENV *_env, Graphics * _gfx){

	if (_env->envType != Fish){

		this->resourceSource = _env;
		blockEnvType = _env->envType;
		accessibility = false;
		_env->ChoosePosition(this->coordinates.x, this->coordinates.y);
	}
	else{

		delete blockTexture;
		blockTexture = new SpriteSheet(L"Textures/Block/water.png", _gfx, 128, 80);
		this->resourceSource = _env;
		blockEnvType = _env->envType;
		accessibility = false;
		_env->ChoosePosition(this->coordinates.x, this->coordinates.y);
	}
	
}

template <typename STR>
void Block::LocateStructure(STR *_str){

	this->structureType = _str->ReturnType();
	this->structure = _str;
	accessibility = false;
	_str->InitPosition(this->coordinates.x, this->coordinates.y);
}


template <typename STR>
void Block::BackStructure(STR *_str){

	this->structureType = _str->ReturnType();
	this->structure = _str;
	accessibility = false;
	//_str->InitPosition(this->coordinates.x, this->coordinates.y);
}

#endif // !BLOCK_H
