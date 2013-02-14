#pragma once
#include "cocos2d.h"
#include "TouchableTowerSprite.h"

enum TowerMenuItem
{
	UPGRADE,
	DESTROY
};

class TowerMenu
{
	cocos2d::CCNode *scene;
	std::vector<cocos2d::CCSprite *> sprites;
public:
	TowerMenu(cocos2d::CCNode *scene);
	~TowerMenu(void);

	cocos2d::CCSprite * AddMenuItem(TowerMenuItem item, TouchableTowerSprite *tower, cocos2d::CCPoint position);

	void Hide();
};

