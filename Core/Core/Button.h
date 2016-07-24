#ifndef  BUTTON_H
#define BUTTON_H

#include "Coordinates.h"
#include "SpriteSheet.h"
#include "Types.h"


class Button
{
	RECT btnRect;
	Coordinates btnPosition;
	int btnSizeX, btnSizeY;
	SpriteSheet * btnTexture;
	bool status;
	wchar_t * source, *selected;
public:
	Button(Graphics * _gfx, int xPos, int yPos, int _sizeX, int _sizeY, wchar_t * _texture, wchar_t * _textureS, bool _status);
	~Button(){ delete btnTexture; }
	bool MyPos(int _xPos, int _yPos);
	void Select(Graphics * _gfx) { delete btnTexture; btnTexture = new SpriteSheet(selected, _gfx, btnSizeX, btnSizeY); }
	void Deselect(Graphics * _gfx) { delete btnTexture; btnTexture = new SpriteSheet(source, _gfx, btnSizeX, btnSizeY); }
	void Render() { if (status == true) { btnTexture->Draw(btnPosition.x, btnPosition.y);} }
	void Activate() { status = true; }
	void Diactivate() { status = false; }
	bool IsHere() { return status; }
};
#endif // ! BUTTON_H