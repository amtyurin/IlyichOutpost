#pragma once
#include "cocos2d.h"
#include "Tower.h"
using namespace cocos2d;

class TowerArray
{
private:
	CCArray *towerArray;	
public:
	TowerArray(void);
	void addTower(Tower &tower);
	void removeTower(Tower &tower);
	~TowerArray(void);
};

