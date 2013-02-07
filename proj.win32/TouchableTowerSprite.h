#pragma once
#include "cocos2d.h"
#include "Tower.h"

using namespace cocos2d;

#define TOWER_SCENE	1
#define TOWER_MENU	2

class TouchableTowerSprite
{
public:
	TouchableTowerSprite(void);
	~TouchableTowerSprite(void);
	void ReturnToCell();
	CCSprite *sprite;
	int index;
	TowerTypes towerType;
	int towerPlace;

	int cellX;
	int cellY;
};

