#include "TouchableTowerSprite.h"
#include "PassingMap.h"


TouchableSprite::TouchableSprite(void)
{
	origPos = ccp(0,0);
}


TouchableSprite::~TouchableSprite(void)
{
}

void TouchableSprite::ReturnToOriginalPosition(){
	this->sprite->setPosition(origPos);
}

void TouchableSprite::SaveInitialPosition(){
	origPos = this->sprite->getPosition();
}