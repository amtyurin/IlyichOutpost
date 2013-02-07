#include "TouchableTowerSprite.h"


TouchableTowerSprite::TouchableTowerSprite(void)
{
}


TouchableTowerSprite::~TouchableTowerSprite(void)
{
}

void TouchableTowerSprite::ReturnToCell(){
	this->sprite->setPositionX(800 - (this->cellX+1)*36);
	this->sprite->setPositionY(cellY*50 + 100);
}