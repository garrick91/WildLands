#include <dinput.h>
#include <fstream>
#include "Coordinates.h"
#include "GameController.h"
#include "UserInterface.h"
#include "Text.h"
#include <cmath>
#include <stdio.h>
#include "SoundClass.h"
#include "mmsystem.h"
#include "Menu.h"
#include "Message.h"
#pragma comment(lib,"Winmm.lib")


#define SPEED 15

Message * m_Msg, *m_Set;
Button * s_Min, *s_Max;

int musicVolume = DSBVOLUME_MAX;
int soundsVolume = DSBVOLUME_MAX;


SoundClass *m_Sound, *s_Tmp;
Menu * gameMenu;
Text * m_Text, *m_Text2, *m_Text3;
int  sessionState = 0;
bool gameState = false;
bool canSet = true;


POINT Pos;
Tree * t;
Block *b, *Choosen;
IDirectInput8 *pDI;
IDirectInputDevice8 *pDIDMouse;
long g_MouseXPos = 0, g_MouseYPos = 0;
UI * m_UI;
int ActiveBranch = 0;
Coordinates camPos;
Graphics* graphics;
SpriteSheet *grass, *house, *tent, *tree, *cow, *back, *ui;
std::vector <Tree*> GameTrees;

void DeleteEnv(std::vector <Tree*> _lst)
{
	
}

inline int ToMapX(int _xPos, int _yPos);
inline int ToMapY(int _xPos, int _yPos);
inline int ToMapX(int _xPos, int _yPos)
{
	float mapX = (_xPos/128 + _yPos/ 64);
	return mapX;
}
inline int ToMapY(int _xPos, int _yPos)
{
	float mapY = (_yPos / 64 - (_xPos / 128));
	return mapY;
}


inline void Replace(Block* _new)
{
	if (Choosen)
	{
		Choosen->Deselect(graphics);
		_new->Select(graphics);
		Choosen = _new;
	}
	else
	{
		_new->Select(graphics);
		Choosen = _new;
	}
}

