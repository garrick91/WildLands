#ifndef  GAMECONTROLLER_H
#define GAMECONTROLLER_H
#include "SettlementInfo.h"
#include <iostream>


class GameController {
	GameController() {};
	static SettlementInfo *Settlement;  //Current settlement
public:

	//Ініціалізація ігрової сесії
	static void Init(Graphics* _gfx);

	//Вибір блоку за вказаними координатами
	static void ChooseBlock(int _xPos, int _yPos, Graphics * _gfx);
	
	//Повернення вказівника на об'єкт класу SettlementInfo
	static SettlementInfo* ReturnSettlement() { return Settlement; }   

	//Очищення обраного блоку
	static void Clear();

	//Створення та встановлення нового ігрового об'єкту - споруди
	template <typename T> static T* Build (std::string FileName,Graphics * _gfx);

	//Оновлення усієї системи
	static void UpdateSystem(Graphics * _gfx);

	//Перевірка стану ресурсів на відповідність
	static bool CheckGoals();

	//Загрузка останньої збереженої сесії
	static void Load(Graphics * _gfx);

	//Збереження останньої збереженної сесії
	static void Save();

	//Рендеринг об'єктів
	static void Render(int _xPos, int _yPos);

	//Оновлення анімацій
	static void Update();

	//Звільнення ресурсів
	static void Release();

	//Перевірка на наявність файлів збереження
	static bool CheckFiles();
};

template <typename T>
T* GameController::Build(std::string FileName, Graphics * _gfx){

	return Settlement->CreateStructure<T>(FileName, _gfx);
}

//Рендеринг усіх елементів списку
template <typename T> 
void RenderObject(std::list<T*> _lst, int _xPos, int _yPos){

	if (_lst.size()>0){

		for (auto iter = _lst.begin(); iter != _lst.end(); iter++){

			if ((*iter)){

				(*iter)->Render(_xPos, _yPos);
			}
		}
	}
}

//Оновлення анімацій усіх анімованих елементів списку
template <typename T> 
void UpdateObject(std::list<T*>  _lst){

	if (_lst.size()>0){

		for (auto iter = _lst.begin(); iter != _lst.end(); iter++){

			if ((*iter)){

				(*iter)->Update();
			}
		}
	}
}

//Видалення обраного елементу із його списку та звільнення пам'яті, виділенної під нього
template <typename TP> void InStList(std::list<TP*> * _lst, Block * _obj, SettlementInfo * SI){
	TP * temp;
	bool Stop = false;
	if (_lst->size()>0){

		auto iter = _lst->begin();
		while (!Stop || iter != _lst->end()){
			if (_obj->ReturnStructure() == (*iter)){

				temp = (*iter);
				_obj->Clear();
				iter = _lst->erase(iter);
				Stop = true;
				temp->Destruction(SI);
				delete temp;
			}
			else{

				++iter;
			}
		}
	}
}

//Виконати дію для кожної споруди у списку
template <typename STL> 
void UpdateList(std::list<STL*> * _lst, SettlementInfo * _SI, Graphics* _gfx){

	if (_lst->size()>0){

		for (auto iter = _lst->begin(); iter != _lst->end(); iter++){

			if ((*iter)){

				(*iter)->Action(_SI, _gfx);
			}
		}
	}
}

//збереження ігрових об'єтів
template <typename ST>
void StSave(std::string _countFile, std::string _dataFile, std::list<ST*> *_lst){
	int size;
	std::string *ToSave;
	size = _lst->size();
	std::ofstream foutC(_countFile);
	std::ofstream foutD(_dataFile);
	foutC << size;
	foutC.close();
	ToSave = new std::string[size];
	if (size){
		
		auto iter = _lst->begin();
	    int 	i = 0;
		while (iter != _lst->end()){
			ToSave[i] = (*iter)->Save();
			foutD << ToSave[i] << std::endl;
			i++;
			iter++;
		}
		foutD.close();
	}
	delete[] ToSave;
}


//Завантаження ігрових споруд
template <typename ST>
void StLoad(std::string _countFile, std::string _dataFile, std::list<ST*> *_lst, std::string _paramName, Graphics * _gfx){
	int size;
	std::string *ToLoad;
	ST* sTmp;
	std::ifstream fin(_countFile);
	fin >> size;
	fin.close();
	ToLoad = new std::string[size];
	std::ifstream finD (_dataFile);
	if (size){	
		
		auto i = 0;
		while (i != size){

			sTmp = new ST(_paramName, _gfx);
			finD >> ToLoad[i];
			sTmp->Load(ToLoad[i]);
			_lst->push_back(sTmp);
			i++;

		}
		finD.close();
	}
	delete[] ToLoad;
}


//Завантаження об'єктів оточення
template <typename ST>
void EnvLoad(std::string _countFile, std::string _dataFile, std::list<ST*> *_lst, std::string _paramName, Graphics * _gfx){
	int size;
	std::string *ToLoad;
	ST* sTmp;
	std::ifstream fin(_countFile);
	fin >> size;
	fin.close();
	ToLoad = new std::string[size];
	std::ifstream finD(_dataFile);
	if (size){

		auto i = 0;
		while (i != size){

			sTmp = new ST(_paramName, _gfx);
			finD >> ToLoad[i];
			sTmp->Load(ToLoad[i], _gfx);
			_lst->push_back(sTmp);
			i++;
		}
		finD.close();
	}
	delete[] ToLoad;
}

#endif // ! GAMECONTROLLER_H