#include "Button.h"

Button::Button(Graphics * _gfx, int xPos, int yPos, int _sizeX, int _sizeY, wchar_t * _texture, wchar_t * _textureS, bool _status)
{
	source = _texture;
	selected = _textureS;
	status = _status;
	btnSizeY = _sizeY;
	btnSizeX = _sizeX;
	btnPosition.x = xPos;
	btnPosition.y = yPos;
	btnRect.left = btnPosition.x;
	btnRect.right = btnPosition.x+ btnSizeX;
	btnRect.top = btnPosition.y;
	btnRect.bottom = btnPosition.y+ btnSizeY;
	btnTexture = new SpriteSheet(source, _gfx);
	
}

bool Button::MyPos(int _xPos, int _yPos)
{
	if (_xPos <= btnRect.right && _xPos >= btnRect.left && _yPos >= btnRect.top && _yPos <= btnRect.bottom)
	{
		return true;
	}
	else
	{
		return false;
	}
}
