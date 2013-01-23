#pragma once
#include "cocos2d.h"

class Tower
{
private:
	int fireSpeed;
	int fireRadius;
	int damage;
	float normRotateX;
	float normRotateY;
	cocos2d::CCPoint position;

public:
	Tower(void);
	Tower(int _damage, int _fireSpeed, int _fireRadius);
	~Tower(void);
	float getX();
	float getY();
	void setX(float newX);
	void setY(float newY);

	
};

