#include "MainFieldScene.h"

#include "MainMenuScene.h"

#include "PassingMap.h"
#include "Wave.h"

using namespace cocos2d;


CCScene* MainFieldScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainFieldScene *layer = MainFieldScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainFieldScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////

        // 1. Add a menu item with "X" image, which is clicked to quit the program.

        // Create a "close" menu item with close icon, it's an auto release object.
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
            "CloseNormal.png",
            "CloseSelected.png",
            this,
            menu_selector(MainMenu::CreateScene));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

        // Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to MainMenu layer as a child layer.
        this->addChild(pMenu, 1);

		CCSize size = CCDirector::sharedDirector()->getWinSize();

        // 3. Add add background, show the cocos2d splash image.
        CCSprite* pSpriteBg = CCSprite::create("background.png");
        CC_BREAK_IF(! pSpriteBg);

		pSpriteBg->setScaleX(size.width / pSpriteBg->getContentSize().width);
		pSpriteBg->setScaleY(size.height / pSpriteBg->getContentSize().height);

        // Place the sprite on the center of the screen
        pSpriteBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainMenu layer as a child layer.
        this->addChild(pSpriteBg, 0);

		// Add wire
		CCSprite* pSpriteWire = CCSprite::create("wire.png");
        CC_BREAK_IF(! pSpriteWire);

        // Place the sprite on the center of the screen
        pSpriteWire->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainMenu layer as a child layer.
        this->addChild(pSpriteWire, 1);

		/*CCSprite *pSpriteTower = CCSprite::create("machineGun.png");
		CC_BREAK_IF(! pSpriteWire);
		pSpriteTower->setPosition(ccp(18,582));
		this->addChild(pSpriteTower);
		for (int i = 0; i<=180; ++i){
			pSpriteTower->setRotation(i);
		}
		*/

		PassingMap::ClearMap();
		PassingMap::SetCellState(5,5,STATE_CELL_BUSY);
		PassingMap::SetCellState(5,6,STATE_CELL_BUSY);
		PassingMap::SetCellState(10,10,STATE_CELL_BUILD);
		PassingMap::SetCellState(11,11,STATE_CELL_BUILD);
		//PassingMap::ShowDebugGrid((CCScene*)this);

		way.AddPoint(PassingMap::GetCell(1,1));
		way.AddPoint(PassingMap::GetCell(2,2));
		way.AddPoint(PassingMap::GetCell(4,4));
		way.AddPoint(PassingMap::GetCell(7,5));
		way.AddPoint(PassingMap::GetCell(12,9));
		PassingMap::ShowWaypoint(&way,(CCScene*)this);

		wave = NULL;		
		wavesCount = 5;
		waveTimout = 5;
		gameLogicTimeout = 0.1f;
		enemyRespawnTime = 2;

		// sound
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("\\Audio\\toska.mp3", true);  

		this->addTower(MACHINE_GUN, ccp(230, 200));

		int posFromBorder = 20;
		panelGeneral =  new PanelGeneral((CCScene*)this, ccp(size.width/2, size.height - posFromBorder),CCSize(size.width/2, 2 * posFromBorder));
		posFromBorder = 45;
		panelTower = new PanelTowers((CCScene*)this, ccp(size.width - posFromBorder, size.height/2), CCSize(2 * posFromBorder, size.height * 2 / 3));

		this->schedule( schedule_selector(MainFieldScene::GameLogic), gameLogicTimeout );

        bRet = true;
    } while (0);

    return bRet;
}

void MainFieldScene::CreateScene(CCObject* sender)
{
    CCScene* anScene = MainFieldScene::scene();
 
    CCDirector::sharedDirector()->replaceScene(anScene);
}

void MainFieldScene::GameLogic(float dt)
{
	static float passedTimeTotal = 0;	
	passedTimeTotal += dt;

	char curTime[10];
	sprintf(curTime, "%d:%d:%d", (int)(passedTimeTotal / 60 / 60) % 24, (int)(passedTimeTotal / 60) % 60, (int)passedTimeTotal % 60);
	panelGeneral->DisplayText(2, curTime, "Arial", 20, 2, 0, 0,0);

	static float passedTimeStartEnemy = 0;
	passedTimeStartEnemy += dt;

	static float passedTimeTillNewWave = 0;
	passedTimeTillNewWave += dt;

	if (passedTimeTillNewWave >= waveTimout){
	CCLog("New wave started");	//spams in logs

		DisplayText(1,NULL,"Arial",50,0,0);

		if (this->wave == NULL){
			this->wave = new Wave((CCScene *)this, &way);
		
			char waveNum[10];
			sprintf(waveNum, "Wave %d", this->wave->GetCurrentWaveNumber());
			panelGeneral->DisplayText(3, waveNum, "Arial", 18, 1, 0, 0,0);
		}		

		if (passedTimeStartEnemy >= enemyRespawnTime){
			this->wave->StartEnemy();
			passedTimeStartEnemy = 0;
		}
	}
	else {
		CCLog("New wave in %f", waveTimout - passedTimeTillNewWave);	
		char text[100];
		sprintf(text,"New wave in\n  %d sec\n\n", (int)(waveTimout - passedTimeTillNewWave));
		DisplayText(1,text,"Arial",50,0,0);
	}

	if (this->wave != NULL){

		//printf("Function called\n");
		towerArrayIterator it;
		for (it = this->towers.begin(); it != this->towers.end(); it++){
			(*it)->processEnemies(this->wave);
		}

		if (this->wave->GetEnemyCount() <= 0)
		{
			if (this->wave->GetCurrentWaveNumber() <= this->wavesCount)
			{	
				//start new wave after some timout
				CCLog("STart new wave in %d secs", this->waveTimout);
				passedTimeTillNewWave = 0;

				delete this->wave;
				this->wave = NULL;
				return;
			}
			else
			{
				CCLog("All waves are passed. You won!");
				//this->scheduleOnce( schedule_selector(MainMenu::CreateScene), 2 );
				this->unschedule( schedule_selector(MainFieldScene::GameLogic));

				panelGeneral->DisplayText(4, "You won!", "Arial", 18, 1, 0, 0,0);

				delete this->wave;
				this->wave = NULL;
				return;
			}
		}	
	}
}

Tower *MainFieldScene::addTower(int towerType, cocos2d::CCPoint position){
	Tower *newTower = towers.createTower(towerType, position);
	this->addChild(newTower->getSprite());
	return newTower;
}

void MainFieldScene::DisplayText(const int tag, const char *text, const char *font, const int size, const int locX, const int locY)
{
	this->removeChildByTag(tag); //Spams child not found in logs

	if (text == NULL)
		return;

	CCSize sizeWin = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* pLabel = CCLabelTTF::create(text, font, size);
	pLabel->setPositionX(sizeWin.width / 2 + locX);
	pLabel->setPositionY(sizeWin.height / 2 + locY);
	
	this->addChild(pLabel, 2, tag);
}