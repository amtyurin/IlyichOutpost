#include "Enemy.h"

#include "PassingMap.h"

Enemy::Enemy(char *image)
{
	health = 0;
	waypoint = NULL;
	speed = 0;
	currentPoint = 0;

	sprite = CCSprite::create(image, CCRectMake(0,0,PassingMap::MAP_CELL_SIZE, PassingMap::MAP_CELL_SIZE) );
}


Enemy::~Enemy(void)
{
}

void Enemy::SetHealth(const int health)
{
	this->health = health;
}

void Enemy::SetWaypoint(Waypoint *way)
{
	this->waypoint = way;
}

void Enemy::SetSpeed(const int speed)
{
	this->speed = speed;
}

void Enemy::SetScene(CCScene *scene)
{
	this->scene = scene;
}

int Enemy::GetHealth()
{
	return health;
}

int Enemy::GetSpeed()
{
	return speed;
}

void Enemy::MoveFinished(Enemy *sender)
{
  Cell *curCell = waypoint->GetPoint(currentPoint);
  Cell *nextCell = waypoint->GetPoint(currentPoint + 1);

  if (curCell && nextCell)
  {
	  sprite->setPosition(ccp(curCell->x, curCell->y));

	  //calculate duration
	  float actualDuration = ccpDistance(ccp(curCell->x, curCell->y), ccp(nextCell->x, nextCell->y)) / speed;

      // Create the actions
      CCFiniteTimeAction* actionMove = CCMoveTo::create( actualDuration, ccp(nextCell->x, nextCell->y) );

      CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(Enemy::MoveFinished));
      sprite->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );

	  currentPoint++;
  }
  else
  {
	  CCLog("Enemy reached destination");

	  scene->removeChild(sprite, true);
  }
}

void Enemy::Start()
{ 
	scene->addChild(sprite);

	MoveFinished(this);
}