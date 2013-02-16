#pragma once
#include "cocos2d.h"
#include "Tower.h"

/*#define TOWER_SCENE	1
#define TOWER_MENU	2
#define TOWER_MENU_ITEM 3*/

enum SPRITE_TYPES{
	TOWER_ON_SCENE = 1,
	TOWER_ON_PANEL,
	MENU_BUTTON
};

class TouchableSprite
{
	//TOWER_ON_SCENE
	cocos2d::CCPoint origPos;

public:
	TouchableSprite(void);
	~TouchableSprite(void);	
	
	//TOWER_ON_SCENE
	Tower *tower;

	// COMMON
	cocos2d::CCSprite *sprite;
	TowerTypes towerType;
	int spriteType;

	// TOWER_MENU
	int cellX;
	int cellY;

	void SaveInitialPosition();
	void ReturnToOriginalPosition();
};

