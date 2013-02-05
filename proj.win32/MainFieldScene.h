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

#include <set>

typedef vector<Tower*>::iterator towerArrayIterator;

using namespace cocos2d;

#define TAG_TOWER_SCENE_MASK	1 << 12
#define TAG_TOWER_MENU_MASK		1 << 13

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

	PanelGeneral *panelGeneral;
	PanelTowers *panelTower;

	MoneyManager *moneyManager;

	CCSprite *touchedPanelSprite;
	CCSprite *touchedTowerSprite;
	CCSprite *movingTowerSprite;
	vector<CCSprite *> touchableSprites;

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

	void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
	//bool ccTouchBegan(CCTouch *touch, CCEvent *pEvent);

	void addTouchableSprite(CCSprite * child, int tag);
	void removeTouchableSprite(CCSprite * child);
};
