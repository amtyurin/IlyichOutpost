#pragma once
#include "cocos2d.h"

#include "Waypoint.h"
#include "Enemy.h"

#include <vector>

using namespace cocos2d;

class Wave : public CCObject
{	
	int currentWaveNumber;
	int enemyCount;
	int createdEnemies;

	vector<Enemy *> aliveEnemies;

public:
	Wave(int enemyCount, int currentWaveNumber);
	~Wave(void);

	bool AddEnemy(CCScene *scene, Waypoint *waypoint, int health, int speed);
	int GetCurrentWaveNumber();

	int GetEnemyCount();
	CCPoint GetEnemyPosition(const int index);
	void MakeDamage(const int index, const int health);
};

