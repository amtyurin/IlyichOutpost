#include "TouchableTowerSprite.h"
#include "PassingMap.h"


TouchableTowerSprite::TouchableTowerSprite(void)
{
	origPos = ccp(0,0);
}


TouchableTowerSprite::~TouchableTowerSprite(void)
{
}

void TouchableTowerSprite::ReturnToOriginalPosition(){
	this->sprite->setPosition(origPos);
}

void TouchableTowerSprite::SaveInitialPosition(){
	origPos = this->sprite->getPosition();
}