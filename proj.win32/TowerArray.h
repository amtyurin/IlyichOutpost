#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include <set>
#include <vector>
#include <algorithm>
#include "MoneyManager.h"


class TowerArray
{
	MoneyManager *moneyManager;
private:
	std::vector<Tower*> towerSet;
public:
	TowerArray(MoneyManager *moneyManager);

	void addTower(Tower *tower);
	Tower *createTower(TowerTypes type, cocos2d::CCPoint _position);
	void removeTower(Tower &tower);
	~TowerArray(void);
	std::vector<Tower*>::iterator begin();
	std::vector<Tower*>::iterator end();

	Tower *GetTower(size_t index);

	bool Buy(TowerTypes type);
};
