#pragma once
#include "cocos2d.h"
#include "TouchableTowerSprite.h"
#include "FileNames.h"

enum TowerMenuItem
{
	UPGRADE,
	DESTROY
};

class TowerMenu
{
private:
	cocos2d::CCNode *scene;
	std::vector<cocos2d::CCSprite *> sprites;
	Tower *tower;
	cocos2d::CCPoint position;
	void chooseButtonsPositions();
	TouchableSprite *upgradeButton;
	TouchableSprite *sellButton;

public:
	TouchableSprite *getUpgradeButton() const { return upgradeButton;};
	TouchableSprite *getSellButton() const { return sellButton;};
	TowerMenu(cocos2d::CCNode *scene);
	TowerMenu(cocos2d::CCNode *scene, TouchableSprite *tTowerSprite);
	~TowerMenu(void);
	void attachToTower(Tower *tower);
	void detachFromTower();

	void Hide();
};

