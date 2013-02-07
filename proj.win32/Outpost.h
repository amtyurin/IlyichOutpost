#pragma once
#include "cocos2d.h"
#include "Wave.h"

enum OutpostType{
	OUTPOST_TYPE_ENEMY = 1,
	OUTPOST_TYPE_OUR
};

class Outpost
{
	float originalHealthScale;
	int healthTotal;
	int healthCurrent;
	cocos2d::CCRect rect;
	OutpostType outpostType;

	cocos2d::CCSprite *sprite;
	cocos2d::CCSprite *spriteHealth;
	cocos2d::CCScene *scene;

public:
	Outpost(cocos2d::CCScene *scene, OutpostType outpostType, cocos2d::CCRect rect);
	~Outpost(void);

	bool MakeDamage();
	OutpostType GetOutpostType();
	bool isTargetInRange(cocos2d::CCPoint ccp);
};

