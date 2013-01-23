#pragma once

#include "cocos2d.h"

#include "Waypoint.h"

using namespace cocos2d;

class Enemy : public CCObject
{
	int health;
	Waypoint *waypoint;
	int currentPoint;
	int speed;

	CCSprite *sprite;
	CCScene *scene;
	void MoveFinished(Enemy* sender);
	
public:
	Enemy(char * image);
	~Enemy(void);

	void SetHealth(const int health);
	void SetWaypoint(Waypoint *way);
	void SetSpeed(const int speed);
	void SetScene(CCScene *scene);

	int GetHealth();
	int GetSpeed();

	void Start();

};

