#pragma once
#include "cocos2d.h"

#include "Waypoint.h"
#include "Enemy.h"

#include <vector>

using namespace cocos2d;

class Wave
{	
	static int currentWaveNumber;
	static int enemyCount;
	int createdEnemies;

	CCScene *scene; 
	Waypoint *waypoint;

	vector<Enemy *> aliveEnemies;

	void CreateEnemies(EnemyType eType, int count);
	void  AlignEnemyCount(EnemyType eType);

public:
	Wave(CCScene *scene, Waypoint *waypoint);
	static Wave* NextWave();
	~Wave(void);

	bool AddEnemy();
	int GetCurrentWaveNumber();

	int GetEnemyCount();
	CCPoint GetEnemyPosition(const int index);
	void MakeDamage(const int index, const int health);
};

