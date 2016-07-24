#include "Menu.h"

void Menu::InitMenu(Graphics *_gfx)
{
	btnNewGame = new Button(_gfx, 70, 245, 256, 40, L"Textures/ui/newSettlement.png", L"Textures/ui/newSettlementS.png", true);
	btnSave = new Button(_gfx, 70, 300, 256, 40, L"Textures/ui/saveSet.png", L"Textures/ui/saveSetS.png", true);
	btnLoad = new Button(_gfx, 70, 355, 256, 40, L"Textures/ui/loadSet.png", L"Textures/ui/loadSetS.png", true);
	btnSet = new Button(_gfx, 70, 410, 256, 40, L"Textures/ui/setSet.png", L"Textures/ui/setSetS.png", true);
	btnExit = new Button(_gfx, 70, 465, 256, 40, L"Textures/ui/exit.png", L"Textures/ui/exitS.png", true);
}

void Menu::RenderMenu()
{
	btnNewGame->Render();
	btnSave->Render();
	btnLoad->Render();
	btnSet->Render();
	btnExit->Render();
}

void Menu::MenuRelease()
{
	delete	btnNewGame;
    delete	btnSave;
    delete	btnLoad;
    delete	btnSet;
    delete	btnExit;
}


