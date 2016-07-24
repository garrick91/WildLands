#include "Block.h"


Block::Block(Graphics * _gfx){

	structure = NULL;
	resourceSource = NULL;
	blockTexture = new SpriteSheet(L"Textures/Block/grass.png", _gfx, 128, 80);
	accessibility = true;
}


void Block::Select(Graphics * _gfx){

	if (blockEnvType != Fish){

		delete blockTexture;
		blockTexture = new SpriteSheet(L"Textures/Block/grass_select.png", _gfx, 128, 80);
		isSelected = true;
	}
	else{

		delete blockTexture;
		blockTexture = new SpriteSheet(L"Textures/Block/water_select.png", _gfx, 128, 80);
		isSelected = true;
	}
}

void Block::Deselect(Graphics * _gfx){

	if (blockEnvType != Fish){

		delete blockTexture;
		blockTexture = new SpriteSheet(L"Textures/Block/grass.png", _gfx, 128, 80);
		isSelected = false;
	}
	else{

		delete blockTexture;
		blockTexture = new SpriteSheet(L"Textures/Block/water.png", _gfx, 128, 80);
		isSelected = false;
	}
}

Block ::~Block(){

	structure = nullptr;
	resourceSource = nullptr;
}


bool Block::Check(){

	return accessibility;
}


EnviromentType  Block::GetResourcesType(){

	if (resourceSource)
		return blockEnvType;
}


std::string  Block::GetStructureType(){

	if (structure)
		return (std::string)typeid(structure).name();
}


void Block::AddBlock(Coordinates newPosition){

	coordinates.x = newPosition.x;
	coordinates.y = newPosition.y;
}


Coordinates Block::GetPosition(){
	return coordinates;
}


inline int ToScreenX(Coordinates _map){

	int screenX = (_map.x - _map.y) * 64;
	return screenX;
}

inline int ToScreenY(Coordinates _map){

	int screenY = (_map.x + _map.y) * 32;
	return screenY;
}

void Block::RenderBlock(int _xPos, int _yPos){

	blockTexture->Draw(ToScreenX(coordinates) + _xPos, ToScreenY(coordinates) + _yPos);
	screen.x=ToScreenX(coordinates) + _xPos;
	screen.y= ToScreenY(coordinates) + _yPos;
}

bool Block::MyDot(int _xPos, int _yPos){

	Coordinates A, B, C, D, //вершини ромбу
		Q, //центр ромбу
		U, V, //одиничні вектори
		W, // ветор у сторону точки
		P; //точка

	P.x = _xPos;
	P.y = _yPos;
	/*
				  D
				- | -
		   -	  |		-
		-		  | 		-
     A------------Q------------C
	    -	      | 		-
		   -	  | 	-
		       -  | -  
				  B
	*/
	//ініціалізація вершин ромбу
	//D
	D.x = ToScreenX(coordinates)+64;
	D.y = ToScreenY(coordinates);
	//B
	B.x = D.x;
	B.y = D.y + 64;
	//A
	A.x = D.x - 64;
	A.y = D.y + 32;
	//C
	C.x = D.x + 64;
	C.y = A.y;

	//Q - центр ромба
	Q.x = (A.x + C.x) / 2;
	Q.y = A.y;

	int a, b; //половини діагоналей

	a = 64;
	b = 32;

	U.x = (C.x - A.x) / (2 * a);
	U.y = (C.y - A.y) / (2 * a);

	V.x = (D.x- B.x) / (2 * b);
	V.y = (D.y - B.y) / (2 * b);

	W.x = P.x - Q.x;
	W.y = P.y - Q.y;

	double xabs, yabs;
	xabs = std::abs(W.x*U.x + W.y*U.y);
	yabs = std::abs(W.x*V.x + W.y*V.y);

	if ((xabs / a + yabs / b) <= 1){

		return true;
	}
	else{

		return false;
	}
}


void Block::Clear(){

	this->blockEnvType = None;
	this->structureType = StNone;
	this->structure = NULL;
	this->resourceSource = NULL;
	this->accessibility = true;
}
