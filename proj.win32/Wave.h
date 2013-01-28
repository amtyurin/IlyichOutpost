#pragma once
#include "cocos2d.h"

#include "Waypoint.h"
#include "Enemy.h"
#include "MoneyManager.h"

#include <vector>

using namespace cocos2d;

class Wave
{	
	static int currentWaveNumber;
	int runningEnemies;

	CCScene *scene; 
	Waypoint *waypoint;

	MoneyManager *moneyManager;

	vector<Enemy *> aliveEnemies;

	void CreateEnemies(const EnemyType eType, const  int count);
	void  AlignEnemyCount(const EnemyType eType, const int enemyInitialCount);

public:
	Wave(CCScene *scene, Waypoint *waypoint, MoneyManager *moneyManager);
	static Wave* NextWave();
	~Wave(void);

	bool StartEnemy();
	int GetCurrentWaveNumber();

	int GetEnemyCount();
	CCPoint GetEnemyPosition(const int index);
	void MakeDamage(const int index, const int health);
};

