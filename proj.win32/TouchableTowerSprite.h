#pragma once
#include "cocos2d.h"
#include "Tower.h"

#define TOWER_SCENE	1
#define TOWER_MENU	2

class TouchableTowerSprite
{
	cocos2d::CCPoint origPos;
public:
	TouchableTowerSprite(void);
	~TouchableTowerSprite(void);	

	cocos2d::CCSprite *sprite;
	int index;
	TowerTypes towerType;
	int towerPlace;

	int cellX;
	int cellY;

	void SaveInitialPosition();
	void ReturnToOriginalPosition();
};

