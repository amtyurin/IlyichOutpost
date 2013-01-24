#pragma once
#include "cocos2d.h"
#include "Wave.h"

enum TowerTypes{
	MACHINE_GUN=1,
	HEAVY_GUN=2
};

class Tower
{
private:
	int fireSpeed;
	int fireRadius;
	int damage;
	float normRotateX;
	float normRotateY;
	cocos2d::CCPoint position;
	cocos2d::CCSprite *spritePtr;
	Tower(void);

public:
	Tower(int type, cocos2d::CCPoint _position);
	Tower(int _damage, int _fireSpeed, int _fireRadius, cocos2d::CCPoint _position);
	~Tower(void);
	float getX();
	float getY();
	void setX(float newX);
	void setY(float newY);
	cocos2d::CCSprite *getSprite();
	
};

