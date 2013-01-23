#include "Tower.h"


Tower::Tower(void)
{
}

Tower::Tower(int _damage, int _fireSpeed, int _fireRadius): 
damage(_damage), fireSpeed(_fireSpeed), fireRadius(_fireRadius){}


Tower::~Tower(void){
}

void Tower::setX(float newX){
	this->position.x = newX;
}

void Tower::setY(float newY){
	this->position.y = newY;
}