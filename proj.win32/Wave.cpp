#include "Wave.h"

#include "Enemy.h"

#include <algorithm>

int Wave::currentWaveNumber = 0;
int Wave::enemyCount = 0;
#define JOKERNN_DEBUG
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
	int diff = enemyCount - aliveEnemies.size();
	for (int i = 0; i < diff; i++)
	{
		Enemy *mob = new Enemy(this, eType, scene, waypoint);
		aliveEnemies.push_back(mob);
	}
}

Wave::Wave(CCScene *scene, Waypoint *waypoint)
{
	createdEnemies = 0;
	aliveEnemies.resize(0);

	this->scene = scene;
	this->waypoint = waypoint;

	currentWaveNumber++;
	switch(Wave::currentWaveNumber)
	{
		case 1:
			enemyCount = 10;
#ifdef JOKERNN_DEBUG
			enemyCount = 1;
#endif
			CreateEnemies(ENEMY_SOLDER, enemyCount);
			break;
		case 2:
			enemyCount = 20;
			CreateEnemies(ENEMY_SOLDER, enemyCount / 2);
			CreateEnemies(ENEMY_HEAVY_SOLDER, enemyCount / 2);
			AlignEnemyCount(ENEMY_HEAVY_SOLDER);
			break;
		case 3:
			enemyCount = 30;
			CreateEnemies(ENEMY_SOLDER, enemyCount / 3);
			CreateEnemies(ENEMY_HEAVY_SOLDER, enemyCount / 3);
			CreateEnemies(ENEMY_HORSEMAN, enemyCount / 3);
			AlignEnemyCount(ENEMY_HEAVY_SOLDER);
			break;
		case 4:
			enemyCount = 40;
			CreateEnemies(ENEMY_SOLDER, enemyCount / 4);
			CreateEnemies(ENEMY_HEAVY_SOLDER, enemyCount / 4);
			CreateEnemies(ENEMY_HORSEMAN, enemyCount / 4);
			CreateEnemies(ENEMY_HEAVY_HORSEMAN, enemyCount / 4);
			AlignEnemyCount(ENEMY_HEAVY_SOLDER);
			break;
		case 5:
			enemyCount = 50;
			CreateEnemies(ENEMY_SOLDER, enemyCount / 5);
			CreateEnemies(ENEMY_HEAVY_SOLDER, enemyCount / 5);
			CreateEnemies(ENEMY_HORSEMAN, enemyCount / 5);
			CreateEnemies(ENEMY_HEAVY_HORSEMAN, enemyCount / 5);
			CreateEnemies(ENEMY_MACHINEGUN_CART, enemyCount / 5);
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
	return enemyCount;
}

bool Wave::AddEnemy()
{
	if (createdEnemies < enemyCount)
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
	enemyCount--;
	aliveEnemies.erase(std::remove(aliveEnemies.begin(), aliveEnemies.end(), enemy), aliveEnemies.end());
}

CCPoint Wave::GetEnemyPosition(const int index)
{
	if (index >= 0 && index < aliveEnemies.size())
	{
		return aliveEnemies[index]->GetPosition();
	}

	CCLog("Wrong enemy index %d", index);

	return ccp(0,0);
}

void Wave::MakeDamage(const int index, const int health)
{
	if (index >= 0 && index < aliveEnemies.size())
	{
		aliveEnemies[index]->MakeDamage(health);
	}

	CCLog("Wrong enemy index %d", index);
}
