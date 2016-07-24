#ifndef MENU_H
#define MENU_H
#include "Button.h"



class Menu{
public:
	Button * btnNewGame, *btnSave, *btnLoad, *btnSet, *btnExit, *btnApply, *btnMore, *btn;
	Menu(Graphics * _gfx) { this->InitMenu(_gfx); }
	void RenderMenu();
	void InitMenu(Graphics * _gfx);
	void MenuRelease();

};


class SoundSettings {
public:
	Button * musicPlus, *musicMinus, *soundPlus, *soundMinus, *btnOk;
	SpriteSheet* music, *sounds;
	SoundSettings(Graphics * _gfx) { this->InitSettings(_gfx); }
	void InitSettings(Graphics * _gfx);
	void RenderSettings();
	void SettingsRelease();
};

#endif // !MENU_H