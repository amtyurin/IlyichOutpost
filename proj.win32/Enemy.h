#pragma once

#include "cocos2d.h"

#include "Waypoint.h"

using namespace cocos2d;

class Enemy : public CCObject
{
	int healthTotal;
	int healthCurrent;
	Waypoint *waypoint;
	int currentPoint;
	int speed;

	CCSprite *sprite;
	CCSprite *spriteHealth;
	CCScene *scene;

	void CheckPointReached(Enemy* sender);
	void Destroy(Enemy *sender);
	
public:
	Enemy(char * image);
	~Enemy(void);

	void SetHealthTotal(const int health);
	void SetWaypoint(Waypoint *way);
	void SetSpeed(const int speed);
	void SetScene(CCScene *scene);

	bool MakeDamage(const int health);

	void Start();

};

