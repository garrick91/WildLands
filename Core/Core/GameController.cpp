#include "GameController.h"
#include <fstream>


SettlementInfo * GameController::Settlement;




void GameController::Init(Graphics* _gfx){

	Settlement = new SettlementInfo(_gfx);
	Settlement->map->GenerateMap<SettlementInfo>(_gfx, Settlement);
}


void GameController::Release(){

	delete Settlement;
}

void GameController::ChooseBlock(int _xPos, int _yPos, Graphics * _gfx){

	Settlement->SelectBlock(_xPos, _yPos, _gfx);
}


void GameController::Clear(){

	if (Settlement->SelectedBlock)
	{
		switch (Settlement->SelectedBlock->structureType) {

		case StWoodCut:
			InStList(&Settlement->lstWoodCut, Settlement->SelectedBlock, Settlement);
			break;
		case StTQuarry:
			InStList(&Settlement->lstQuarries, Settlement->SelectedBlock, Settlement);
			break;
		case StSmeltery:
			InStList(&Settlement->lstSmelts, Settlement->SelectedBlock, Settlement);
			break;
		case StArmourer:
			InStList(&Settlement->lstArmors, Settlement->SelectedBlock, Settlement);
			break;
		case StMint:
			InStList(&Settlement->lstMints, Settlement->SelectedBlock, Settlement);
			break;


		case StHunter:
			InStList(&Settlement->lstHunterHouses, Settlement->SelectedBlock, Settlement);
			break;
		case StFarm:
			InStList(&Settlement->lstFarms, Settlement->SelectedBlock, Settlement);
			break;
		case StMill:
			InStList(&Settlement->lstMills, Settlement->SelectedBlock, Settlement);
			break;
		case StField:
			InStList(&Settlement->lstFields, Settlement->SelectedBlock, Settlement);
			break;
		case StBaker:
			InStList(&Settlement->lstBakerys, Settlement->SelectedBlock, Settlement);
			break;
		case StBrewer:
			InStList(&Settlement->lstBrewerys, Settlement->SelectedBlock, Settlement);
			break;

		case StTents:
			MessageBox(NULL, "YOU CAN'T DESTROY TENTS", "WAAAHHH! ERROR!", NULL);
			break;
		case StChurch:
			InStList(&Settlement->lstChurchs, Settlement->SelectedBlock, Settlement);
			break;
		case StOutpost:
			InStList(&Settlement->lstOutposts, Settlement->SelectedBlock, Settlement);
			break;
		case StTavern:
			InStList(&Settlement->lstTaverns, Settlement->SelectedBlock, Settlement);
			break;
		case StGrave:
			InStList(&Settlement->lstGraves, Settlement->SelectedBlock, Settlement);
			break;
		}
	}
	else
	{
			MessageBox(NULL, "BLOCK ISN'T SELECTED!", "Error", NULL);
	}
}


void GameController::UpdateSystem(Graphics * _gfx){

	UpdateList(&Settlement->lstQuarries, Settlement, _gfx);
	UpdateList(&Settlement->lstWoodCut, Settlement, _gfx);
	UpdateList(&Settlement->lstSmelts, Settlement, _gfx);
	UpdateList(&Settlement->lstArmors, Settlement, _gfx);
	UpdateList(&Settlement->lstMints, Settlement, _gfx);

	UpdateList(&Settlement->lstHunterHouses, Settlement, _gfx);
	UpdateList(&Settlement->lstFarms, Settlement, _gfx);
	UpdateList(&Settlement->lstFields, Settlement, _gfx);
	UpdateList(&Settlement->lstMills, Settlement, _gfx);
	UpdateList(&Settlement->lstBakerys, Settlement, _gfx);
	UpdateList(&Settlement->lstBrewerys, Settlement, _gfx);

	UpdateList(&Settlement->lstTents, Settlement, _gfx);
	UpdateList(&Settlement->lstChurchs, Settlement, _gfx);
	UpdateList(&Settlement->lstOutposts, Settlement, _gfx);
	UpdateList(&Settlement->lstTaverns, Settlement, _gfx);
	UpdateList(&Settlement->lstGraves, Settlement, _gfx);


	if (Settlement->currentWeek % 10 == 0)
	{
		int n = 1 + rand() % 4;
		switch (n)
		{
		case 1:
			MessageBox(NULL, "RATS ATE OUR MEAL, MY LORD!", "RATS!!!", NULL);
			if (Settlement->mealAmount->currentCount >= 10)
			{
				Settlement->mealAmount->currentCount -= 10;
			}
			else
			{
				Settlement->mealAmount->currentCount = 0;
			}
			break;
		case 2:
			MessageBox(NULL, "In our village was operating a heretic, My Lord!", "HERECY!!!", NULL);
			if (Settlement->totalReligion->currentCount >= 10)
			{
				Settlement->totalReligion->currentCount -= 10;
			}
			else
			{
				Settlement->totalReligion->currentCount = 0;
			}
			break;
		case 3:
			MessageBox(NULL, "Pack of wolves spotted near the settlement! Citizens are frightened, my lord!", "WOLFS!!!", NULL);
			Settlement->totalFear->currentCount += 10;
			break;
		case 4:
			MessageBox(NULL, "Detractors spread rumors about you, my lord!", "RUMORS!!!", NULL);
			Settlement->totalPleasure->currentCount -= 10;
			break;
		}
	}
}

