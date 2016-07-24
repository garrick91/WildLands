#include "SettlementInfo.h"
#include <math.h>

SettlementInfo::SettlementInfo(Graphics * _gfx){

	map = new Map(32);
	humanAmount = new Resource(1000, Human);
	woodAmount = new Resource(1000, Wood);
	totalPleasure = new Resource(0, Pleasure);
	mealAmount = new Resource(1000, Meal);
	stoneAmount = new Resource(1000, Stone);
	goldAmount = new Resource(1000, Gold);
	ironAmount = new Resource(1000, Iron);
	ironBarsAmount = new Resource(1000, IronBars);
	goldBarsAmount = new Resource(1000, GoldBars);
	aammunitionAmount = new Resource(1000, ArmorAndWeapon);
	coinsAmount = new Resource(1000, Coins);
	wheatGrainsAmount = new Resource(1000, WheatGrains);
	humulusAmount = new Resource(1000, Humulus);
	flourAmount = new Resource(1000, Flour);
	AlcoholAmount = new Resource(1000, Flour);
	totalReligion = new Resource(0, Religion);
	totalFear = new Resource(0, Fear);
	totalHumans = new Resource(1000, Human);


	targetWeek = 100;
	targetFear = 200;
	targetReligion = 150;
	targetPleasure = 500;
	targetPopulation = 50;
}

SettlementInfo::~SettlementInfo(){

	delete map;
	delete SelectedBlock;
	delete humanAmount;
	delete woodAmount;
	delete totalPleasure;
	delete mealAmount;
	delete stoneAmount;
	delete goldAmount;
	delete ironAmount;
	delete ironBarsAmount;
	delete goldBarsAmount;
	delete aammunitionAmount;
	delete coinsAmount;
	delete wheatGrainsAmount;
	delete humulusAmount;
	delete flourAmount;
	delete AlcoholAmount;
	delete totalReligion;
	delete totalFear;
	

	EraseLists(&trees);
	EraseLists(&rockDepos);
	EraseLists(&ironDepos);
	EraseLists(&goldDepos);
	EraseLists(&deerDepos);
	EraseLists(&cowDepos);
	EraseLists(&wolfDepos);
	EraseLists(&fruitDepos);
	EraseLists(&fishDepos);


	EraseLists(&lstWoodCut);
	EraseLists(&lstQuarries);
	EraseLists(&lstSmelts);
	EraseLists(&lstArmors);
	EraseLists(&lstMints);


	EraseLists(&lstHunterHouses);
	EraseLists(&lstFarms);
	EraseLists(&lstFields);
	EraseLists(&lstMills);
	EraseLists(&lstBakerys);
	EraseLists(&lstBrewerys);

	EraseLists(&lstTents);
	EraseLists(&lstChurchs);
	EraseLists(&lstOutposts);
	EraseLists(&lstTaverns);
	EraseLists(&lstGraves);
}

void SettlementInfo::SelectBlock(int _xPos, int _yPos, Graphics * _gfx){
	if (map->ReturnChoosen(_xPos, _yPos, _gfx)){
		if (SelectedBlock){

			SelectedBlock->Deselect(_gfx);
		}
		SelectedBlock = map->ReturnChoosen(_xPos, _yPos, _gfx);
	}
}

Block* SettlementInfo::ReturnSelected(){
	return SelectedBlock;
}