//функция обработки сообщений
LRESULT CALLBACK  WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_ESCAPE:
			if (sessionState == 0 && gameState == true)
			{
				sessionState = 1;
				m_Sound->Shutdown();
				m_Sound->Initialize(hwnd, "Sound/forest.wav", musicVolume, true);
			}
			else
			{
				sessionState = 0;
				m_Sound->Shutdown();
				m_Sound->Initialize(hwnd, "Sound/menu.wav", musicVolume, true);
			}
			break;
		case 'W':
		case VK_UP:
			camPos.y += 1;
			break;
		case 'S':
		case VK_DOWN:
			camPos.y -= 1;
			break;
		case 'D':
		case VK_RIGHT:
			camPos.x -= 1;
			break;
		case 'A':
		case VK_LEFT:
			camPos.x += 1;
			break;
		case 'M':
			break;
		case VK_ADD:

			if (sessionState == 4)
			{
				
			}
			
			break;
		case VK_SUBTRACT:
			if (sessionState == 4)
			{
				
			}
			break;
		default:
			break;
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		Pos.x = LOWORD(lParam);
		Pos.y = HIWORD(lParam);
		switch (sessionState)
		{
			//-------------------------------------  MENU  ---------------------------------------//
		case 0:
			if (gameMenu->btnNewGame->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnNewGame->Select(graphics);
			}
			else if (gameMenu->btnSave->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnSave->Select(graphics);
			}
			else if (gameMenu->btnLoad->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnLoad->Select(graphics);
			}
			else if (gameMenu->btnExit->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnExit->Select(graphics);
			}
			break;

			//-------------------------------------  INGAME  ---------------------------------------//
		case 1:
			// Сохраняем координаты курсора мыши
			//-------------------------------------  CHOOSE BLOCK  ---------------------------------------//
			if (Pos.x > 0 && Pos.y > 0 && Pos.x < 1121 && Pos.y < 556)
			{
				GameController::ChooseBlock(Pos.x - camPos.x*SPEED, Pos.y - camPos.y*SPEED, graphics);
			
			}
			//-------------------------------------  CLEAR  ---------------------------------------//
			else if (m_UI->btnClear->MyPos(Pos.x, Pos.y))
			{
				GameController::Clear();
			}
			//-------------------------------------  ECONOMIC  ---------------------------------------//
			else if (m_UI->btnEc1->MyPos(Pos.x, Pos.y))
			{
				ActiveBranch = m_UI->ActivateEconomic();
				m_UI->DiactivateProvision();
				m_UI->DiactivateSocial();
			}
			//-------------------------------------  PROVISION  ---------------------------------------//
			else if (m_UI->btnProv1->MyPos(Pos.x, Pos.y))
			{
				ActiveBranch = m_UI->ActivateProvision();
				m_UI->DiactivateEconomic();
				m_UI->DiactivateSocial();
			}
			//-------------------------------------  SOCIAL  ---------------------------------------//
			else if (m_UI->btnSoc1->MyPos(Pos.x, Pos.y))
			{
				ActiveBranch = m_UI->ActivateSocial();
				m_UI->DiactivateProvision();
				m_UI->DiactivateEconomic();
			}
			

			switch (ActiveBranch)
			{
				//-------------------------------------  ECONOMIC  ---------------------------------------//
			case 1:
				if (m_UI->btnWC->MyPos(Pos.x, Pos.y) && m_UI->btnWC->IsHere())
				{
					m_UI->btnWC->Select(graphics);
				}
				else if (m_UI->btnQuarry->MyPos(Pos.x, Pos.y) && m_UI->btnQuarry->IsHere())
				{
					m_UI->btnQuarry->Select(graphics);
				}
				else if (m_UI->btnSmeltery->MyPos(Pos.x, Pos.y) && m_UI->btnSmeltery->IsHere())
				{
					m_UI->btnSmeltery->Select(graphics);
				}
				else if (m_UI->btnArmory->MyPos(Pos.x, Pos.y) && m_UI->btnArmory->IsHere())
				{
					m_UI->btnArmory->Select(graphics);
				}
				else if (m_UI->btnMints->MyPos(Pos.x, Pos.y) && m_UI->btnMints->IsHere())
				{
					m_UI->btnMints->Select(graphics);
				}
				break;
				//-------------------------------------  PROVISION  ---------------------------------------//
			case 2:
				if (m_UI->btnHunter->MyPos(Pos.x, Pos.y) && m_UI->btnHunter->IsHere())
				{
					m_UI->btnHunter->Select(graphics);
				}
				else if (m_UI->btnFarm->MyPos(Pos.x, Pos.y) && m_UI->btnFarm->IsHere())
				{
					m_UI->btnFarm->Select(graphics);
				}
				else if (m_UI->btnFiels->MyPos(Pos.x, Pos.y) && m_UI->btnFiels->IsHere())
				{
					m_UI->btnFiels->Select(graphics);
				}
				else if (m_UI->btnMill->MyPos(Pos.x, Pos.y) && m_UI->btnMill->IsHere())
				{
					m_UI->btnMill->Select(graphics);
				}
				else if (m_UI->btnBakery->MyPos(Pos.x, Pos.y) && m_UI->btnBakery->IsHere())
				{
					m_UI->btnBakery->Select(graphics);
				}
				else if (m_UI->btnBrewery->MyPos(Pos.x, Pos.y) && m_UI->btnBrewery->IsHere())
				{
					m_UI->btnBrewery->Select(graphics);
				}
				break;
				//-------------------------------------  SOCIAL  ---------------------------------------//
			case 3:
				if (m_UI->btnTents->MyPos(Pos.x, Pos.y) && m_UI->btnTents->IsHere())
				{
					m_UI->btnTents->Select(graphics);
				}
				else if (m_UI->btnChurch->MyPos(Pos.x, Pos.y) && m_UI->btnChurch->IsHere())
				{
					m_UI->btnChurch->Select(graphics);
				}
				else if (m_UI->btnOutpost->MyPos(Pos.x, Pos.y) && m_UI->btnOutpost->IsHere())
				{
					m_UI->btnOutpost->Select(graphics);
				}
				else if (m_UI->btnTavern->MyPos(Pos.x, Pos.y) && m_UI->btnTavern->IsHere())
				{
					m_UI->btnTavern->Select(graphics);
				}
				else if (m_UI->btnGrave->MyPos(Pos.x, Pos.y) && m_UI->btnGrave->IsHere())
				{
					m_UI->btnGrave->Select(graphics);
				}
				break;
			}
			if (m_UI->btnStep->MyPos(Pos.x, Pos.y) && m_UI->btnStep->IsHere())
			{
				m_UI->btnStep->Select(graphics);
			}
			break;
			break;
			//-------------------------------------  EXCEPTION  ---------------------------------------//
		case 2:

			break;
		case 3:
			if (Pos.x>300 && Pos.x<800 && Pos.y>300 && Pos.y<550)
				sessionState = 1;
			break;
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		// Сохраняем координаты курсора мыши
		Pos.x = LOWORD(lParam);
		Pos.y = HIWORD(lParam);

		switch (sessionState)
		{
			//-------------------------------------  MENU  ---------------------------------------//
		case 0:
			//-------------------------------------   NEW GAME  ---------------------------------------//
			if (gameMenu->btnNewGame->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnNewGame->Deselect(graphics);
				if (GameController::ReturnSettlement())
				{
					GameController::Release();
				}
				GameController::Init(graphics);
				sessionState = 1;
				gameState = true;
				m_Sound->Shutdown();
				m_Sound->Initialize(hwnd, "Sound/forest.wav", musicVolume ,false);
			}
			//-------------------------------------  SAVE  ---------------------------------------//
			else if (gameMenu->btnSave->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnSave->Deselect(graphics);
				if (gameState == true)
				{
					GameController::Save();
					sessionState == 1;
				}				
			}
			//-------------------------------------   LOAD GAME  ---------------------------------------//
			else if (gameMenu->btnLoad->MyPos(Pos.x, Pos.y))
			{
				gameState == true;
				if (GameController::CheckFiles())
				{
					gameMenu->btnLoad->Deselect(graphics);
					if (GameController::ReturnSettlement())
					{
						GameController::Release();
					}
					GameController::Load(graphics);
					sessionState = 1;
					
				}
				else
				{
					MessageBox(hwnd, "FILES ARE NOT EXIST OR EMPTY", "LOAD ERROR", MB_OK);
				}
				
			}
			else if (gameMenu->btnSet->MyPos(Pos.x, Pos.y))
			{
				m_Msg = new Message(hwnd, graphics, L"VOLUME SETTINGS");
				s_Min = new Button(graphics, 650, 450, 32, 32, L"Textures/ui/btnMinus.png", L"Textures/ui/btnMinus.png", true);
				s_Max = new Button(graphics, 400, 450, 32, 32, L"Textures/ui/btnPlus.png", L"Textures/ui/btnPlus.png", true);
				sessionState = 4;
			}
			else if (gameMenu->btnExit->MyPos(Pos.x, Pos.y))
			{
				gameMenu->btnExit->Deselect(graphics);
				SendMessage(hwnd, WM_CLOSE, 0, 0);
			}
			else
			{
				gameMenu->btnNewGame->Deselect(graphics);
				gameMenu->btnLoad->Deselect(graphics);
				gameMenu->btnSave->Deselect(graphics);
				gameMenu->btnExit->Deselect(graphics);
			}
			break;

			//-------------------------------------  INGAME  ---------------------------------------//
		case 1:
			
			//-------------------------------------  NEXT TURN  ---------------------------------------//
			if (m_UI->btnStep->MyPos(Pos.x, Pos.y) && m_UI->btnStep->IsHere())
			{
				m_UI->btnStep->Deselect(graphics);
				GameController::UpdateSystem(graphics);
				GameController::ReturnSettlement()->currentWeek++;
				if (GameController::ReturnSettlement()->currentWeek == GameController::ReturnSettlement()->targetWeek)
				{
					if (GameController::CheckGoals())
					{
						m_Msg = new Message(hwnd, graphics, L"YOU ARE THE BEST LORD!!! YOU HAVE CREATED A BEAUTIFUL VILLAGE!!!");
						sessionState = 5;
						gameState = false;
					}
					else
					{
						m_Msg = new Message(hwnd, graphics, L" I'TS FAIL! YOU ARE THE WORST LORD!!! YOUR PLASE IS ON THE GALLOWS!!!");
						sessionState = 5;
						gameState = false;
					}
				}
				if (GameController::ReturnSettlement()->totalFear->currentCount > GameController::ReturnSettlement()->targetFear || GameController::ReturnSettlement()->totalPleasure->currentCount < 0)
				{
					m_Msg = new Message(hwnd, graphics, L" I'TS FAIL! YOU ARE THE WORST LORD!!! YOUR PLASE IS ON THE GALLOWS!!!");
					sessionState = 5;
					gameState = false;
				}

			}
			else
			{
				m_UI->btnStep->Deselect(graphics);
				switch (ActiveBranch)
				{
					//-------------------------------------  ECONOMIC BRANCH  ---------------------------------------//
				case 1:
					//-------------------------------------  WOODCUTTER  ---------------------------------------//
					if (m_UI->btnWC->MyPos(Pos.x, Pos.y) && m_UI->btnWC->IsHere())
					{
						m_UI->btnWC->Deselect(graphics);
						WoodcutterHut<SettlementInfo> *temp;
						temp = GameController::Build<WoodcutterHut<SettlementInfo>>("Parameters/WoodcutterHut.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstWoodCut.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", musicVolume, false);
						}
					}
					//-------------------------------------  QUERRY  ---------------------------------------//
					else if (m_UI->btnQuarry->MyPos(Pos.x, Pos.y) && m_UI->btnQuarry->IsHere())
					{
						m_UI->btnQuarry->Deselect(graphics);
						Quarry<SettlementInfo> *temp;
						temp = GameController::Build<Quarry<SettlementInfo>>("Parameters/Quarry.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstQuarries.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/querry.wav", musicVolume, false);
						}

					}
					else if (m_UI->btnSmeltery->MyPos(Pos.x, Pos.y) && m_UI->btnSmeltery->IsHere())
					{
						m_UI->btnSmeltery->Deselect(graphics);
						Smeltery<SettlementInfo> *temp;
						temp = GameController::Build<Smeltery<SettlementInfo>>("Parameters/Smeltery.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstSmelts.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/smelt.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnArmory->MyPos(Pos.x, Pos.y) && m_UI->btnArmory->IsHere())
					{
						m_UI->btnArmory->Deselect(graphics);
						Armourer<SettlementInfo> *temp;
						temp = GameController::Build<Armourer<SettlementInfo>>("Parameters/Armourer.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstArmors.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/armmint.wav", musicVolume, false);
						}
					}
					else if (m_UI->btnMints->MyPos(Pos.x, Pos.y) && m_UI->btnMints->IsHere())
					{
						m_UI->btnMints->Deselect(graphics);
						Mint<SettlementInfo> *temp;
						temp = GameController::Build<Mint<SettlementInfo>>("Parameters/Mint.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstMints.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/armmint.wav", soundsVolume, false);
						}
					}
					else
					{
						m_UI->DeselectEc(graphics);
					}
					break;
					//-------------------------------------  PROVISION  ---------------------------------------//
				case 2:
					//-------------------------------------  HUNTER  ---------------------------------------//
					if (m_UI->btnHunter->MyPos(Pos.x, Pos.y) && m_UI->btnHunter->IsHere())
					{
						m_UI->btnHunter->Deselect(graphics);
						HunterHouse<SettlementInfo> *temp;
						temp = GameController::Build<HunterHouse<SettlementInfo>>("Parameters/HunterHouse.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstHunterHouses.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/hunter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnFarm->MyPos(Pos.x, Pos.y) && m_UI->btnFarm->IsHere())
					{
						m_UI->btnFarm->Deselect(graphics);
						Farm<SettlementInfo> *temp;
						temp = GameController::Build<Farm<SettlementInfo>>("Parameters/Farm.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstFarms.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnFiels->MyPos(Pos.x, Pos.y) && m_UI->btnFiels->IsHere())
					{
						m_UI->btnFiels->Deselect(graphics);
						Field<SettlementInfo> *temp;
						temp = GameController::Build<Field<SettlementInfo>>("Parameters/Field.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstFields.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnMill->MyPos(Pos.x, Pos.y) && m_UI->btnMill->IsHere())
					{
						m_UI->btnMill->Deselect(graphics);
						Mill<SettlementInfo> *temp;
						temp = GameController::Build<Mill<SettlementInfo>>("Parameters/Mill.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstMills.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnBakery->MyPos(Pos.x, Pos.y) && m_UI->btnBakery->IsHere())
					{
						m_UI->btnBakery->Deselect(graphics);
						Bakery<SettlementInfo> *temp;
						temp = GameController::Build<Bakery<SettlementInfo>>("Parameters/Bakery.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstBakerys.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnBrewery->MyPos(Pos.x, Pos.y) && m_UI->btnBrewery->IsHere())
					{
						m_UI->btnBrewery->Deselect(graphics);
						Brewery<SettlementInfo> *temp;
						temp = GameController::Build<Brewery<SettlementInfo>>("Parameters/Brewery.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstBrewerys.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else
					{
						m_UI->DeselectProv(graphics);
					}
					break;
					//-------------------------------------  SOCIAL  ---------------------------------------//
				case 3:
					if (m_UI->btnTents->MyPos(Pos.x, Pos.y) && m_UI->btnTents->IsHere())
					{
						m_UI->btnTents->Deselect(graphics);
						Dugout<SettlementInfo> *temp;
						temp = GameController::Build<Dugout<SettlementInfo>>("Parameters/Tent.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstTents.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/tents.wav", musicVolume,false);
						}
					}
					else if (m_UI->btnChurch->MyPos(Pos.x, Pos.y) && m_UI->btnChurch->IsHere())
					{
						m_UI->btnChurch->Deselect(graphics);
						Church<SettlementInfo> *temp;
						temp = GameController::Build<Church<SettlementInfo>>("Parameters/Church.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstChurchs.push_back(temp);
							s_Tmp->Shutdown();
							s_Tmp->Initialize(hwnd, "Sound/zvon.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnOutpost->MyPos(Pos.x, Pos.y) && m_UI->btnOutpost->IsHere())
					{
						m_UI->btnOutpost->Deselect(graphics);
						Outpost<SettlementInfo> *temp;
						temp = GameController::Build<Outpost<SettlementInfo>>("Parameters/Outpost.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstOutposts.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnTavern->MyPos(Pos.x, Pos.y) && m_UI->btnTavern->IsHere())
					{
						m_UI->btnTavern->Deselect(graphics);
						Tavern<SettlementInfo> *temp;
						temp = GameController::Build<Tavern<SettlementInfo>>("Parameters/Tavern.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstTaverns.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else if (m_UI->btnGrave->MyPos(Pos.x, Pos.y) && m_UI->btnGrave->IsHere())
					{
						m_UI->btnGrave->Deselect(graphics);
						Grave<SettlementInfo> *temp;
						temp = GameController::Build<Grave<SettlementInfo>>("Parameters/Grave.prm", graphics);
						if (temp)
						{
							GameController::ReturnSettlement()->lstGraves.push_back(temp);
							s_Tmp->Shutdown();
							//s_Tmp->Initialize(hwnd, "Sound/woodcutter.wav", soundsVolume, false);
						}
					}
					else
					{
						m_UI->DeselectSoc(graphics);
					}
					break;
				default:
					break;
				}
				break;

				//-------------------------------------  EXCEPTIONS  ---------------------------------------//
		case 4:
			if (s_Min->MyPos(Pos.x, Pos.y) )
			{
				if (musicVolume > DSBVOLUME_MIN)
				{
					musicVolume -= 200;
					//soundsVolume -= 200;
				}
				m_Sound->Shutdown();
				m_Sound->Initialize(hwnd, "Sound/menu.wav", musicVolume, true);	
			}
			if (s_Max->MyPos(Pos.x, Pos.y))
			{
				if (musicVolume < DSBVOLUME_MAX)
				{
					musicVolume += 200;
					//soundsVolume += 200;
				}
				m_Sound->Shutdown();
				m_Sound->Initialize(hwnd, "Sound/menu.wav", musicVolume, true);
			}
			break;
			}
			break;

		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		Pos.x = LOWORD(lParam);
		Pos.y = HIWORD(lParam);
		switch (sessionState)
		{
			//-------------------------------------  MENU  ---------------------------------------//
		case 0:

			//-------------------------------------  INGAME  ---------------------------------------//
		case 1:
			// Сохраняем координаты курсора мыши
			//-------------------------------------  CHOOSE BLOCK  ---------------------------------------//
			switch (ActiveBranch)
			{
				//-------------------------------------  ECONOMIC  ---------------------------------------//
			case 1:
				if (m_UI->btnWC->MyPos(Pos.x, Pos.y) && m_UI->btnWC->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Woodcutter's house. It cost 6 wood and 1 free human. Every week it give 4 wood.");
					sessionState = 3;
				}
				else if (m_UI->btnQuarry->MyPos(Pos.x, Pos.y) && m_UI->btnQuarry->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Quarry. It cost 10 wood and 2 free human. Every week it give 2 stone, 1 iron and 1 gold.");
					sessionState = 3;
				}
				else if (m_UI->btnSmeltery->MyPos(Pos.x, Pos.y) && m_UI->btnSmeltery->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Smeltery. It cost 10 stone, 5 wood and 1 free human. Every week it give 3 iron bars and 3 gold bars.");
					sessionState = 3;
				}
				else if (m_UI->btnArmory->MyPos(Pos.x, Pos.y) && m_UI->btnArmory->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Armourer. It cost 20 wood and 1 free human. Every week it converte 2 iron bars into 1 armor.");
					sessionState = 3;
				}
				else if (m_UI->btnMints->MyPos(Pos.x, Pos.y) && m_UI->btnMints->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Armourer. It cost 20 wood and 1 free human. Every week it converte 2 gold bars into 10 coins.");
					sessionState = 3;
				}
				break;
				//-------------------------------------  PROVISION  ---------------------------------------//
			case 2:
				if (m_UI->btnHunter->MyPos(Pos.x, Pos.y) && m_UI->btnHunter->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Hunter's house. It cost 12 wood and 1 free human. Every week it give 12 meal.");
					sessionState = 3;
				}
				else if (m_UI->btnFarm->MyPos(Pos.x, Pos.y) && m_UI->btnFarm->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Farm. It cost 6 wood and 1 free human. Every week it give 30 meal. It must be built near the fruit trees");
					sessionState = 3;
				}
				else if (m_UI->btnFiels->MyPos(Pos.x, Pos.y) && m_UI->btnFiels->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Fields. It cost 16 wood. Every week it give 3 wheat grains and 3 humulus.");
					sessionState = 3;
				}
				else if (m_UI->btnMill->MyPos(Pos.x, Pos.y) && m_UI->btnMill->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Mill. It cost 16 wood and 1 free human. Every week it convert 6 wheat grains to 24 flour.");
					sessionState = 3;
				}
				else if (m_UI->btnBakery->MyPos(Pos.x, Pos.y) && m_UI->btnBakery->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Bakery. It cost 25 wood and 1 free human. Every week it convert 30 flour to 50 meal.");
					sessionState = 3;
				}
				else if (m_UI->btnBrewery->MyPos(Pos.x, Pos.y) && m_UI->btnBrewery->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Brewery. It cost 20 wood and 1 free human. Every week it convert 6 humulus to 18 alcohol.");
					sessionState = 3;
				}
				break;
			case 3:
				if (m_UI->btnTents->MyPos(Pos.x, Pos.y) && m_UI->btnTents->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Tent. It cost 7 wood and give 2 human once.");
					sessionState = 3;
				}
				else if (m_UI->btnChurch->MyPos(Pos.x, Pos.y) && m_UI->btnChurch->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Church. It cost 8 stone and convert 20 coins and 4 alcohol to 5 religion.");
					sessionState = 3;
				}
				else if (m_UI->btnOutpost->MyPos(Pos.x, Pos.y) && m_UI->btnOutpost->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Outpost. It cost 14 stone and give -5 fear for 1 arm.");
					sessionState = 3;
				}
				else if (m_UI->btnTavern->MyPos(Pos.x, Pos.y) && m_UI->btnTavern->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Tavern. It cost 10 stone and give +5 to pleasure fear for 4 alcohol.");
					sessionState = 3;
				}
				else if (m_UI->btnGrave->MyPos(Pos.x, Pos.y) && m_UI->btnGrave->IsHere())
				{
					m_Msg = new Message(hwnd, graphics, L"Graveyard. It cost 4 stone and give 10 to religion and 3 to fear.");
					sessionState = 3;
				}
				break;
				//-------------------------------------  SOCIAL  ---------------------------------------//
			}
		case 3:

			break;
		}
	}
	break;
	

	default:
		return (DefWindowProc(hwnd, msg, wParam, lParam));
		break;
	}
	return 0;
}

//входная точка приложения
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR LpCmdLine, int nCmdShow)
{
	HWND hwnd; //дескриптор окна
	MSG msg; // идентификатор сообщения
	WNDCLASSEX wc; //класс окна

				   //определяем класс окна
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW | CS_OWNDC | CS_DBLCLKS;
	wc.lpfnWndProc = WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "WINDOWCLASS";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//регистрирую класс
	if (!RegisterClassEx(&wc))
		return 0;
	RECT rect = { 0,0, 1366, 768 };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);


	//создаю окно после регистрации
	hwnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "WINDOWCLASS", "WILDLANDS", WS_OVERLAPPEDWINDOW | WS_VISIBLE,-10,-30, rect.right - rect.left, rect.bottom - rect.top, NULL, NULL, hInstance, NULL);
	if (hwnd == NULL)
	{
		return -1;
	}

	graphics = new Graphics();
	if (!graphics->InitGraphics(hwnd))
	{
		delete graphics;
		return -1;
	}

	ShowWindow(hwnd, SW_SHOWDEFAULT);

	m_Sound = new SoundClass();
	s_Tmp = new SoundClass();
	m_Sound->Initialize(hwnd, "Sound/menu.wav", musicVolume,true);


	//--------------------
	Graphics* gfx = graphics;
	Coordinates c;

	gameMenu = new Menu(gfx);
	m_UI = new UI(graphics);

	m_Text = new Text();
	m_Text->InitText();
	m_Text->CreateTextFormat();
	m_Text->SetTextAlignment();
	m_Text->CreateDeviceResources(hwnd, graphics->GetRenderTarget(),D2D1::ColorF::White);



	m_Text2 = new Text();
	m_Text2->InitText();
	m_Text2->CreateTextFormat();
	m_Text2->SetTextAlignment();
	m_Text2->CreateDeviceResources(hwnd, graphics->GetRenderTarget(), D2D1::ColorF::Black);

	m_Text3 = new Text();
	m_Text3->InitText();
	m_Text3->CreateTextFormat();
	m_Text3->SetTextAlignment();
	m_Text3->CreateDeviceResources(hwnd, graphics->GetRenderTarget(), D2D1::ColorF::Red);


	SpriteSheet *up, *right, *bottom, *back, *backMenu;
	backMenu = new SpriteSheet(L"Textures/ui/menu_back.png", gfx, 1366, 768);
	back = new SpriteSheet(L"Textures/ui/back.png", gfx, 1366, 768);
	up = new SpriteSheet(L"Textures/ui/up.png", gfx, 1366, 74);
	right = new SpriteSheet(L"Textures/ui/right.png", gfx, 246, 555);
	bottom = new SpriteSheet(L"Textures/ui/bottom.png", gfx, 1366, 139);
	camPos.x = 40;
	camPos.y = -16;
	

	wchar_t m_name[256];


	//	PlaySound("sound1.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
	
	msg.message = WM_NULL;
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			DispatchMessage(&msg);
		else
		{
			graphics->BeginDraw();
			graphics->ClearScreen(0, 0, 0);
			int x = 50;
			int y = 175;
			switch (sessionState)
			{
			case 0:

				backMenu->Draw(0, 0);
				gameMenu->RenderMenu();

				break;
			case 1:
				back->Draw(0, 0);

				GameController::Render(camPos.x*SPEED, camPos.y*SPEED);
				GameController::Update();

				right->Draw(1120, 74);
				up->Draw(0, 0);
				bottom->Draw(0, 600);
				m_UI->btnRender();



				//top text

				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->woodAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Wood:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->stoneAmount->currentCount);
				wprintf(L"%s\n", m_name);
				x += 100;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Stone:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->ironAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Iron:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->goldAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Gold:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->mealAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Meal:");
				x += 90;

				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->AlcoholAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Alcohol:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);

				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->humanAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Human:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);




				//SECON LINE
				x = 50;

				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->wheatGrainsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Wheat:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->humulusAmount->currentCount);
				wprintf(L"%s\n", m_name);
				x += 100;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Humulus:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->ironBarsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Iron bars:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->goldBarsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Gold bars:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->flourAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Flour:");
				x += 90;

				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->aammunitionAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Amunition:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);

				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->coinsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Coins:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);


				//right text
				y -= 30;
				m_Text2->Drawtext(1200, y, graphics->GetRenderTarget(), L"CURRENT:");
				y += 30;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->currentWeek);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Week:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalHumans->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Population:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalReligion->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Religion:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalFear->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Fear:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalPleasure->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Pleasure:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);


				y += 38;
				m_Text3->Drawtext(1200, y, graphics->GetRenderTarget(), L"GOALS:");
				y += 30;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetWeek);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Week:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 35;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetPopulation);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Population:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetReligion);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Religion:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetFear);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Fear:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 33;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetPleasure);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Pleasure:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				break;
			case 3:
				back->Draw(0, 0);

				GameController::Render(camPos.x*SPEED, camPos.y*SPEED);
				GameController::Update();

				right->Draw(1120, 74);
				up->Draw(0, 0);
				bottom->Draw(0, 600);
				m_UI->btnRender();



				//top text

				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->woodAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Wood:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->stoneAmount->currentCount);
				wprintf(L"%s\n", m_name);
				x += 100;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Stone:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->ironAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Iron:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->goldAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Gold:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->mealAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Meal:");
				x += 90;

				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->AlcoholAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Alcohol:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);

				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->humanAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), L"Human:");
				x += 90;
				m_Text->Drawtext(x, -10, graphics->GetRenderTarget(), m_name);




				//SECON LINE
				x = 50;

				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->wheatGrainsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Wheat:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->humulusAmount->currentCount);
				wprintf(L"%s\n", m_name);
				x += 100;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Humulus:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->ironBarsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Iron bars:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->goldBarsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Gold bars:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->flourAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Flour:");
				x += 90;

				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);
				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->aammunitionAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Amunition:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);

				x += 100;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->coinsAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), L"Coins:");
				x += 90;
				m_Text->Drawtext(x, 30, graphics->GetRenderTarget(), m_name);


				//right text
				y -= 30;
				m_Text2->Drawtext(1200, y, graphics->GetRenderTarget(), L"CURRENT:");
				y += 30;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->currentWeek);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Week:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->humanAmount->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Population:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalReligion->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Religion:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalFear->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Fear:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->totalPleasure->currentCount);
				wprintf(L"%s\n", m_name);
				m_Text2->Drawtext(1150, y, graphics->GetRenderTarget(), L"Pleasure:");
				m_Text2->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);


				y += 38;
				m_Text3->Drawtext(1200, y, graphics->GetRenderTarget(), L"GOALS:");
				y += 30;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetWeek);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Week:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 35;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetPopulation);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Population:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetReligion);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Religion:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 38;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetFear);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Fear:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);
				y += 33;
				swprintf_s(m_name, L"%d", GameController::ReturnSettlement()->targetPleasure);
				wprintf(L"%s\n", m_name);
				m_Text3->Drawtext(1150, y, graphics->GetRenderTarget(), L"Pleasure:");
				m_Text3->Drawtext(1250, y, graphics->GetRenderTarget(), m_name);

				if (m_Msg)
				{
					m_Msg->Render(300, 300, gfx);
				}
				break;
			case 4:

				backMenu->Draw(0, 0);
				gameMenu->RenderMenu();

				if (m_Msg)
				{
					m_Msg->Render(300, 300, gfx);
				}
				if (s_Min)
				{
					s_Min->Render();
				}
				if (s_Max)
				{
					s_Max->Render();
				}
				break;
			case 5:

				backMenu->Draw(0, 0);
				gameMenu->RenderMenu();

				if (m_Msg)
				{
					m_Msg->Render(400, 300, gfx);
				}
				break;


			default:
				break;
			}
			graphics->EndDraw();
		}
	}
	GameController::Release();
	m_Text->DiscardResources();
	delete m_UI;
	delete graphics;
	return 0;
}