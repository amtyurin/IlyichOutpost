#include "Enemy.h"

#include "PassingMap.h"

Enemy::Enemy(char *image)
{
	healthTotal = healthCurrent = 0;
	waypoint = NULL;
	speed = 0;
	currentPoint = 0;

	sprite = CCSprite::create(image, CCRectMake(0,0,PassingMap::MAP_CELL_SIZE, PassingMap::MAP_CELL_SIZE) );

	// add health line
	spriteHealth = CCSprite::create("health_line.png");

	int posX = sprite->getContentSize().width / 2;
	int posY = sprite->getContentSize().height;
	spriteHealth->setPositionX(posX);
	spriteHealth->setPositionY(posY);	

	sprite->addChild(spriteHealth, 1);
}

Enemy::~Enemy(void)
{
}

void Enemy::SetHealthTotal(const int health)
{
	this->healthCurrent = this->healthTotal = health;
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

void Enemy::Destroy(Enemy *sender)
{
	sprite->cleanup();
	sprite->removeAllChildrenWithCleanup(true);
	scene->removeChild(sprite, true);
}

void Enemy::CheckPointReached(Enemy *sender)
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

      CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(Enemy::CheckPointReached));
      sprite->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );

	  currentPoint++;

	  // For testing
	  MakeDamage(60);
  }
  else
  {
	  CCLog("Enemy reached destination");
	  Destroy(sender);
  }
}

// true - if killed
bool Enemy::MakeDamage(const int health)
{
	healthCurrent -= health;
	if (healthCurrent <= 0)
	{
		sprite->cleanup();

		spriteHealth->setScaleX(0);

		//CCParticleExplosion *particle = CCParticleExplosion::createWithTotalParticles(100);
		//particle->setTexture(sprite->getTexture());

		CCFiniteTimeAction* actionKill = CCTwirl::create(ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2), 3, 0.3, ccg(1,1), 0.2);

        CCFiniteTimeAction* actionDestroy = CCCallFuncN::create( this, callfuncN_selector(Enemy::Destroy));
        sprite->runAction( CCSequence::create(actionKill, actionDestroy, NULL) );

		return true;
	}
	else
	{
		spriteHealth->setScaleX((float)healthCurrent / healthTotal);
	}

	return false;
}

void Enemy::Start()
{ 
	scene->addChild(sprite);

	CheckPointReached(this);
}