#pragma once
#include "tower.h"

class ElectromagneticTower :
	public Tower
{
	void fire(Wave *wave, int index);
	void startFireAnimation(const cocos2d::CCPoint startPosition, const cocos2d::CCPoint endPosistion);
	void deleteShell(cocos2d::CCNode *sender);
	void endFireAnimation(cocos2d::CCNode *sender);

public:
	ElectromagneticTower(MoneyManager *moneyManager, TowerTypes type, cocos2d::CCPoint _position);
	~ElectromagneticTower(void);

	virtual void processEnemies(Wave *wave);
};

