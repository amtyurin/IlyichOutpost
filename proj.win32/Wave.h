#pragma once
#include "cocos2d.h"

#include "Waypoint.h"

using namespace cocos2d;

class Wave : public CCObject
{	
	int currentWaveNumber;
	int enemyCount;
	int createdEnemies;
	int timeout;

	CCTimer timer;

	CCScene *scene;
	Waypoint *waypoint;
	void AddEnemy(float dt);

public:
	Wave(int enemyCount);
	~Wave(void);

	void Start(CCScene *scene, Waypoint *waypoint);
};

