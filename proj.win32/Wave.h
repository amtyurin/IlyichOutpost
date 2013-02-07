#pragma once
#include "cocos2d.h"

#include "Waypoint.h"
#include "Enemy.h"
#include "MoneyManager.h"

#include <vector>

class Wave
{	
	static int currentWaveNumber;
	int createdEnemies;
	int enemyCountForWave;

	cocos2d::CCScene *scene; 
	Waypoint *waypoint;

	MoneyManager *moneyManager;

	std::vector<Enemy *> aliveEnemies;
	std::vector<EnemyType> enemyTypeMap;

	void CreateEnemyTypeMap(const EnemyType eType, const  int count);
	void  AlignEnemyCount(const EnemyType eType, const int enemyInitialCount);

public:
	Wave(cocos2d::CCScene *scene, Waypoint *waypoint, MoneyManager *moneyManager);
	static Wave* NextWave();
	~Wave(void);

	bool StartEnemy();
	int GetCurrentWaveNumber();
	int GetEnemyCount();
	cocos2d::CCPoint GetEnemyPosition(const size_t index);
	bool AllEnemiesCreated();

	void MakeDamage(const size_t index, const int health);
};

