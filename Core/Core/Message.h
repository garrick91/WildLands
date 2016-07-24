#ifndef MESSAGE_H
#define MESSAGE_H
#include "Button.h"
#include "Text.h"
#include "SpriteSheet.h"
#include <string>


class Message {

		//Button *bMas;
		SpriteSheet * texture;
		Text * txt;
		wchar_t * wch;

public:
	Message(HWND hwnd, Graphics * _gfx, wchar_t * wch);
	void Render(int _xPos, int _yPos, Graphics * _gfx);
	~Message();
};

#endif // !MESSAGE_H