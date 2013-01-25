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

		wavesCount = 5;
		waveTimout = 5;
		wave = NULL;
		this->scheduleOnce( schedule_selector(MainFieldScene::StartWave), waveTimout );

		this->schedule( schedule_selector(MainFieldScene::GameLogic), 0.3f );

		// sound
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("\\Audio\\toska.mp3", true);  

		this->addTower(MACHINE_GUN, ccp(130, 100));

		int posFromBorder = 20;
		panelGeneral =  new PanelGeneral((CCScene*)this, ccp(size.width/2, size.height - posFromBorder),CCSize(size.width/2, 2 * posFromBorder));
		posFromBorder = 50;
		panelTower = new PanelTowers((CCScene*)this, ccp(size.width - posFromBorder, size.height/2), CCSize(2 * posFromBorder, size.height * 2 / 3));


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

	//printf("Function called\n");
	towerArrayIterator it;
	for (it = this->towers.begin(); it != this->towers.end(); ++it){
		for (int i = 0; i < this->wave->GetEnemyCount(); ++i){
			if (it->isTargetInRange(this->wave->GetEnemyPosition(i))){
				it->turnTo(this->wave->GetEnemyPosition(i));
			}
		}
	}

	if (wave->GetEnemyCount() <= 0)
	{
		if (wave->GetCurrentWaveNumber() <= wavesCount)
		{	
			//start new wave after some timout
			CCLog("STart new wave in %d secs", waveTimout);
			this->scheduleOnce( schedule_selector(MainFieldScene::StartWave), waveTimout );
		}
		else
		{
			CCLog("All waves are passed. You won!");
		}
	}
}

void MainFieldScene::StartWave(float dt)
{
	if (wave != NULL){
		delete wave;
	}

	wave = new Wave((CCScene *)this, &way);	

	this->schedule( schedule_selector(MainFieldScene::WaveGenerateEnemyProcess), 2.0 );
}

void MainFieldScene::WaveGenerateEnemyProcess(float dt)
{
    // called every X msec
	bool added = wave->AddEnemy();
	if (!added)
	{		
		this->unschedule( schedule_selector(MainFieldScene::WaveGenerateEnemyProcess) );		
	}
}

Tower MainFieldScene::addTower(int towerType, cocos2d::CCPoint position){
	Tower newTower(towerType, position);
	this->addChild(newTower.getSprite());
	this->towers.addTower(newTower);
	return newTower;
}
