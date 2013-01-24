#include "Enemy.h"

#include "PassingMap.h"

Enemy::Enemy(EnemyType eType, CCScene *scene, Waypoint *way)
{
	this->waypoint = way;
	this->scene = scene;
	currentPoint = 0;

	char *image = NULL;

	switch(eType)
	{
		case ENEMY_SOLDER:
			this->healthCurrent = this->healthTotal = 50;
			speed = 10;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_SOLDER:
			this->healthCurrent = this->healthTotal = 100;
			speed = 10;
			image = "enemy.png";
			break;
		case ENEMY_HORSEMAN:
			this->healthCurrent = this->healthTotal = 150;
			speed = 25;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_HORSEMAN:
			this->healthCurrent = this->healthTotal = 300;
			speed = 20;
			image = "enemy.png";
			break;
		case ENEMY_MACHINEGUN_CART:
			this->healthCurrent = this->healthTotal = 500;
			speed = 20;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_MACHINEGUN_CART:
			this->healthCurrent = this->healthTotal = 750;
			speed = 15;
			image = "enemy.png";
			break;
		case ENEMY_ARMORED_CAR:
			this->healthCurrent = this->healthTotal = 1000;
			speed = 15;
			image = "enemy.png";
			break;
		case ENEMY_TANK:
			this->healthCurrent = this->healthTotal = 1500;
			speed = 10;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_TANK:
			this->healthCurrent = this->healthTotal = 2000;
			speed = 7;
			image = "enemy.png";
			break;
		default:
			CCLog("Wrong enemy type!");
			this->healthCurrent = this->healthTotal = 50;
			speed = 10;
			image = "enemy.png";
			break;
	}

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

void Enemy::SetSpeed(const int speed)
{
	this->speed = speed;
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
	  //MakeDamage(60);
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

CCPoint Enemy::GetPosition()
{
	return sprite->getPosition();
}