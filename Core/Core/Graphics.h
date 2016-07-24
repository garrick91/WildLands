#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>
#include <d2d1.h>

class  Graphics
{
public:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

	Graphics();
	~Graphics();


	bool InitGraphics(HWND hwnd);
	ID2D1RenderTarget* GetRenderTarget()
	{
		return renderTarget;
	}
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
};

#endif // !GRAPHICS_H