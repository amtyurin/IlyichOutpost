#pragma once
#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "Waypoint.h"
#include "Wave.h"
#include "Tower.h"
#include "TowerArray.h"
#include "OutpostArray.h"

#include "PanelGeneral.h"
#include "PanelTowers.h"

#include "MoneyManager.h"
#include "UILayer.h"

#include <set>

typedef std::vector<Tower*>::iterator towerArrayIterator;

using namespace cocos2d;

class MainFieldScene : public cocos2d::CCLayer
{
	Waypoint way;
	Wave *wave;

	int wavesCount;
	int waveTimout;
	float gameLogicTimeout;
	int enemyRespawnTime;
	TowerArray *towers;
	OutpostArray outposts;

	UILayer *UI;

	PanelGeneral *panelGeneral;
	PanelTowers *panelTower;

	MoneyManager *moneyManager;	

	void DisplayText(const int tag, const char *text, const char *font, const int size, const int locX, const int locY);
	void StopGame(char *text);

	void StartWave(float dt);
	void WaveGenerateEnemyProcess(float dt);
	void GameLogic(float dt);
	void addTower(TowerTypes towerType, cocos2d::CCPoint position);
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // implement the "static node()" method manually
    CREATE_FUNC(MainFieldScene);

	// Menu items handlers
	void CreateScene(CCObject* sender);		
};
