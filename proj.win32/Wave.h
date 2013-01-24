#pragma once
#include "cocos2d.h"

#include "Waypoint.h"

using namespace cocos2d;

class Wave : public CCObject
{	
	int currentWaveNumber;
	int enemyCount;
	int createdEnemies;

public:
	Wave(int enemyCount, int currentWaveNumber);
	~Wave(void);

	bool AddEnemy(CCScene *scene, Waypoint *waypoint, int health, int speed);
	int GetCurrentWaveNumber();
	int GetEnemyCount();
};

