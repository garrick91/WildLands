#ifndef GAMEUI_H
#define GAMEUI_H

#include "SpriteSheet.h"
#include "Coordinates.h"

struct Button
{
	Coordinates position;
	SpriteSheet *btnTexture;
	Button(int _xPos, int _yPos) {};
};

#endif