void SettlementInfo::SetBack(Graphics * _gfx){

	SetEnv(this->trees, _gfx, this->map);
	SetEnv(this->rockDepos, _gfx, this->map);
	SetEnv(this->ironDepos, _gfx, this->map);
	SetEnv(this->goldDepos, _gfx, this->map);
	SetEnv(this->cowDepos, _gfx, this->map);
	SetEnv(this->deerDepos, _gfx, this->map);
	SetEnv(this->fruitDepos, _gfx, this->map);
	SetEnv(this->wolfDepos, _gfx, this->map);
	SetEnv(this->fishDepos, _gfx, this->map);

	SetStr(this->lstWoodCut, this->map);
	SetStr(this->lstQuarries, this->map);
	SetStr(this->lstSmelts, this->map);
	SetStr(this->lstArmors, this->map);
	SetStr(this->lstMints, this->map);

	SetStr(this->lstHunterHouses, this->map);
	SetStr(this->lstFarms, this->map);
	SetStr(this->lstFields, this->map);
	SetStr(this->lstMills, this->map);
	SetStr(this->lstBakerys, this->map);
	SetStr(this->lstBrewerys, this->map);


	SetStr(this->lstTents, this->map);
	SetStr(this->lstChurchs, this->map);
	SetStr(this->lstOutposts, this->map);
	SetStr(this->lstTaverns, this->map);
	SetStr(this->lstGraves, this->map);
}


void SettlementInfo::SaveSettlement()
{
	std::ofstream fout("Saves/Settlement.save");
	fout << woodAmount->currentCount << std::endl;
	fout << totalPleasure->currentCount << std::endl;
	fout << mealAmount->currentCount << std::endl;
	fout << stoneAmount->currentCount << std::endl;
	fout << goldAmount->currentCount << std::endl;
	fout << ironAmount->currentCount << std::endl;
	fout << ironBarsAmount->currentCount << std::endl;
	fout << goldBarsAmount->currentCount << std::endl;
	fout << aammunitionAmount->currentCount << std::endl;
	fout << coinsAmount->currentCount << std::endl;
	fout << wheatGrainsAmount->currentCount << std::endl;
	fout << humulusAmount->currentCount << std::endl;
	fout << humanAmount->currentCount << std::endl;
	fout << flourAmount->currentCount << std::endl;
	fout << AlcoholAmount->currentCount << std::endl;
	fout << totalReligion->currentCount << std::endl;
	fout << totalFear->currentCount << std::endl;
	fout << totalHumans->currentCount << std::endl;
	fout << targetWeek << std::endl;
	fout << targetFear << std::endl;
	fout << targetReligion << std::endl;
	fout << targetPleasure << std::endl;
	fout << targetPopulation << std::endl;
	fout << currentWeek << std::endl;
	fout.close();
}

void SettlementInfo::LoadSettlement()
{
	int tmp;
	std::ifstream fin("Saves/Settlement.save");
	fin >> tmp;
	woodAmount->currentCount = tmp;
	fin >> tmp;
	totalPleasure->currentCount =tmp;
	fin >> tmp;
	mealAmount->currentCount = tmp;
	fin >> tmp;
	stoneAmount->currentCount= tmp;
	fin >> tmp;
	goldAmount->currentCount= tmp;
	fin >> tmp;
	ironAmount->currentCount= tmp;
	fin >> tmp;
	ironBarsAmount->currentCount= tmp;
	fin >> tmp;
	goldBarsAmount->currentCount= tmp;
	fin >> tmp;
	aammunitionAmount->currentCount= tmp;
	fin >> tmp;
	coinsAmount->currentCount= tmp;
	fin >> tmp;
	wheatGrainsAmount->currentCount= tmp;
	fin >> tmp;
	humulusAmount->currentCount= tmp;
	fin >> tmp;
	humanAmount->currentCount= tmp;
	fin >> tmp;
	flourAmount->currentCount= tmp;
	fin >> tmp;
	AlcoholAmount->currentCount= tmp;
	fin >> tmp;
	totalReligion->currentCount= tmp;
	fin >> tmp;
	totalFear->currentCount = tmp;
	fin >> tmp;
	totalHumans->currentCount = tmp;
	fin >> tmp;
	targetWeek = tmp;
	fin >> tmp;
	targetFear = tmp;
	fin >> tmp;
	targetReligion = tmp;
	fin >> tmp;
	targetPleasure = tmp;
	fin >> tmp;
	targetPopulation = tmp;
	fin >> tmp;
	currentWeek = tmp;
	fin.close();
}