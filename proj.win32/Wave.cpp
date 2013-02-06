#include "Wave.h"

#include "Enemy.h"

#include <algorithm>

int Wave::currentWaveNumber = 0;

void Wave::CreateEnemyTypeMap(const EnemyType eType,const int count)
{
	for (int i = 0; i < count; i++)
	{
		enemyTypeMap.push_back(eType);
	}
}

void Wave::AlignEnemyCount(const EnemyType eType, const int enemyInitialCount)
{
	CreateEnemyTypeMap(eType, enemyInitialCount - this->enemyTypeMap.size());
}

Wave::Wave(CCScene *scene, Waypoint *waypoint, MoneyManager *moneyManager)
{	
	this->createdEnemies = 0;
	this->enemyCountForWave = 0;
	this->aliveEnemies.resize(0);
	this->enemyTypeMap.resize(0);

	this->scene = scene;
	this->waypoint = waypoint;
	this->moneyManager = moneyManager;

	currentWaveNumber++;
	switch(Wave::currentWaveNumber)
	{
		case 1:
			this->enemyCountForWave = 10;
			CreateEnemyTypeMap(ENEMY_SOLDIER, this->enemyCountForWave);
			break;
		case 2:
			this->enemyCountForWave = 20;
			CreateEnemyTypeMap(ENEMY_SOLDIER, this->enemyCountForWave * 2 / 3);
			CreateEnemyTypeMap(ENEMY_HEAVY_SOLDIER, this->enemyCountForWave / 3);
			AlignEnemyCount(ENEMY_SOLDIER, this->enemyCountForWave);
			break;	
		default:
			if (Wave::currentWaveNumber > 1){
				this->enemyCountForWave = Wave::currentWaveNumber * 12;
				int parts = sqrt((float)Wave::currentWaveNumber);
				int maxEnemyType = min(parts, MAX_ENEMY_NUMBER - 1);
				for (int i = 1; i <= maxEnemyType; i++){
					CreateEnemyTypeMap(static_cast<EnemyType>(i), this->enemyCountForWave / parts);
				}
				AlignEnemyCount(static_cast<EnemyType>(maxEnemyType), this->enemyCountForWave);
			}
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
	if (this->createdEnemies < this->enemyCountForWave){	
		Enemy *mob = new Enemy(moneyManager, enemyTypeMap[this->createdEnemies], scene, waypoint);
		this->aliveEnemies.push_back(mob);
		mob->Start();		
		this->createdEnemies++;
		return true;
	}
	else{
		CCLog("All enemies were created");
		return false;
	}
}

CCPoint Wave::GetEnemyPosition(const size_t index)
{
	if (index >= 0 && index < this->aliveEnemies.size())
	{
		return this->aliveEnemies[index]->GetPosition();
	}

	CCLog("GetEnemyPosition: Wrong enemy index %d, count %d", index,aliveEnemies.size() );

	return ccp(0,0);
}

void Wave::MakeDamage(const size_t index, const int health)
{
	if (index >= 0 && index < this->aliveEnemies.size())
	{
		bool killed = this->aliveEnemies[index]->MakeDamage(health);
		if (killed)	{
			aliveEnemies.erase(std::remove(aliveEnemies.begin(), aliveEnemies.end(), aliveEnemies[index]), aliveEnemies.end());
		}
		return;
	}

	CCLog("MakeDamage: Wrong enemy index %d, count %d", index,aliveEnemies.size() );
}

bool Wave::AllEnemiesCreated()
{
	return ((this->enemyCountForWave - this->createdEnemies) <= 0);
}