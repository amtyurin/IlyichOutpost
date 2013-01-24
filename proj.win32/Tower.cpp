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
			this->fireRadius = 150;
			this->spritePtr = CCSprite::create("machineGun.png");
		case HEAVY_GUN:
			this->damage = 20;
			this->fireSpeed = 5;
			this->fireRadius = 170;
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

CCSprite * Tower::getSprite() const{
	return this->spritePtr;
}

const bool Tower::operator < (const Tower &tower) const{
	/*int compareValue = this->position.x * 10000 + this->position.y;
	int compareValue2 = tower.getX() * 10000 + tower.getY();
	return compareValue < compareValue2;*/
	return (this < &tower);
}

void Tower::turnTo(const CCPoint point){
	this->spritePtr->setRotationX(point.x);
	this->spritePtr->setRotationY(point.y);
}

const bool Tower::operator> (const Tower &tower) const{
	return !(*this < tower);
}

const bool Tower::isTargetInRange(CCPoint target) const{
	double dX = abs(this->position.x-target.x);
	double dY = abs(this->position.y - target.y);
	double range = sqrt(pow(dX, 2) + pow(dY, 2));
	if (range <= this->fireRadius) {
		return true;
	}else{
		return false;
	}
}