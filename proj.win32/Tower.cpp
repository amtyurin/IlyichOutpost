#include "Tower.h"

using namespace cocos2d;

Tower::Tower(void)
{
}

Tower::Tower(int _damage, int _fireSpeed, int _fireRadius, CCPoint _position): 
damage(_damage), fireSpeed(_fireSpeed), fireRadius(_fireRadius), position(_position){
	spritePtr = CCSprite::create("machineGun.png");
	spritePtr->setPosition(this->position);
}

Tower::Tower(int type, CCPoint _position){
	switch (type){
		case MACHINE_GUN:
			this->damage = 10;
			this->fireSpeed = 10;
			this->fireRadius = 50;
			this->spritePtr = CCSprite::create("machineGun.png");
		case HEAVY_GUN:
			this->damage = 20;
			this->fireSpeed = 5;
			this->fireRadius = 70;
			this->spritePtr = CCSprite::create("machineGun.png");
		default:
			this->damage = 0;
			this->fireSpeed = 0;
			this->fireRadius = 0;
	}
	this->position=_position;
	this->spritePtr->setPosition(_position);
}


Tower::~Tower(void){
	
}

void Tower::setX(float newX){
	this->position.x = newX;
}

void Tower::setY(float newY){
	this->position.y = newY;
}

CCSprite * Tower::getSprite(){
	return this->spritePtr;
}