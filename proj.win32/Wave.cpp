#include "Wave.h"

#include "Enemy.h"

Wave::Wave(int enemyCount)
{
	currentWaveNumber = 0;
	this->enemyCount = enemyCount;
	createdEnemies = 0;
	timeout = 0;
}


Wave::~Wave(void)
{
}

bool Wave::AddEnemy(CCScene *scene, Waypoint *waypoint)
{
	if (createdEnemies < enemyCount)
	{
		Enemy *mob1 = new Enemy("enemy.png");
		mob1->SetHealth(100);
		mob1->SetWaypoint(waypoint);
		mob1->SetSpeed(15);	
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
