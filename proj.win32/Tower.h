#pragma once
#include "cocos2d.h"
#include "Wave.h"
#include <math.h>
#include "Wave.h"
#include "Enemy.h"
#include "UpgradeBase.h"

#define GAME_SPEED 10

#define UPGRADES_COUNT_TOWER 5
#define UPGRADE_COEF_TOWER 1.2

enum TowerTypes{
	MACHINE_GUN = 1,
	HEAVY_GUN = 2
};

enum CircleHalf{  //for turns processing
	UPPER_HALF = 0,
	LOWER_HALF
};

class Tower : public UpgradeBase
{
private:
	int fireSpeed;
	int fireRadius;
	int damage;
	int reloadTime;
	int price;
	float normRotateX;
	float normRotateY;

	MoneyManager *moneyManager;

	cocos2d::CCPoint position;
	cocos2d::CCSprite *spritePtr;
	cocos2d::CCSprite *spriteRange;

	void fire(Wave *wave, int index);

public:
	Tower(MoneyManager *moneyManager, int type, cocos2d::CCPoint _position);
	~Tower(void);
	const float getX() const { return position.x;};
	const float getY() const { return position.y;};
	void setX(const float newX);
	void setY(const float newY);
	const float getDamage() const { return damage;};
	cocos2d::CCSprite *getSprite() const;
	void turnTo(const cocos2d::CCPoint position) const;
	const bool operator < (const Tower &tower) const;
	const bool operator > (const Tower &tower) const;
	const bool isTargetInRange(CCPoint target) const;
	void processEnemies(Wave *wave);
	const bool isAbleToFire() const;

	virtual void Upgrade();
	bool CanBuy();
	void Buy();
};

