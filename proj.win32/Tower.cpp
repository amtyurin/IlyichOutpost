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
	//CCLog("Type: %d\n", type);
	switch (type){
		case MACHINE_GUN:
			this->damage = 10;
			this->fireSpeed = 10;
			this->fireRadius = 50;
			this->spritePtr = CCSprite::create("machineGun.png");
			break;
		case HEAVY_GUN:
			this->damage = 20;
			this->fireSpeed = 5;
			this->fireRadius = 70;
			this->spritePtr = CCSprite::create("machineGun.png");
			break;
		default:
			this->damage = 0;
			this->fireSpeed = 0;
			this->fireRadius = 0;
	}
	this->position=_position;
	this->spritePtr->setPosition(_position);
	//CCLog("FireRadius: %d\n", this->fireRadius);
}


Tower::~Tower(void){
	//this->spritePtr->release();
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
	double dx = abs(this->position.x - point.x);
	double dy = abs(this->position.y - point.y);
	/*if (dy <= 0.0000001){
		dy = 0.1;
	}*/
	double tanOfAngle = (dx/dy);
	double angle = atan(tanOfAngle)*57.2957795135;
	CCLog("%f\t%f\t%f\t%f\n", dx, dy, tanOfAngle, angle);
	if (angle >=0 && angle <=360){
		this->spritePtr->setRotation(angle);
	}
	//CCLog("%f\t%f\n", angle, angleDegrees);
	/*double dX = abs(this->position.x - point.x);
	double dY = abs(this->position.y - point.y);
	double angleSin = (dX/dY);
	double angle = asin(angleSin);
	this->spritePtr->setRotation(angle*180/3.14);*/
	//this->spritePtr->setRotationX(point.x);
	//this->spritePtr->setRotationY(point.y);
}

const bool Tower::operator> (const Tower &tower) const{
	return !(*this < tower);
}

const bool Tower::isTargetInRange(CCPoint target) const{
	//std::cout<<this->position.x<<"\t"<<this->position.y<<std::endl;
	//std::cout<<target.x<<"\t"<<target.y<<std::endl;
	double dX = abs(this->position.x - target.x);
	double dY = abs(this->position.y - target.y);
	double range = sqrt(pow(dX, 2) + pow(dY, 2));
	//CCLog("%f\t%d\n", range, this->fireRadius);
	if (range <= this->fireRadius) {
		return true;
	}else{
		return false;
	}
}