#ifndef TEXT_H
#define TEXT_H

#include <d2d1.h>
#include <DWrite.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib") 

class Text
{
	IDWriteFactory * writeFactory;
	IDWriteTextFormat * textFormat;
	const wchar_t* text;
	UINT32 lenght;
	ID2D1SolidColorBrush* blackBrush;

public:
	int InitText();
	void CreateTextFormat();
	void SetTextAlignment();
	void CreateDeviceResources(HWND hwnd, ID2D1RenderTarget* rt, D2D1::ColorF::Enum _color);
	void DiscardResources();
	void Drawtext(int x, int y, ID2D1RenderTarget* rt, wchar_t * _text);

};
#endif