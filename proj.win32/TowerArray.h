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
	vector<Tower*> towerSet;
public:
	TowerArray(MoneyManager *moneyManager);

	void addTower(Tower *tower);
	Tower *createTower(TowerTypes type, cocos2d::CCPoint _position);
	void removeTower(Tower &tower);
	~TowerArray(void);
	vector<Tower*>::iterator begin();
	vector<Tower*>::iterator end();

	Tower *GetTower(int index);

	bool Buy(TowerTypes type);
};
