#pragma once
#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "Waypoint.h"
#include "Wave.h"

class MainFieldScene : public cocos2d::CCLayer
{
	Waypoint way;
	Wave *wave1;

public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainFieldScene);

	// Menu items handlers
	void CreateScene(CCObject* sender);		

	void addEnemies(float dt);
};

