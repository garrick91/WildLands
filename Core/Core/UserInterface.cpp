#include "UserInterface.h"

void UI::InitUI(Graphics * _gfx)
{
	btnClear = new Button(_gfx, 22, 610, 32, 32, L"Textures/ui/btnClear.png", L"Textures/ui/btnClear.png", true);
	btnEc1 = new Button(_gfx, 22, 652, 64, 64, L"Textures/ui/btnEC1.png", L"Textures/ui/btnEC1.png", true);
	btnProv1 = new Button(_gfx, 96, 652, 64, 64, L"Textures/ui/btnProv1.png", L"Textures/ui/btnProv1.png", true);
	btnSoc1 = new Button(_gfx, 170, 652, 64, 64, L"Textures/ui/btnSoc1.png", L"Textures/ui/btnSoc1.png", true);
	btnStep = new Button(_gfx, 1148, 615, 196, 128, L"Textures/ui/btnStep.png", L"Textures/ui/btnStepS.png", true);

	btnWC = new Button(_gfx, 272, 610, 128, 128, L"Textures/ui/btnWC.png", L"Textures/ui/btnWCS.png", false);
	btnQuarry = new Button(_gfx, 410, 610, 128, 128, L"Textures/ui/btnQuarry.png", L"Textures/ui/btnQuarryS.png", false);
	btnSmeltery = new Button(_gfx, 548, 610, 128, 128, L"Textures/ui/btnSmelt.png", L"Textures/ui/btnSmeltS.png", false);
	btnArmory = new Button(_gfx, 686, 610, 128, 128, L"Textures/ui/btnArm.png", L"Textures/ui/btnArmS.png", false);
	btnMints = new Button(_gfx, 824, 610, 128, 128, L"Textures/ui/btnMint.png", L"Textures/ui/btnMintS.png", false);

	btnHunter = new Button(_gfx, 272, 610, 128, 128, L"Textures/ui/btnHunter.png", L"Textures/ui/btnHunterS.png", false);
	btnFarm = new Button(_gfx, 410, 610, 128, 128, L"Textures/ui/btnFarm.png", L"Textures/ui/btnFarmS.png", false);
	btnFiels = new Button(_gfx, 548, 610, 128, 128, L"Textures/ui/btnField.png", L"Textures/ui/btnFieldS.png", false);
	btnMill = new Button(_gfx, 686, 610, 128, 128, L"Textures/ui/btnMill.png", L"Textures/ui/btnMillS.png", false);
	btnBakery = new Button(_gfx, 824, 610, 128, 128, L"Textures/ui/btnBaker.png", L"Textures/ui/btnBakerS.png", false);
	btnBrewery = new Button(_gfx, 962, 610, 128, 128, L"Textures/ui/btnBrewer.png", L"Textures/ui/btnBrewerS.png", false);

	btnTents = new Button(_gfx, 272, 610, 128, 128, L"Textures/ui/btnTents.png", L"Textures/ui/btnTentsS.png", false);
	btnChurch = new Button(_gfx, 410, 610, 128, 128, L"Textures/ui/btnChurch.png", L"Textures/ui/btnChurchS.png", false);
	btnOutpost = new Button(_gfx, 548, 610, 128, 128, L"Textures/ui/btnOutpost.png", L"Textures/ui/btnOutpostS.png", false);
	btnTavern = new Button(_gfx, 686, 610, 128, 128, L"Textures/ui/btnTavern.png", L"Textures/ui/btnTavernS.png", false);
	btnGrave = new Button(_gfx, 824, 610, 128, 128, L"Textures/ui/btnGrave.png", L"Textures/ui/btnGraveS.png", false);
}

void UI::btnRender()
{
	btnClear->Render();
	btnEc1->Render();
	btnProv1->Render();
	btnSoc1->Render();
	btnStep->Render();

	btnWC->Render();
	btnQuarry->Render();
	btnSmeltery->Render();
	btnArmory->Render();
	btnMints->Render();

	btnHunter->Render();
	btnFarm->Render();
	btnFiels->Render();
	btnMill->Render();
	btnBakery->Render();
	btnBrewery->Render();

	btnTents->Render();
	btnChurch->Render();
	btnOutpost->Render();
	btnTavern->Render();
	btnGrave->Render();
	 
}


void UI::UIRelease()
{
	delete btnWC; //лесоруб
		delete btnQuarry;//рудник
		delete btnSmeltery;
		delete btnArmory;
		delete btnMints;

		delete btnHunter; //охотник
		delete btnFarm;
		delete btnFiels;
		delete btnMill;
		delete btnBakery;
		delete btnBrewery;

		delete btnTents; //палатки
		delete btnChurch;
		delete btnOutpost;
		delete btnTavern;
		delete btnGrave;

		delete btnSoc1;
		delete btnProv1;
		delete btnEc1;
		delete btnClear;
		delete btnHelp;
		delete btnPortion;
		delete btnStep;
}

int UI::ActivateEconomic()
{
	btnQuarry->Activate();
	btnWC->Activate();
	btnSmeltery->Activate();
	 btnArmory->Activate();
	 btnMints->Activate();

	return 1;
}

void UI::DiactivateEconomic()
{
	btnQuarry->Diactivate();
	btnWC->Diactivate();
	btnSmeltery->Diactivate();
	btnArmory->Diactivate();
	btnMints->Diactivate();
}


int UI::ActivateProvision()
{
	btnHunter->Activate();
	 btnFarm->Activate();
	 btnFiels->Activate();
	 btnMill->Activate();
	 btnBakery->Activate();
	 btnBrewery->Activate();
	return 2;
}

int UI::ActivateSocial()
{
	btnTents->Activate();
	btnChurch->Activate();
	btnOutpost->Activate();
	btnTavern->Activate();
	btnGrave->Activate();
	return 3;
}

void UI::DiactivateProvision()
{
	btnHunter->Diactivate();
	btnFarm->Diactivate();
	btnFiels->Diactivate();
	btnMill->Diactivate();
	btnBakery->Diactivate();
	btnBrewery->Diactivate();
}
void UI::DiactivateSocial()
{
	btnTents->Diactivate();
	btnChurch->Diactivate();
	btnOutpost->Diactivate();
	btnTavern->Diactivate();
	btnGrave->Diactivate();
}


void UI::DeselectEc(Graphics * _gfx)
{
	btnQuarry->Deselect(_gfx);
	btnWC->Deselect(_gfx);
	btnSmeltery->Deselect(_gfx);
	btnArmory->Deselect(_gfx);
	btnMints->Deselect(_gfx);

	btnStep->Deselect(_gfx);
}

void UI::DeselectProv(Graphics * _gfx)
{
	btnHunter->Deselect(_gfx);
	btnFarm->Deselect(_gfx);
	btnFiels->Deselect(_gfx);
	btnMill->Deselect(_gfx);
	btnBakery->Deselect(_gfx);
	btnBrewery->Deselect(_gfx);

	btnStep->Deselect(_gfx);
}

void UI::DeselectSoc(Graphics * _gfx)
{
	btnTents->Deselect(_gfx);
	btnChurch->Deselect(_gfx);
	btnOutpost->Deselect(_gfx);
	btnTavern->Deselect(_gfx);
	btnGrave->Deselect(_gfx);

	btnStep->Deselect(_gfx);
}