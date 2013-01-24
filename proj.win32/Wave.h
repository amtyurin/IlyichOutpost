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

public:
	Wave(int enemyCount);
	~Wave(void);

	bool AddEnemy(CCScene *scene, Waypoint *waypoint);
};

