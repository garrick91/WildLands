#ifndef TYPES_H
#define TYPES_H

enum Seasons
{
	Winter,
	Spring,
	Summer,
	Autumn
};


enum EnviromentType {
	None,
	Trees, //+
	CoalDepo, //-
	Rock, //+
	GoldDepo, //+
	IronDepo, //+
	Deer, //+
	Cow,//+
	Fish,//+
	Wolf,//+
	Shrub, //+
	FruitTrees
};

enum BlockBackground {
	Ground,
	GrassLT,
	GrassT,
	GrassRT,
	GrassLM,
	GrassM,
	GrassRM,
	GrassLL,
	GrassL,
	GrassRL,
	Sand,
	WaterLT,
	WaterT,
	WaterRT,
	WaterLM,
	WaterM,
	WaterRM,
	WaterLL,
	WaterL,
	WaterRL
};

enum StructureType {
	StNone,	


	StTQuarry,
	StWoodCut,
	StSmeltery,
	StArmourer,
	StMint,

	//--------
	StHunter,
	StFarm,
	StField,
	StMill,
	StBaker,
	StBrewer,

	//--------
	StTents,
	StChurch,
	StOutpost,
	StTavern,
	StGrave
};

enum ResourceType {

	////**************ОСНОВНОЙ РЕСУРС******************////
	Human, //человек


//-----------------------------------------------//

	//СТРОИТЕЛЬНЫЕ И ЭКОНОМИЧЕСКИЕ РЕСУРСЫ


	/**************Основные ресуры******************/
	Coal, //уголь
	Wood, //дерево
	Stone, //камень
	Iron, //железо
	Gold, //золото


	/************Второстепенные ресуры***************/
	Boards, //доски
	Bricks, //кирпичи
	IronBars, //железные слитки
	GoldBars, //золотые слитки
	Skin, //шкура
	Clothes,

	ArmorAndWeapon, //оружие и броня
	Coins, //монеты


//-----------------------------------------------//


	//ПИЩЕВЫЕ РЕСУРСЫ


/**************Основные ресуры******************/
	Meal, //Провизия
	WheatGrains, //пшеничные зёрна
	Humulus, //хмель
	Water, //вода


/************Второстепенные ресуры***************/
	Flour, //мука
	Alcohol, //алкоголь

			
//-----------------------------------------------//


			//НЕМАТЕРИАЛЬНЫЕ РЕСУРСЫ
		
	Pleasure, //удовольствие
	Fear, //страх
	Religion, //религия
	Enlightenment, //просвещённость

	Empty
};

enum FoodPortion
{
	VerySmall=1,
	Small = 2,
	Normal = 3,
	Big = 4,
	VeryBig = 5
};

#endif // !TYPES_H
