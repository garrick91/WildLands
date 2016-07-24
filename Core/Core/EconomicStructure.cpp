#include "stdafx.h"

#include "EconomicStructure.h"
#include "Map.h"
#include <fstream>


////Äîáû÷à
////øàáëîíû
//template <typename T, typename SI> void Find_T(T _obj, std::list<Enviroment*>* _lst)
//{
//	for (int i = 0; i < (int)(SI->map->ReturnGameMap().size() / 2); i++)
//	{
//		for (int j = 0; j < (int)(SI->map->ReturnGameMap().size() / 2); j++)
//		{
//			if ((SI->map->ReturnGameMap()[i][j]->GetResourcesType() == _obj->type) &&
//				(SI->map->ReturnGameMap()[i][j]->GetPosition().x <= (_obj->coord.x - _obj->workAreaRadius)) &&
//				(SI->map->ReturnGameMap()[i][j]->GetPosition().x >= (_obj->coord.x + _obj->workAreaRadius)) &&
//				(SI->map->ReturnGameMap()[i][j]->GetPosition().y <= (_obj->coord.y - _obj->workAreaRadius)) &&
//				(SI->map->ReturnGameMap()[i][j]->GetPosition().y >= (_obj->coord.y + _obj->workAreaRadius)))
//			{
//				_lst->push_back(SI->map->ReturnGameMap()[i][j]->ReturnEnviroment());
//			}
//		}
//	}
//}
//
//template <typename T> void Action_T(T _obj, std::list<Enviroment*>* _lst, int _resAmount)
//{
//	Enviroment* tmp = new Enviroment();
//	if ((_obj->workStatus == true) && (!_lst->empty()))
//	{
//		for (auto iter = _lst->begin(), end = _lst->end(); iter != end; ++iter)
//		{
//			tmp = *iter;
//			if (tmp->resource->currentCount >= _obj->resIncrease)
//			{
//				tmp->resource->currentCount -= _obj->resIncrease;
//				_resAmount += _obj->resIncrease;
//				break;
//			}
//			else
//			{
//				iter = _lst->erase(iter);
//				end = _lst->end();
//				continue;
//			}
//		}
//	}
//	delete tmp;
//}
//
//
//json InitData(std::string FileName) //ïîäãğóçêà èñõîäíûõ äàííûõ ñ äèñêà
//{
//	json j_out;
//	std::string cipher;
//	std::ifstream fin(FileName);
//	fin >> cipher;
//	fin.close();
//	j_out = json::parse(ChangedString(cipher));
//	return j_out;
//}
//
//
//////********************************** ÓÃÎËÜÍÀß ØÀÕÒÀ **********************************************//
////void  Mine::MakeAction() 
////{
////	if (this->workStatus == true && MainCoal && (MainCoal->resource->currentCount>0))
////	{
////		this->MainCoal->resource->currentCount -= this->resIncrease;
////		SettlementInfo::coalAmount.currentCount += this->resIncrease;
////	}
////}
////
////void Mine::FindCoal ()
////{
////	if (this->type == SettlementInfo::map.ReturnGameMap()[this->coord.x - 1][this->coord.y - 1]->ReturnEnviroment()->resource->type)
////	{
////		this->MainCoal = SettlementInfo::map.ReturnGameMap()[this->coord.x - 1][this->coord.y - 1]->ReturnEnviroment();
////	}
////}
////
////
//
////********************************* ÕÈÆÈÍÀ ËÅÑÎĞÓÁÀ **********************************************//
//
//WoodcutterHut::WoodcutterHut()
//{
//	MainTrees = new std::list <Enviroment*>;
//}
//
//template <typename SI> WoodcutterHut::WoodcutterHut(std::string Filename)
//{
//	json out = InitData(Filename);
//	this->size = out["size"];
//	structureResource = new Resource(0, Human);
//	this->structureResource->currentCount = out["resCount"];
//	this->type = Tree;
//	this->coord.x = 0;
//	this->coord.y = 0;
//	this->resIncrease = out["resIncrease"];
//	buildDate = SI->sumWeek;
//	workStatus = true;
//	workAreaRadius = 0;
//
//	woodCost = out["woodcost"];
//	HumanCost = out["humancost"];
//}
//
//WoodcutterHut::~WoodcutterHut()
//{
//
//}
//
//template <typename SI> bool WoodcutterHut::CanBuild()
//{
//	return true;
//}
//
//int WoodcutterHut::ReturnSize()
//{
//	return 0;
//}
//
//template <typename SI> void WoodcutterHut::Destruction()
//{
//
//}
//
//template <typename SI> void WoodcutterHut::Construction()
//{
//	Find_T <WoodcutterHut*>(this, MainTrees);
//}
//
//template <typename SI> void WoodcutterHut::Action()
//{
//	Action_T <WoodcutterHut*> (this, MainTrees, SI->woodAmount->currentCount);
//}
//
//
//template <typename SI> void WoodcutterHut::Save()
//{
//
//}
//
//template <typename SI> void  WoodcutterHut::Load()
//{
//
//}
//
//void WoodcutterHut::Out()
//{
//
//}

