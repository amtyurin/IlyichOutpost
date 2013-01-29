#pragma once
#include "cocos2d.h"
#include "Wave.h"

using namespace cocos2d;

enum OutpostType{
	OUTPOST_TYPE_ENEMY = 1,
	OUTPOST_TYPE_OUR
};

class Outpost
{
	float originalHealthScale;
	int healthTotal;
	int healthCurrent;
	CCRect rect;
	OutpostType outpostType;

	CCSprite *sprite;
	CCSprite *spriteHealth;
	CCScene *scene;

public:
	Outpost(CCScene *scene, OutpostType outpostType, CCRect rect);
	~Outpost(void);

	bool MakeDamage();
	OutpostType GetOutpostType();
	bool isTargetInRange(CCPoint ccp);
};

