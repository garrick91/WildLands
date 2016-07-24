#ifndef  SPRITESHEET_H
#define SPRITESHEET_H

#include "Graphics.h" 
#include <wincodec.h> // Component (WIC) хедер для декодирования изображения из файла

class SpriteSheet
{

	Graphics* gfx; //указатель на графический класс
	ID2D1Bitmap* bmp; //загружает файл и конвертирует в direct2d формат
public:
	float frame;
	int spriteWidth, spriteHeight, spritesAccross;

	SpriteSheet(wchar_t* filename, Graphics* gfx);
	SpriteSheet(wchar_t* filename, Graphics* gfx, int spriteWidth, int spriteHeight);

	~SpriteSheet();

	//отрисовуем растр в цель визуализации
	void Draw();
	void Draw(int x, int y);
	void DrawAnimation(float x, float y);
	void Update();
};

#endif