#include "Wave.h"

#include "Enemy.h"

#include <algorithm>

int Wave::currentWaveNumber = 0;

void Wave::CreateEnemies(const EnemyType eType,const int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy *mob = new Enemy(moneyManager, eType, scene, waypoint);
		this->aliveEnemies.push_back(mob);
	}
}

void Wave::AlignEnemyCount(const EnemyType eType, const int enemyInitialCount)
{
	int diff = enemyInitialCount - aliveEnemies.size();
	for (int i = 0; i < diff; i++)
	{
		Enemy *mob = new Enemy(moneyManager, eType, scene, waypoint);
		this->aliveEnemies.push_back(mob);
	}
}

Wave::Wave(CCScene *scene, Waypoint *waypoint, MoneyManager *moneyManager)
{
	this->runningEnemies = 0;
	this->aliveEnemies.resize(0);

	this->scene = scene;
	this->waypoint = waypoint;
	this->moneyManager = moneyManager;

	currentWaveNumber++;
	int enemyInitialCount = 0;
	switch(Wave::currentWaveNumber)
	{
		case 1:
			enemyInitialCount = 10;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount);
			break;
		case 2:
			enemyInitialCount = 20;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 2);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 2);
			AlignEnemyCount(ENEMY_HEAVY_SOLDIER,enemyInitialCount);
			break;
		case 3:
			enemyInitialCount = 30;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 3);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 3);
			CreateEnemies(ENEMY_HORSEMAN, enemyInitialCount / 3);
			AlignEnemyCount(ENEMY_HEAVY_SOLDIER,enemyInitialCount);
			break;
		case 4:
			enemyInitialCount = 40;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 4);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 4);
			CreateEnemies(ENEMY_HORSEMAN, enemyInitialCount / 4);
			CreateEnemies(ENEMY_HEAVY_HORSEMAN, enemyInitialCount / 4);
			AlignEnemyCount(ENEMY_HEAVY_SOLDIER,enemyInitialCount);
			break;
		case 5:
			enemyInitialCount = 50;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 5);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 5);
			CreateEnemies(ENEMY_HORSEMAN, enemyInitialCount / 5);
			CreateEnemies(ENEMY_HEAVY_HORSEMAN, enemyInitialCount / 5);
			CreateEnemies(ENEMY_MACHINEGUN_CART, enemyInitialCount / 5);
			AlignEnemyCount(ENEMY_HEAVY_TANK,enemyInitialCount);
			break;
	}	
}

Wave::~Wave(void)
{
}

int Wave::GetCurrentWaveNumber()
{
	return this->currentWaveNumber;
}

int Wave::GetEnemyCount()
{
	return this->aliveEnemies.size();
}

bool Wave::StartEnemy()
{
	if (this->runningEnemies < this->aliveEnemies.size()){	
		this->aliveEnemies[runningEnemies]->Start();		
		this->runningEnemies++;
		return true;
	}
	else{
		CCLog("All enemies were created");
		return false;
	}
}

CCPoint Wave::GetEnemyPosition(const int index)
{
	if (index >= 0 && index < this->aliveEnemies.size())
	{
		return this->aliveEnemies[index]->GetPosition();
	}

	CCLog("GetEnemyPosition: Wrong enemy index %d, count %d", index,aliveEnemies.size() );

	return ccp(0,0);
}

void Wave::MakeDamage(const int index, const int health)
{
	if (index >= 0 && index < this->aliveEnemies.size())
	{
		bool killed = this->aliveEnemies[index]->MakeDamage(health);
		if (killed)	{
			aliveEnemies.erase(std::remove(aliveEnemies.begin(), aliveEnemies.end(), aliveEnemies[index]), aliveEnemies.end());
			runningEnemies--;
		}
		return;
	}

	CCLog("MakeDamage: Wrong enemy index %d, count %d", index,aliveEnemies.size() );
}
