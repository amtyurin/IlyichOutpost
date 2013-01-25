#pragma once
#include "cocos2d.h"

#include "Waypoint.h"
#include "Enemy.h"

#include <vector>

using namespace cocos2d;

class Wave
{	
	static int currentWaveNumber;
	int enemyInitialCount;
	int createdEnemies;

	CCScene *scene; 
	Waypoint *waypoint;

	vector<Enemy *> aliveEnemies;

	void CreateEnemies(const EnemyType eType, const  int count);
	void  AlignEnemyCount(const EnemyType eType);

public:
	Wave(CCScene *scene, Waypoint *waypoint);
	static Wave* NextWave();
	~Wave(void);

	bool AddEnemy();
	void RemoveEnemy(Enemy *enemy);
	int GetCurrentWaveNumber();

	int GetEnemyCount();
	CCPoint GetEnemyPosition(const int index);
	void MakeDamage(const int index, const int health);
};

