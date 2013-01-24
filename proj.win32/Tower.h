#pragma once
#include "cocos2d.h"
#include "Wave.h"
#include <math.h>

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
	cocos2d::CCSprite *spriteRange;
	Tower(void);

public:
	Tower(int type, cocos2d::CCPoint _position);
	Tower(int _damage, int _fireSpeed, int _fireRadius, cocos2d::CCPoint _position);
	~Tower(void);
	const float getX() const { return position.x;};
	const float getY() const { return position.y;};
	void setX(const float newX);
	void setY(const float newY);
	cocos2d::CCSprite *getSprite() const;
	void turnTo(const cocos2d::CCPoint position);
	const bool operator < (const Tower &tower) const;
	const bool operator > (const Tower &tower) const;
	const bool isTargetInRange(CCPoint target) const;
};

