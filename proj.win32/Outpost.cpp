#include "Outpost.h"

using namespace cocos2d;

Outpost::Outpost(CCScene *scene, OutpostType outpostType, CCRect rect)
{
	this->scene = scene;
	this->outpostType = outpostType;
	this->rect = rect;

	char *image = NULL;
	switch(outpostType)
	{
		case OUTPOST_TYPE_ENEMY:
			image = FILE_NAME_IMAGE_OUTPOST_ENEMY;
			this->healthTotal = 100;
			break;
		case OUTPOST_TYPE_OUR:
			image = FILE_NAME_IMAGE_OUTPOST_OUR;
			this->healthTotal = 100;
			break;
		default:
			CCLog("Wrong outpost type!");
			break;
	}
	this->healthCurrent = healthTotal;

	//upgradeble?
	//

	CCSprite *spriteEnemyLocal = CCSprite::create(image);
	float scaleX = rect.size.width / spriteEnemyLocal->getContentSize().width;
	float scaleY = rect.size.height / spriteEnemyLocal->getContentSize().height;
	spriteEnemyLocal->setScaleX(scaleX);
	spriteEnemyLocal->setScaleY(scaleY);
	spriteEnemyLocal->setPosition(ccp(rect.size.width / 2, rect.size.height / 2));

	this->sprite = CCSprite::create();
	this->sprite->addChild(spriteEnemyLocal, 1);
	this->sprite->setContentSize(CCSize(rect.size.width, rect.size.height));
	this->sprite->setPosition(ccp(rect.getMidX(), rect.getMidY()));

	// add health line
	this->spriteHealth = CCSprite::create(FILE_NAME_IMAGE_HEALTH_LINE);

	int posX = this->sprite->getContentSize().width / 2;
	int posY = this->sprite->getContentSize().height + 10;
	this->spriteHealth->setPositionX(posX);
	this->spriteHealth->setPositionY(posY);	
	this->originalHealthScale = rect.size.width / this->spriteHealth->getContentSize().width;
	this->spriteHealth->setScaleX(this->originalHealthScale);

	this->sprite->addChild(this->spriteHealth, 3);

	this->scene->addChild(this->sprite);
}


Outpost::~Outpost(void)
{
}

bool Outpost::MakeDamage()
{
	this->healthCurrent -= this->healthTotal / 10;
	if (healthCurrent <= 0)
	{
		this->spriteHealth->setScaleX(0);

		return true;
	}
	else
	{
		this->spriteHealth->setScaleX(this->originalHealthScale * (float)this->healthCurrent / this->healthTotal);
		return false;
	}
}

OutpostType Outpost::GetOutpostType()
{
	return this->outpostType;
}

bool Outpost::isTargetInRange(CCPoint ccp)
{
	if (ccp.x >= rect.getMinX() && ccp.x <= rect.getMaxX() &&
		ccp.y >= rect.getMinY() && ccp.y <= rect.getMaxY()){
			return true;
	}
	return false;
}
