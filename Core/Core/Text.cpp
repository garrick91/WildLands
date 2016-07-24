#include "Text.h"



int Text::InitText() {
	HRESULT hr = (DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&writeFactory)));

	return 0;
}

void Text::CreateTextFormat() {
	HRESULT hr = writeFactory->CreateTextFormat(
		L"Gabriola",                // Font family name.
		NULL,                       // Font collection (NULL sets it to use the system font collection).
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		25.0f,
		L"en-us",
		&textFormat
	);
}

void Text::SetTextAlignment() {
	HRESULT hr = textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	hr = textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
}

void Text::CreateDeviceResources(HWND hwnd, ID2D1RenderTarget* rt, D2D1::ColorF::Enum _color)
{
	RECT rc;
	GetClientRect(hwnd, &rc);

	D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

	HRESULT hr = rt->CreateSolidColorBrush(
		D2D1::ColorF(_color),
		&blackBrush
	);
}

void Text::DiscardResources()
{
	blackBrush->Release();
}

void Text::Drawtext(int x, int y, ID2D1RenderTarget* rt, wchar_t * _text)
{
	lenght = (UINT32)wcslen(_text);

	D2D1_RECT_F layoutRect = D2D1::RectF(
		static_cast<FLOAT>(x),
		static_cast<FLOAT>(y),
		static_cast<FLOAT>(x + 400),
		static_cast<FLOAT>(y + 15)
	);
	rt->DrawText(
		_text,        // The string to render.
		lenght,    // The string's length.
		textFormat,    // The text format.
		layoutRect,       // The region of the window where the text will be rendered.
		blackBrush     // The brush used to draw the text.
	);

}