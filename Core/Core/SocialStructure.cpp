#include "SocialStructure.h"
#include "stddef.h"




//************************************************************ÿ¿¡ÀŒÕS***************************************************************************************************************************************************************************************//
//template <typename SI> void ActionTemp(double _foodCoef, double _religionCoef, double _fearCoef, double _enlightCoef, int _residents, int _PFP, FoodPortion _portion, Resource* _religion, Resource* _fear, Resource* _enlight, Resource* _pleasure, SI* _obj)
//{
//	if (_religion && _fear && _enlight && _pleasure && _obj->mealAmount  && _obj->mealAmount->currentCount > (int)(_foodCoef *_PFP*_residents*_portion))
//	{
//		_obj->mealAmount->currentCount -= (int)(_foodCoef *_PFP*_residents*_portion);
//		_pleasure->currentCount = (int)(_foodCoef*_residents * _PFP * (int)_portion + _religionCoef*_religion->currentCount+ _enlightCoef*_enlight->currentCount - _fearCoef*_fear->currentCount);
//		_obj->totalPleasure->currentCount += _pleasure->currentCount;
//		_pleasure->currentCount = 0;
//	}
//	else
//	{
//		_pleasure->currentCount = (int)(_religionCoef*_religion->currentCount + _enlightCoef*_enlight->currentCount - _fearCoef*_fear->currentCount - _foodCoef*_residents * _PFP * _portion);
//		_obj->totalPleasure->currentCount += _pleasure->currentCount;
//		_pleasure->currentCount = 0;
//	}
//}
//
//
//json InitData(std::string FileName) //ÔÓ‰„ÛÁÍ‡ ËÒıÓ‰Ì˚ı ‰‡ÌÌ˚ı Ò ‰ËÒÍ‡
//{
//	json j_out;
//	std::string cipher;
//	std::ifstream fin(FileName);
//	fin >> cipher;
//	fin.close();
//	j_out = json::parse(ChangedString(cipher));
//	return j_out;
//}




