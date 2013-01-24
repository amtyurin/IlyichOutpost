#include "Wave.h"

#include "Enemy.h"

Wave::Wave(int enemyCount, int currentWaveNumber)
{
	this->currentWaveNumber = currentWaveNumber;
	this->enemyCount = enemyCount;
	createdEnemies = 0;
	aliveEnemies.resize(0);
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
		Enemy *mob = new Enemy("enemy.png");
		mob->SetHealthTotal(health);
		mob->SetWaypoint(waypoint);
		mob->SetSpeed(speed);	
		mob->SetScene(scene);

		aliveEnemies.push_back(mob);
	
		mob->Start();

		createdEnemies++;

		return true;
	}
	else
	{
		CCLog("All enemies were created");

		return false;
	}
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
