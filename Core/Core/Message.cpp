#include "Message.h"

Message::Message(HWND hwnd, Graphics * _gfx, wchar_t * _wch)
{
	texture = new SpriteSheet(L"Textures/ui/exception.png", _gfx, 500, 250);
	txt = new Text();
	txt->InitText();
	txt->CreateTextFormat();
	txt->SetTextAlignment();
	txt->CreateDeviceResources(hwnd, _gfx->GetRenderTarget(), D2D1::ColorF::White);
	wch = _wch;
}

void Message::Render(int _xPos, int _yPos, Graphics * _gfx)
{
	texture->Draw(_xPos, _yPos);
	txt->Drawtext(_xPos+50, _yPos+50, _gfx->GetRenderTarget(), wch);
}

Message::~Message()
{
	txt->DiscardResources();
	delete txt;
	delete texture;
	delete wch;
}