#pragma once
#include "cocos2d.h"
#include "Tower.h"
#include <set>
#include <vector>
#include <algorithm>


class TowerArray
{
private:
	vector<Tower> towerSet;
public:
	TowerArray(void);
	void addTower(Tower &tower);
	void removeTower(Tower &tower);
	~TowerArray(void);
	vector<Tower>::iterator begin();
	vector<Tower>::iterator end();
};
