#ifndef  USERINTERFACE_H
#define USERINTERFACE_H
#include "Button.h"
#include <d3d9.h>
#include <d3dx9.h>

class UI
{
public:
	
	Button
		*btnWC, //лесоруб
		*btnQuarry,//рудник
		*btnSmeltery,
		*btnArmory,
		*btnMints,

		*btnHunter, //охотник
		*btnFarm,
		*btnFiels,
		*btnMill,
		*btnBakery,
		*btnBrewery,

		*btnTents, //палатки
		*btnChurch,
		*btnOutpost,
		*btnTavern,
		*btnGrave,

		 *btnSoc1, 
		 *btnProv1, 
		 *btnEc1, 
		 *btnClear,
		 *btnHelp,
		 *btnPortion,
		 *btnStep;

	 UI(Graphics * _gfx) { this->InitUI(_gfx); }
	 ~UI() { this->UIRelease(); }
	 void InitUI(Graphics * _gfx);
	 void UIRelease();
	 void btnRender();
	 int ActivateEconomic();
	 int ActivateProvision();
	 int ActivateSocial();
	 void DiactivateEconomic();
	 void DiactivateProvision();
	 void DiactivateSocial();
	 void DeselectEc(Graphics * _gfx);
	 void DeselectProv(Graphics * _gfx);
	 void DeselectSoc(Graphics * _gfx);
};


#endif // ! USERINTERFACE_H