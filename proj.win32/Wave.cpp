#include "Wave.h"

#include "Enemy.h"

#include <algorithm>

int Wave::currentWaveNumber = 0;

void Wave::CreateEnemies(const EnemyType eType,const int count)
{
	for (int i = 0; i < count; i++)
	{
		Enemy *mob = new Enemy(this, eType, scene, waypoint);
		aliveEnemies.push_back(mob);
	}
}

void Wave::AlignEnemyCount(const EnemyType eType)
{
	int diff = enemyInitialCount - aliveEnemies.size();
	for (int i = 0; i < diff; i++)
	{
		Enemy *mob = new Enemy(this, eType, scene, waypoint);
		aliveEnemies.push_back(mob);
	}
}

Wave::Wave(CCScene *scene, Waypoint *waypoint)
{
	enemyInitialCount = 0;
	createdEnemies = 0;
	aliveEnemies.resize(0);

	this->scene = scene;
	this->waypoint = waypoint;

	currentWaveNumber++;
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
			AlignEnemyCount(ENEMY_HEAVY_SOLDIER);
			break;
		case 3:
			enemyInitialCount = 30;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 3);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 3);
			CreateEnemies(ENEMY_HORSEMAN, enemyInitialCount / 3);
			AlignEnemyCount(ENEMY_HEAVY_SOLDIER);
			break;
		case 4:
			enemyInitialCount = 40;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 4);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 4);
			CreateEnemies(ENEMY_HORSEMAN, enemyInitialCount / 4);
			CreateEnemies(ENEMY_HEAVY_HORSEMAN, enemyInitialCount / 4);
			AlignEnemyCount(ENEMY_HEAVY_SOLDIER);
			break;
		case 5:
			enemyInitialCount = 50;
			CreateEnemies(ENEMY_SOLDIER, enemyInitialCount / 5);
			CreateEnemies(ENEMY_HEAVY_SOLDIER, enemyInitialCount / 5);
			CreateEnemies(ENEMY_HORSEMAN, enemyInitialCount / 5);
			CreateEnemies(ENEMY_HEAVY_HORSEMAN, enemyInitialCount / 5);
			CreateEnemies(ENEMY_MACHINEGUN_CART, enemyInitialCount / 5);
			AlignEnemyCount(ENEMY_HEAVY_TANK);
			break;
	}	
}

Wave::~Wave(void)
{
}

int Wave::GetCurrentWaveNumber()
{
	return currentWaveNumber;
}

int Wave::GetEnemyCount()
{
	return aliveEnemies.size();
}

bool Wave::AddEnemy()
{
	if (createdEnemies < enemyInitialCount)
	{				
		aliveEnemies[createdEnemies]->Start();

		createdEnemies++;

		return true;
	}
	else
	{
		CCLog("All enemies were created");

		return false;
	}
}
void Wave::RemoveEnemy(Enemy *enemy)
{
	aliveEnemies.erase(std::remove(aliveEnemies.begin(), aliveEnemies.end(), enemy), aliveEnemies.end());
}

CCPoint Wave::GetEnemyPosition(const int index)
{
	if (index >= 0 && index < aliveEnemies.size())
	{
		return aliveEnemies[index]->GetPosition();
	}

	CCLog("GetEnemyPosition: Wrong enemy index %d, count %d", index,aliveEnemies.size() );

	return ccp(0,0);
}

void Wave::MakeDamage(const int index, const int health)
{
	if (index >= 0 && index < aliveEnemies.size())
	{
		aliveEnemies[index]->MakeDamage(health);
		return;
	}

	CCLog("MakeDamage: Wrong enemy index %d, count %d", index,aliveEnemies.size() );
}