bool GameController::CheckGoals(){
	if (Settlement->currentWeek == Settlement->targetWeek)
	{
		if (Settlement->totalReligion->currentCount >= Settlement->targetReligion && Settlement->totalFear->currentCount <= Settlement->targetFear && Settlement->totalHumans->currentCount >= Settlement->targetPopulation && Settlement->totalPleasure->currentCount >= Settlement->targetPleasure) {

			return true;
		}
		else {

			return false;
		}
	}
}


//перевірка файлу на існування
bool IfFileExistsAndIsNotEmpty(std::string fPath){

	char str[255];

	std::ifstream file_re;
	file_re.open(fPath.c_str());

	if (!file_re)
		return false;


	return true;
}

bool GameController::CheckFiles(){

	if (IfFileExistsAndIsNotEmpty("Saves/TCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/SCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/ICount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/GCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/FTCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/CCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/DCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/FCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/WCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/QCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/WCCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/SMCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/AMCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/MTCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/HHCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/FMCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/FDCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/BKCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/BWCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/TentCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/CHCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/OPCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/TVCount.save") &&
		IfFileExistsAndIsNotEmpty("Saves/GVCount.save") &&

		IfFileExistsAndIsNotEmpty("Saves/Trees.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Rocks.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Iron.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Gold.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Fruit.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Cow.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Deer.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Fish.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Wolf.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Querry.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Woodcutter.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Smelts.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Mints.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Hunter.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Farms.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Fields.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Mills.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Bakerys.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Brewerys.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Tent.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Churchs.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Outposts.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Taverns.save") &&
		IfFileExistsAndIsNotEmpty("Saves/Graves.save"))
		return true;

	return false;
}


void GameController::Load(Graphics * _gfx){

		Settlement = new SettlementInfo(_gfx);
		Settlement->map->GenerateEmpty(_gfx);


		EnvLoad("Saves/TCount.save", "Saves/Trees.save", &Settlement->trees, "Parameters/Trees.prm", _gfx);
		EnvLoad("Saves/SCount.save", "Saves/Rocks.save", &Settlement->rockDepos, "Parameters/Rocks.prm", _gfx);
		EnvLoad("Saves/ICount.save", "Saves/Iron.save", &Settlement->ironDepos, "Parameters/Iron.prm", _gfx);
		EnvLoad("Saves/GCount.save", "Saves/Gold.save", &Settlement->goldDepos, "Parameters/Gold.prm", _gfx);
		EnvLoad("Saves/FTCount.save", "Saves/Fruit.save", &Settlement->fruitDepos, "Parameters/Fruit.prm", _gfx);
		EnvLoad("Saves/CCount.save", "Saves/Cow.save", &Settlement->cowDepos, "Parameters/Cow.prm", _gfx);
		EnvLoad("Saves/DCount.save", "Saves/Deer.save", &Settlement->deerDepos, "Parameters/Deer.prm", _gfx);
		EnvLoad("Saves/FCount.save", "Saves/Fish.save", &Settlement->fishDepos, "Parameters/Fish.prm", _gfx);
		EnvLoad("Saves/WCount.save", "Saves/Wolf.save", &Settlement->wolfDepos, "", _gfx);

		StLoad("Saves/QCount.save", "Saves/Querry.save", &Settlement->lstQuarries, "Parameters/Quarry.prm", _gfx);
		StLoad("Saves/WCCount.save", "Saves/Woodcutter.save", &Settlement->lstWoodCut, "Parameters/WoodcutterHut.prm", _gfx);
		StLoad("Saves/SMCount.save", "Saves/Smelts.save", &Settlement->lstSmelts, "Parameters/Smeltery.prm", _gfx);
		StLoad("Saves/AMCount.save", "Saves/Armors.save", &Settlement->lstArmors, "Parameters/Armourer.prm", _gfx);
		StLoad("Saves/MTCount.save", "Saves/Mints.save", &Settlement->lstMints, "Parameters/Mint.prm", _gfx);


		StLoad("Saves/HHCount.save", "Saves/Hunter.save", &Settlement->lstHunterHouses, "Parameters/HunterHouse.prm", _gfx);
		StLoad("Saves/FMCount.save", "Saves/Farms.save", &Settlement->lstFarms, "Parameters/Farm.prm", _gfx);
		StLoad("Saves/FDCount.save", "Saves/Fields.save", &Settlement->lstFields, "Parameters/Field.prm", _gfx);
		StLoad("Saves/MLCount.save", "Saves/Mills.save", &Settlement->lstMills, "Parameters/Mill.prm", _gfx);
		StLoad("Saves/BKCount.save", "Saves/Bakerys.save", &Settlement->lstBakerys, "Parameters/Bakery.prm", _gfx);
		StLoad("Saves/BWCount.save", "Saves/Brewerys.save", &Settlement->lstBrewerys, "Parameters/Brewery.prm", _gfx);

		StLoad("Saves/TentCount.save", "Saves/Tent.save", &Settlement->lstTents, "Parameters/Tent.prm", _gfx);
		StLoad("Saves/CHCount.save", "Saves/Churchs.save", &Settlement->lstChurchs, "Parameters/Church.prm", _gfx);
		StLoad("Saves/OPCount.save", "Saves/Outposts.save", &Settlement->lstOutposts, "Parameters/Outpost.prm", _gfx);
		StLoad("Saves/TVCount.save", "Saves/Taverns.save", &Settlement->lstTaverns, "Parameters/Tavern.prm", _gfx);
		StLoad("Saves/GVCount.save", "Saves/Graves.save", &Settlement->lstGraves, "Parameters/Grave.prm", _gfx);

		Settlement->LoadSettlement();

		Settlement->SetBack(_gfx);

}


