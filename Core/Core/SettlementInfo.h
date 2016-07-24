#ifndef  SETTLEMENTINFO_H
#define  SETTLEMENTINFO_H

#include "EconomicStructure.h"
#include "ProvisionStructure.h"
#include "SocialStructure.h"
#include "Coordinates.h"
#include "Enviroment.h"
#include "Map.h"
#include <typeinfo.h>
#include <list>


class SettlementInfo{

public:
	//Обраний блок
	Block * SelectedBlock;

	//Ігрова мапа
	Map *map;

	int currentWeek, //Поточна неділя
		sumWeek, //Сумарна кількість неділь
		targetWeek, //Цільова неділя
		targetReligion, //Цільова кількість релігії
		targetFear, //Цільова кількість страху
		targetPopulation, //Цільова популяція
		targetPleasure; //Цільовий рівень задоволення

	//Ігрові ресурси
	Resource *humanAmount; //Жителі поселення
	Resource *woodAmount; //Дерево
	Resource *stoneAmount; //Каміння
	Resource *goldAmount; //Золото
	Resource *ironAmount; //Залізо
	Resource *ironBarsAmount; //Залізні злитки
	Resource *goldBarsAmount; //Золоті злитки
	Resource *aammunitionAmount; //Амуніція
	Resource *coinsAmount; //Золоті монети
	Resource *mealAmount; //Провізія
	Resource *wheatGrainsAmount; //Пшеничні зерна
	Resource *humulusAmount; //Хміль
	Resource *flourAmount; //Мука
	Resource *AlcoholAmount; //Алкоголь
	Resource *totalPleasure; //Задоволення
	Resource *totalFear; //Страх
	Resource *totalHumans; //Населення
	Resource *totalReligion; //Релігія

	//Будівлі для добування будівельних ресурсів та їх обробки
	std::list <WoodcutterHut<SettlementInfo>*>lstWoodCut; //Список дроворубів
	std::list <Quarry<SettlementInfo>*>lstQuarries; //Список рудників
	std::list <Smeltery<SettlementInfo>*>lstSmelts; //Список плавильнь
	std::list <Armourer<SettlementInfo>*>lstArmors; //Список зброярів
	std::list <Mint<SettlementInfo>*>lstMints; //Список монетних дворів

	//Будівлі для добування їжі та її обробки
	std::list <HunterHouse<SettlementInfo>*> lstHunterHouses; //Список мисливців
	std::list <Farm<SettlementInfo>*> lstFarms; //Список ферм
	std::list <Field<SettlementInfo>*> lstFields; //Список зернових полів
	std::list <Mill<SettlementInfo>*> lstMills; //Список
	std::list <Bakery<SettlementInfo>*> lstBakerys; //Пекарні
	std::list <Brewery<SettlementInfo>*> lstBrewerys; //Броварні

	//Будівлі для добування соціальних ресурсів
	std::list <Dugout<SettlementInfo>*>lstTents; //Палатки
	std::list <Church<SettlementInfo>*>lstChurchs; //Церкви
	std::list <Outpost<SettlementInfo>*>lstOutposts; //Оборонні пости
	std::list <Tavern<SettlementInfo>*>lstTaverns; //Таверни
	std::list <Grave<SettlementInfo>*>lstGraves; //Кладовища


	//Окружение
	std::list<Tree*> trees; //Дерева
	std::list<StoneEnv*> rockDepos; //Каміння
	std::list<GoldEnv*> goldDepos; //Золоті жили
	std::list<IronEnv*>  ironDepos; //Залізні жили
	std::list<DeerEnv*> deerDepos; //Пасовища оленів
	std::list<CowEnv*>  cowDepos; //Пасовища корів
	std::list<WolfEnv*>  wolfDepos; //Вовчі стаї
	std::list<FruitTree*> fruitDepos; //Фруктові дерева
	std::list<FishEnv*>  fishDepos; //Ставки

	SettlementInfo(Graphics * _gfx);
	~SettlementInfo();

	void SaveSettlement();
	void LoadSettlement();
	//Метод для вибору блоку
	void SelectBlock(int _xPos, int _yPos, Graphics * _gfx);

	//Повернення обраного блоку
	Block * ReturnSelected();

	//Створення будівлі
	template <typename T> T* CreateStructure(std::string FileName, Graphics * _gfx);

	//Встановлення будівлі на місце після завантаження збереження
	void SetBack(Graphics * _gfx);
};

template <typename T> T* SettlementInfo::CreateStructure(std::string FileName, Graphics * _gfx){

	T* obj = new T(FileName, _gfx);
	if (SelectedBlock){
		if (SelectedBlock->Check()){
			if (obj->CanBuild(this)){

				SelectedBlock->LocateStructure<T>(obj);
				obj->Construction(this);
				obj->InitBD(this);
				obj->Find(this);

				return obj;
			}
			else{

				delete obj;
				
				MessageBox(NULL, "Not enought resources!!!", "ERROR", MB_OK);
			}
		}
		else{

			MessageBox(NULL, "Block isn't empty!", "ERROR", MB_OK);
			return NULL;
		}
	}
	else{

		MessageBox(NULL, "Block isn't choosen!", "ERROR", MB_OK);
		return NULL;
	}
	return NULL;	
}

//Видалення елементів списку із пам'яті
template <typename Т> void EraseLists(std::list <Т*> * _lst){

	Т * temp;
	
	if (_lst->size()>0)
	{
		auto iter = _lst->begin();
		while (iter != _lst->end())
		{
				temp = (*iter);
				iter = _lst->erase(iter);
				delete temp;
		}
	}
}


//Встановити на місце об'єкт оточення
template <typename T> void SetEnv(std::list<T*> _lst, Graphics * _gfx, Map* _map){

	const auto blockBegin = _map->ReturnGameMap().begin();
	auto objIter = _lst.begin();
	auto blockIter = blockBegin;

	while (objIter != _lst.end()){
		while (blockIter != _map->ReturnGameMap().end()){
			if ((*objIter)->GetPos().x == (*blockIter)->GetPosition().x && (*objIter)->GetPos().y == (*blockIter)->GetPosition().y){

				(*blockIter)->LocateEnviroment((*objIter), _gfx);
				break;
			}
			++blockIter;
		}
		objIter++;
	}
}

//Встановити на місце споруду
template <typename T> void SetStr(std::list<T*> _lst, Map* _map){
	
	const auto blockBegin = _map->ReturnGameMap().begin();
	auto objIter = _lst.begin();
	auto blockIter = blockBegin;
	while (objIter != _lst.end()) {
		blockIter = blockBegin;
		while (blockIter != _map->ReturnGameMap().end()) {
			if ((*objIter)->coord.x == (*blockIter)->GetPosition().x-1 && (*objIter)->coord.y == (*blockIter)->GetPosition().y-1 ) {

				(*blockIter)->BackStructure((*objIter));
				break;
			}
			blockIter++;
		}
		objIter++;
	}
}


#endif // ! SETTLEMENTINFO_H