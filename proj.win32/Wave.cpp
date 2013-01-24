#include "Wave.h"

#include "Enemy.h"

Wave::Wave(int enemyCount, int currentWaveNumber)
{
	this->currentWaveNumber = currentWaveNumber;
	this->enemyCount = enemyCount;
	createdEnemies = 0;
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

bool Wave::AddEnemy(CCScene *scene, Waypoint *waypoint, int health, int speed)
{
	if (createdEnemies < enemyCount)
	{
		Enemy *mob1 = new Enemy("enemy.png");
		mob1->SetHealthTotal(health);
		mob1->SetWaypoint(waypoint);
		mob1->SetSpeed(speed);	
		mob1->SetScene(scene);
	
		mob1->Start();

		createdEnemies++;

		return true;
	}
	else
	{
		return false;
	}
}
