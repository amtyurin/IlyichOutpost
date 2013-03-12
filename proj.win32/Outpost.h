#pragma once
#include "cocos2d.h"
#include "Wave.h"

class Outpost
{
	float originalHealthScale;
	int healthTotal;
	int healthCurrent;
	cocos2d::CCRect rect;

	cocos2d::CCSprite *sprite;
	cocos2d::CCSprite *spriteHealth;
	cocos2d::CCScene *scene;

public:
	Outpost(cocos2d::CCScene *scene,  bool our, cocos2d::CCRect rect);
	~Outpost(void);

	bool MakeDamage();
	bool isTargetInRange(cocos2d::CCPoint ccp);
};

