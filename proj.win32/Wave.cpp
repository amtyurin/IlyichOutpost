#include "Wave.h"

#include "Enemy.h"

Wave::Wave(int enemyCount)
{
	currentWaveNumber = 0;
	this->enemyCount = enemyCount;
	createdEnemies = 0;
	timeout = 0;
	scene = NULL;
	waypoint = NULL;
}


Wave::~Wave(void)
{
}

void Wave::AddEnemy(float dt)
{
	Enemy *mob1 = new Enemy("enemy.png");
	mob1->SetHealth(100);
	mob1->SetWaypoint(waypoint);
	mob1->SetSpeed(15);	
	mob1->SetScene(scene);
	
	mob1->Start();

	createdEnemies++;

	if (createdEnemies > enemyCount )
	{
		//this->unschedule( schedule_selector(Wave::AddEnemy));
	}
}

void Wave::Start(CCScene *scene, Waypoint *waypoint)
{
	this->scene = scene;
	this->waypoint = waypoint;

	//AddEnemy(1.0);
	timer.initWithTarget(this, schedule_selector(Wave::AddEnemy));
	timer.setInterval(1.0);
	timer.update(1.0);
	//this->schedule( schedule_selector(Wave::AddEnemy), 1.0 );

	currentWaveNumber++;
	enemyCount *= 2;
	timeout += 5;
}