void GameController::Save(){

	Settlement->SaveSettlement();
	StSave("Saves/TCount.save", "Saves/Trees.save", &Settlement->trees);
	StSave("Saves/SCount.save", "Saves/Rocks.save", &Settlement->rockDepos);
	StSave("Saves/ICount.save", "Saves/Iron.save", &Settlement->ironDepos);
	StSave("Saves/GCount.save", "Saves/Gold.save", &Settlement->goldDepos);
	StSave("Saves/FTCount.save", "Saves/Fruit.save", &Settlement->fruitDepos);
	StSave("Saves/CCount.save", "Saves/Cow.save", &Settlement->cowDepos);
	StSave("Saves/DCount.save", "Saves/Deer.save", &Settlement->deerDepos);
	StSave("Saves/FCount.save", "Saves/Fish.save", &Settlement->fishDepos);
	StSave("Saves/WCount.save", "Saves/Wolf.save", &Settlement->wolfDepos);
	
	StSave("Saves/QCount.save", "Saves/Querry.save", &Settlement->lstQuarries);
	StSave("Saves/WCCount.save", "Saves/Woodcutter.save", &Settlement->lstWoodCut);
	StSave("Saves/SMCount.save", "Saves/Smelts.save", &Settlement->lstSmelts);
	StSave("Saves/AMCount.save", "Saves/Armors.save", &Settlement->lstArmors);
	StSave("Saves/MTCount.save", "Saves/Mints.save", &Settlement->lstMints);

	StSave("Saves/HHCount.save", "Saves/Hunter.save", &Settlement->lstHunterHouses);
	StSave("Saves/FMCount.save", "Saves/Farms.save", &Settlement->lstFarms);
	StSave("Saves/FDCount.save", "Saves/Fields.save", &Settlement->lstFields);
	StSave("Saves/MLCount.save", "Saves/Mills.save", &Settlement->lstMills);
	StSave("Saves/BKCount.save", "Saves/Bakerys.save", &Settlement->lstBakerys);
	StSave("Saves/BWCount.save", "Saves/Brewerys.save", &Settlement->lstBrewerys);


	StSave("Saves/TentCount.save", "Saves/Tent.save", &Settlement->lstTents);
	StSave("Saves/CHCount.save", "Saves/Churchs.save", &Settlement->lstChurchs);
	StSave("Saves/OPCount.save", "Saves/Outposts.save", &Settlement->lstOutposts);
	StSave("Saves/TVCount.save", "Saves/Taverns.save", &Settlement->lstTaverns);
	StSave("Saves/GVCount.save", "Saves/Graves.save", &Settlement->lstGraves);
}

void GameController::Render(int _xPos, int _yPos){

	Settlement->map->RenderMap(_xPos, _yPos, Settlement);	
}

void GameController::Update(){

	UpdateObject(Settlement->deerDepos);
	UpdateObject(Settlement->cowDepos);
	UpdateObject(Settlement->trees);
	UpdateObject(Settlement->fruitDepos);
	UpdateObject(Settlement->wolfDepos);
}
