#pragma once
#include "cocos2d.h"
#include "Tower.h"

#define TOWER_SCENE	1
#define TOWER_MENU	2
#define TOWER_MENU_ITEM 3

class TouchableTowerSprite
{
	//TOWER_SCENE
	cocos2d::CCPoint origPos;

public:
	TouchableTowerSprite(void);
	~TouchableTowerSprite(void);	
	
	//TOWER_SCENE
	Tower *tower;

	// COMMON
	cocos2d::CCSprite *sprite;
	TowerTypes towerType;
	int towerPlace;

	// TOWER_MENU
	int cellX;
	int cellY;

	void SaveInitialPosition();
	void ReturnToOriginalPosition();
};