////************************************** ÊÀÌÅÍÎËÎÌÍß ***************************************//
//void Quarry::MakeAction()
//{
//	Action <Quarry*>(this, MainStone, SettlementInfo::stoneAmount.currentCount);
//}
//
//void Quarry::FindStone()
//{
//	Find <Quarry*>(this, MainStone);
//}
//
//
//
//
////**************************************** ÇÎËÎÒÎÄÎÁÛÂÀŞÙÈÉ ĞÓÄÍÈÊ ****************************************//
//void GoldMine::MakeAction()
//{
//	Action <GoldMine*>(this, MainGold, SettlementInfo::goldAmount.currentCount);
//}
//
//void GoldMine::FindGold()
//{
//	Find <GoldMine*>(this, MainGold);
//}
//
////**************************************** ÆÅËÅÇÎÄÎÁÛÂÀŞÙÈÉ ĞÓÄÍÈÊ *****************************************//
//
//void IronMine::MakeAction()
//{
//	Action <IronMine*>(this, MainIron, SettlementInfo::ironAmount.currentCount);
//}
//
//void IronMine::FirnIron()
//{
//	Find <IronMine*>(this, MainIron);
//}
//
//
//
////1 óğîâåíü îáğàáîòêè
//
//void Sawmill::MakeAction()
//{
//	if (this->workStatus == true  &&  SettlementInfo::woodAmount.currentCount && (SettlementInfo::woodAmount.currentCount>0))
//	{
//		SettlementInfo::woodAmount.currentCount -= this->sourceAmount;
//		SettlementInfo::boardsAmount.currentCount += this->resIncrease;
//	}
//}
//
//void Stonemason::MakeAction()
//{
//	if (this->workStatus == true && SettlementInfo::stoneAmount.currentCount && (SettlementInfo::stoneAmount.currentCount>0))
//	{
//		SettlementInfo::stoneAmount.currentCount -= this->sourceAmount;
//		SettlementInfo::bricksAmount.currentCount += this->resIncrease;
//	}
//}
//
//void Smeltery::MakeAction()
//{
//	if (this->workStatus == true && SettlementInfo::ironAmount.currentCount && SettlementInfo::goldAmount.currentCount && (SettlementInfo::ironAmount.currentCount>0) && (SettlementInfo::goldAmount.currentCount>0))
//	{
//		SettlementInfo::ironAmount.currentCount -= this->sourceAmount;
//		SettlementInfo::goldAmount.currentCount -= this->sourceAmount;
//
//		SettlementInfo::ironBarsAmount.currentCount += this->resIncrease;
//		SettlementInfo::goldBarsAmount.currentCount += this->resIncrease;
//	}
//}
//
//
//
////2 óğîâåíü îáğàáîòêè
//
//
//void Armourer::MakeAction()
//{
//	if (this->workStatus == true && SettlementInfo::ironBarsAmount.currentCount && (SettlementInfo::ironBarsAmount.currentCount>0))
//	{
//		SettlementInfo::ironBarsAmount.currentCount -= this->sourceAmount;
//		SettlementInfo::aammunitionAmount.currentCount += this->resIncrease;
//	}
//}
//
//void Mint::MakeAction()
//{
//	if (this->workStatus == true && SettlementInfo::goldBarsAmount.currentCount && (SettlementInfo::goldBarsAmount.currentCount>0))
//	{
//		SettlementInfo::goldBarsAmount.currentCount -= this->sourceAmount;
//		SettlementInfo::coinsAmount.currentCount += this->resIncrease;
//	}
//}