//************************************************************************   «≈ÃÀﬂÕ ¿   *******************************************************************************************************************************************************************//
//template <typename SI>
//Dugout<SI>::Dugout()
//{
//	structureResource = new Resource(0, Human);
//	MainReligion = new Resource(0, Religion);
//	MainFear = new Resource(0, Fear);
//	MainEnlight = new Resource(0, Enlightenment);
//}
//template <typename SI>
// Dugout<SI>::Dugout(std::string FileName)
//{
//	json out = InitData(FileName);
//	this->size = out["size"];
//	structureResource = new Resource(0, Human);
//	this->structureResource ->currentCount = out ["resCount"];
//	numOfResidents = structureResource->currentCount;
//	this->coord.x = 0;
//	this->coord.y = 0;
//	this->resIncrease = out["resIncrease"];
//	workStatus = true;
//	workAreaRadius = 0;
//
//	woodCost = out["woodcost"];
//	firewood = out["firewood"];
//	pleasureMulct = out["mulct"];
//	MainReligion = new Resource(0, Religion);
//	MainFear = new Resource(0, Fear);
//	MainEnlight = new Resource(0, Enlightenment);
//	portion = Normal;
//}
//
//template <typename SI>
//Dugout<SI>::Dugout(int _size, int _x, int _y, int _resCoutn, ResourceType _type, int _woodCost, int _firewood, int _mulct, FoodPortion _portion, int _increase, int _area, bool _status, int _relCount, ResourceType _rel, int _fearCount, ResourceType _fear)
//{
//	this->size = _size;
//	this->coord.x = (float) _x; 
//	this->coord.y = (float) _y;
//	this->structureResource = new Resource(_resCoutn, _type);
//	numOfResidents = structureResource->currentCount;
//	woodCost = _woodCost;
//	firewood = _firewood;
//	pleasureMulct = _mulct;
//	portion = _portion;
//	this->resIncrease = _increase;
//	this->workAreaRadius = _area;
//	this->workStatus = _status;
//	MainReligion = new Resource(_relCount, _rel);
//	MainFear = new Resource(_fearCount, _fear);
//}
//template <typename SI>
//Dugout<SI>::~Dugout()
//{
//	delete MainFear;
//	delete MainReligion;
//	delete structureResource;
//}
//
//
//template <typename SI> 
//void Dugout<SI>::Action(SI* _obj)
//{
//	ActionTemp<SI>(0.06, 0.2, 0.1, 0.0, this->numOfResidents, 7, this->portion, this->MainReligion, this->MainFear, this->MainEnlight, this->structureResource, _obj);
//}
//
//template <typename SI> 
//void Dugout<SI>::Construction(SI* _obj)
//{
//	_obj->woodAmount->currentCount -= woodCost;
//	_obj->humanAmount->currentCount += numOfResidents;
//}
//
//template <typename SI> 
//void Dugout<SI>::Destruction(SI* _obj)
//{
//	_obj->humanAmount->currentCount -= numOfResidents;
//	if (_obj->sumWeek == buildDate)
//	{
//		_obj->woodAmount->currentCount += (int) (0.75*woodCost);
//	}
//	else
//	{
//		_obj->woodAmount->currentCount += (int) (0.25*woodCost);
//	}
//}
//
//template <typename SI> 
//bool Dugout<SI>::CanBuild(SI* _obj)
//{
//	if (_obj->woodAmount && _obj->woodAmount->currentCount >= woodCost)
//		return true;
//	else return false;
//}
//
//
//template <typename SI> 
//void Dugout<SI>::MonthAction(SI* _obj)
//{
//	if (_obj->woodAmount && SI->woodAmount->currentCount >= firewood)
//	{
//		_obj->woodAmount->currentCount -= firewood;
//	}
//	else
//	{
//		_obj->totalPleasure->currentCount -= pleasureMulct;
//	}
//}
//template <typename SI>
//void Dugout<SI>::Save()
//{
//	json j_in;
//	j_in["size"] = size;
//	j_in["coord.x"] = coord.x;
//	j_in["coord.y"] = coord.y;
//	j_in["resCount"] = structureResource->currentCount;
//	j_in["resIncrease"] = resIncrease;
//	j_in["status"] = workStatus;
//	j_in["area"] = workAreaRadius;
//	j_in["religionCount"] = MainReligion->currentCount;
//	j_in["fearCount"] = MainFear->currentCount;
//	j_in["buildDate"] = buildDate;
//	j_in["woodcost"] = woodCost;
//	j_in["firewood"] = firewood;
//	j_in["mulct"] = pleasureMulct;
//
//
//	std::string decipher = j_in.dump();
//	std::string cipher;
//	for (int n = 0; n < decipher.length(); n++)
//	{
//		cipher += decipher[n] ^ 11;
//	}
//	std::ofstream fout("Dugout.save");
//	fout << cipher;
//	fout.close();
//}
//
//template <typename SI>
//void Dugout<SI>::Load()
//{
//	json j_out;
//	std::string cipher, decipher;
//	std::ifstream fin("Dugout.save");
//	fin >> cipher;
//	fin.close();
//	for (int n = 0; n < cipher.length(); n++)
//	{
//		decipher += cipher[n] ^ 11;
//	}
//	j_out = json::parse(decipher);
//	size = j_out["size"];
//	coord.x = j_out["coord.x"];
//	coord.y = j_out["coord.y"];
//	structureResource->currentCount = j_out["resCount"];
//	resIncrease = j_out["resIncrease"];
//	workStatus = j_out["status"];
//	workAreaRadius = j_out["area"];
//	MainReligion->currentCount = j_out["religionCount"];
//	MainFear->currentCount = j_out["fearCount"];
//	buildDate = j_out["buildDate"];
//	woodCost = j_out["woodcost"];
//	firewood = j_out["firewood"];
//	pleasureMulct = j_out["mulct"];
//}
//
//template <typename SI>
//void Dugout<SI>::Out()
//{
//	std::cout << size << std::endl;
//	std::cout << coord.x << std::endl;
//	std::cout << coord.y << std::endl;
//	std::cout << structureResource->currentCount << std::endl;
//	std::cout << structureResource->type << std::endl;
//	std::cout << woodCost << std::endl;
//	std::cout << firewood << std::endl;
//	std::cout << pleasureMulct << std::endl;
//	std::cout << portion << std::endl;
//	std::cout << type << std::endl;
//	std::cout << resIncrease << std::endl;
//	std::cout << workAreaRadius << std::endl;
//	std::cout << workStatus << std::endl;
//	std::cout << MainReligion->currentCount << std::endl;
//	std::cout << MainReligion->type << std::endl;
//	std::cout << MainFear->currentCount << std::endl;
//	std::cout << MainFear->type << std::endl;
//	std::cout << buildDate << std::endl;
//}
//
//template <typename SI>
//int Dugout<SI>::ReturnSize()
//{
//	return this->size;
//}
//
//template <typename SI> 
//void Dugout<SI>::InitBD(SI* _obj)
//{
//	this->buildDate = _obj->sumWeek;
//}

