#pragma once

#include "cocos2d.h"

#include "Waypoint.h"
#include "UpgradeBase.h"
#include "FileNames.h"

using namespace cocos2d;

#define UPGRADES_COUNT_ENEMY 5
#define UPGRADE_COEF_ENEMY 1.1

enum EnemyType
{
	ENEMY_SOLDIER = 1,
	ENEMY_HEAVY_SOLDIER,
	ENEMY_HORSEMAN,
	ENEMY_HEAVY_HORSEMAN,
	ENEMY_MACHINEGUN_CART,
	ENEMY_HEAVY_MACHINEGUN_CART,
	ENEMY_ARMORED_CAR,
	ENEMY_TANK,
	ENEMY_HEAVY_TANK,
	//add new enemies here
	MAX_ENEMY_NUMBER
};

class Enemy : public CCObject , public UpgradeBase
{
	int healthTotal;
	int healthCurrent;
	Waypoint *waypoint;
	int currentPoint;
	int speed;

	MoneyManager *moneyManager;

	CCSprite *sprite;
	CCSprite *spriteHealth;
	CCScene *scene;

	void CheckPointReached();
	void (*BaseReachedCallback)();
	void Destroy();	
	
public:
	Enemy(MoneyManager *moneyManager, const EnemyType eType, CCScene *scene, Waypoint *way);
	~Enemy(void);

	void SetSpeed(const int speed);
	CCPoint GetPosition();

	bool MakeDamage(const int health);

	void Start();

	virtual void Upgrade();
};

