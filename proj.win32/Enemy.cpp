#include "Enemy.h"

#include "PassingMap.h"
#include "Wave.h"

Enemy::Enemy(void *wave, const EnemyType eType, CCScene *scene, Waypoint *way)
{
	this->wave = wave;
	this->waypoint = way;
	this->scene = scene;
	this->currentPoint = 0;

	char *image = NULL;

	switch(eType)
	{
		case ENEMY_SOLDER:
			this->healthCurrent = this->healthTotal = 50;
			this->speed = 10;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_SOLDER:
			this->healthCurrent = this->healthTotal = 100;
			this->speed = 10;
			image = "enemy.png";
			break;
		case ENEMY_HORSEMAN:
			this->healthCurrent = this->healthTotal = 150;
			this->speed = 25;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_HORSEMAN:
			this->healthCurrent = this->healthTotal = 300;
			this->speed = 20;
			image = "enemy.png";
			break;
		case ENEMY_MACHINEGUN_CART:
			this->healthCurrent = this->healthTotal = 500;
			this->speed = 20;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_MACHINEGUN_CART:
			this->healthCurrent = this->healthTotal = 750;
			this->speed = 15;
			image = "enemy.png";
			break;
		case ENEMY_ARMORED_CAR:
			this->healthCurrent = this->healthTotal = 1000;
			this->speed = 15;
			image = "enemy.png";
			break;
		case ENEMY_TANK:
			this->healthCurrent = this->healthTotal = 1500;
			this->speed = 10;
			image = "enemy.png";
			break;
		case ENEMY_HEAVY_TANK:
			this->healthCurrent = this->healthTotal = 2000;
			this->speed = 7;
			image = "enemy.png";
			break;
		default:
			CCLog("Wrong enemy type!");
			this->healthCurrent = this->healthTotal = 50;
			this->speed = 10;
			image = "enemy.png";
			break;
	}

	this->sprite = CCSprite::create(image, CCRectMake(0,0,PassingMap::MAP_CELL_SIZE, PassingMap::MAP_CELL_SIZE) );
	this->sprite->setPosition(ccp(-100, -100));

	// add health line
	this->spriteHealth = CCSprite::create("health_line.png");

	int posX = this->sprite->getContentSize().width / 2;
	int posY = this->sprite->getContentSize().height;
	this->spriteHealth->setPositionX(posX);
	this->spriteHealth->setPositionY(posY);	

	this->sprite->addChild(this->spriteHealth, 1);

	this->scene->addChild(this->sprite);
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
	((Wave *)(this->wave))->RemoveEnemy(this);

	this->sprite->cleanup();
	this->sprite->removeAllChildrenWithCleanup(true);
	this->scene->removeChild(this->sprite, true);
}

void Enemy::CheckPointReached(Enemy *sender)
{
  Cell *curCell = waypoint->GetPoint(currentPoint);
  Cell *nextCell = waypoint->GetPoint(currentPoint + 1);

  if (curCell && nextCell)
  {
	  this->sprite->setPosition(ccp(curCell->x, curCell->y));

	  //calculate duration
	  float actualDuration = ccpDistance(ccp(curCell->x, curCell->y), ccp(nextCell->x, nextCell->y)) / this->speed;

      // Create the actions
      CCFiniteTimeAction* actionMove = CCMoveTo::create( actualDuration, ccp(nextCell->x, nextCell->y) );

      CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(Enemy::CheckPointReached));
      this->sprite->runAction( CCSequence::create(actionMove, actionMoveDone, NULL) );

	  this->currentPoint++;

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
void Enemy::MakeDamage(const int health)
{
	this->healthCurrent -= health;
	if (healthCurrent <= 0)
	{
		this->sprite->cleanup();

		this->spriteHealth->setScaleX(0);

		//CCParticleExplosion *particle = CCParticleExplosion::createWithTotalParticles(100);
		//particle->setTexture(sprite->getTexture());

		CCFiniteTimeAction* actionKill = CCTwirl::create(ccp(sprite->getContentSize().width / 2, sprite->getContentSize().height / 2), 3, 0.3, ccg(1,1), 0.2);

        CCFiniteTimeAction* actionDestroy = CCCallFuncN::create( this, callfuncN_selector(Enemy::Destroy));
        this->sprite->runAction( CCSequence::create(actionKill, actionDestroy, NULL) );
	}
	else
	{
		this->spriteHealth->setScaleX((float)this->healthCurrent / this->healthTotal);
	}
}

void Enemy::Start()
{ 
	CheckPointReached(this);
}

CCPoint Enemy::GetPosition()
{
	return this->sprite->getPosition();
}