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
	TouchableTowerSprite *upgradeButton;
	TouchableTowerSprite *sellButton;

public:
	TouchableTowerSprite *getUpgradeButton() const { return upgradeButton;};
	TouchableTowerSprite *getSellButton() const { return sellButton;};
	TowerMenu(cocos2d::CCNode *scene);
	TowerMenu(cocos2d::CCNode *scene, TouchableTowerSprite *tTowerSprite);
	~TowerMenu(void);
	void attachToTower(Tower *tower);
	void detachFromTower();
	cocos2d::CCSprite * AddMenuItem(TowerMenuItem item, TouchableTowerSprite *tower, cocos2d::CCPoint position);

	void Hide();
};