////************************************************************************   ƒ≈–≈¬ﬂÕÕ€… ƒŒÃ   *******************************************************************************************************************************************************//
//
//
//WoodHut::WoodHut()
//{
//	SI->woodAmount->currentCount -= boardsCost;
//	SI->stoneAmount->currentCount -= stoneCost;
//	SI->skinAmount->currentCount -= skinCost;
//	SI->humanAmount->currentCount += numOfResidents;
//	structureResource = new Resource(0, Pleasure);
//	MainReligion = new Resource(0, Religion);
//	MainFear = new Resource(0, Fear);
//	MainEnlight = new Resource(0, Enlightenment);
//	buildDate = SI->sumWeek;
//}
//
//WoodHut::~WoodHut()
//{
//	delete MainFear;
//	delete MainReligion;
//	SI->humanAmount->currentCount -= numOfResidents;
//	delete structureResource;
//	delete MainEnlight;
//	if (SI->sumWeek == buildDate)
//	{
//		SI->woodAmount->currentCount += (int) 0.75*boardsCost;
//		SI->stoneAmount->currentCount += (int) 0.75*stoneCost;
//		SI->skinAmount->currentCount += (int) 0.75*skinCost;
//	}
//	else
//	{
//		SI->woodAmount->currentCount += (int) 0.25*boardsCost;
//		SI->stoneAmount->currentCount += (int) 0.25*stoneCost;
//	}
//}
//
//void WoodHut::Action()
//{
////	ActionTemp(0.03, 0.2, 0.2, 0.1, numOfResidents, 14, portion, MainReligion, MainFear, MainEnlight, structureResource);
//}
//
//
//void WoodHut::Construction()
//{
//
//}
//
//
//
////************************************************************************    ¿Ã≈ÕÕ€… ƒŒÃ   **********************************************************************//
//
//
//StoneHouse::StoneHouse()
//{
//	SI->boardsAmount->currentCount -= boardsCost;
//	SI->bricksAmount->currentCount -= bricksCost;
//	
//	SI->humanAmount->currentCount += numOfResidents;
//	structureResource = new Resource(0, Pleasure);
//	MainReligion = new Resource(0, Religion);
//	MainFear = new Resource(0, Fear);
//	MainEnlight = new Resource(0, Enlightenment);
//	buildDate = SI->sumWeek;
//}
//
//StoneHouse::~StoneHouse()
//{
//	delete MainFear;
//	delete MainReligion;
//	SI->humanAmount->currentCount -= numOfResidents;
//	delete structureResource;
//	delete MainEnlight;
//	if (SI->sumWeek == buildDate)
//	{
//		SI->woodAmount->currentCount += (int) 0.75*boardsCost;
//		SI->stoneAmount->currentCount += (int) 0.75*bricksCost;
//	}
//	else
//	{
//		SI->woodAmount->currentCount += (int) 0.25*boardsCost;
//		SI->stoneAmount->currentCount += (int) 0.25*bricksCost;
//		//SI->skinAmount += (int) 0.25*skinCost;
//	}
//}
//
//void StoneHouse::Action()
//{
////	ActionTemp(0.03, 0.2, 0.1, 0.4, numOfResidents, 21, portion, MainReligion, MainFear, MainEnlight, structureResource);
//}
//
//void StoneHouse::MonthAction()
//{
//	if (SI->coalAmount->currentCount >= coalCost && SI->clothesAmount->currentCount > clothesCost)
//	{
//		SI->coalAmount->currentCount -= coalCost;
//		SI->clothesAmount->currentCount -= clothesCost;
//	}
//	else
//	{
//		/*SI->totalPleasure -=*/
//	}
//	
//}