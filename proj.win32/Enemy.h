#pragma once

#include "cocos2d.h"

#include "Waypoint.h"

using namespace cocos2d;

enum EnemyType
{
	ENEMY_SOLDIER,
	ENEMY_HEAVY_SOLDIER,
	ENEMY_HORSEMAN,
	ENEMY_HEAVY_HORSEMAN,
	ENEMY_MACHINEGUN_CART,
	ENEMY_HEAVY_MACHINEGUN_CART,
	ENEMY_ARMORED_CAR,
	ENEMY_TANK,
	ENEMY_HEAVY_TANK
};

class Enemy : public CCObject
{
	int healthTotal;
	int healthCurrent;
	Waypoint *waypoint;
	int currentPoint;
	int speed;

	void *wave;

	CCSprite *sprite;
	CCSprite *spriteHealth;
	CCScene *scene;

	void CheckPointReached();
	void Destroy();
	
public:
	Enemy(void *wave, const EnemyType eType, CCScene *scene, Waypoint *way);
	~Enemy(void);

	void SetSpeed(const int speed);
	CCPoint GetPosition();

	void MakeDamage(const int health);

	void Start();
};

