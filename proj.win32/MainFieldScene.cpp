#include "MainFieldScene.h"

#include "MainMenuScene.h"

#include "PassingMap.h"
#include "Wave.h"
#include "GameAI.h"

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
        CCSprite* pSpriteBg = CCSprite::create(FILE_NAME_IMAGE_BACKGROUND);
        CC_BREAK_IF(! pSpriteBg);

		pSpriteBg->setScaleX(size.width / pSpriteBg->getContentSize().width);
		pSpriteBg->setScaleY(size.height / pSpriteBg->getContentSize().height);

        // Place the sprite on the center of the screen
        pSpriteBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainMenu layer as a child layer.
        this->addChild(pSpriteBg, 0);		

		this->setTouchEnabled(true);

		this->UI = new UILayer((CCScene*)this, we->towers);
		this->addChild(UI, 100);
		
		PassingMap::ClearMap();
		PassingMap::InitCells();
		//PassingMap::ShowDebugGrid((CCScene*)this, STATE_CELL_FREE);

		we = new Player(PassingMap::GenerateWaypoint(), PassingMap::GenerateBuildCells());
		//PassingMap::ShowWaypoint(we->way,(CCScene*)this);
		PassingMap::ShowRoad(we->way,(CCScene*)this);

		if (GameSettings::vsAI){
			ai = new GameAI((CCLayer *)this->UI, PassingMap::GenerateSymmetricWaypoint(12, 0, 12, 25, we->way), PassingMap::GenerateSymmetricBuildCellsForAI(12, 0, 12, 25, we->buildCells));
			//PassingMap::ShowWaypoint(ai->way,(CCScene*)this);
			PassingMap::ShowRoad(ai->way,(CCScene*)this);
		}
		else
			ai = NULL;		
		
		wavesCount = 500;
		waveTimout = 5;
		enemyRespawnTime = 2;

		we->moneyManager.AddMoney(1000);		
		Outpost *outpost = new Outpost((CCScene*)this, true, CCRect(350, 250, 80, 80));		
		we->outposts.AddOutpost(outpost);
		if (ai){
			ai->moneyManager.AddMoney(1000);
			outpost = new Outpost((CCScene*)this, false, CCRect(300, 200, 30, 30));
			ai->outposts.AddOutpost(outpost);
		}

		// sound
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILE_NAME_AUDIO_MAIN_SCENE_BG, true);  

		this->schedule( schedule_selector(MainFieldScene::GameLogic), TIMEOUT_GAME_LOGIC);		

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

	{// display time
		char curTime[TEXT_SIZE];
		sprintf(curTime, "%d:%d:%d", (int)(passedTimeTotal / 60 / 60) % 24, (int)(passedTimeTotal / 60) % 60, (int)passedTimeTotal % 60);
		UI->displayText(2, curTime, "Arial", 20, 2, 0, 0,0);
	}

	static float passedTimeStartEnemy = 0;
	passedTimeStartEnemy += dt;

	static float passedTimeTillNewWave = 0;
	passedTimeTillNewWave += dt;

	if (passedTimeTillNewWave >= waveTimout){		

		DisplayText(1,NULL,"Arial",50,0,0);

		if (we->wave == NULL && (ai == NULL || (ai != NULL && ai->wave == NULL))){
			we->wave = new Wave((CCScene *)this, we->way, &we->moneyManager);
			if (ai) ai->wave = new Wave((CCScene *)this, ai->way, &ai->moneyManager);

			//CCLog("New wave started");
		
			{ // display wave number
				char waveNum[TEXT_SIZE];
				sprintf(waveNum, "Wave %d", we->wave->GetCurrentWaveNumber());
				UI->displayText(3, waveNum, "Arial", 18, 1, 0, 0,0);
			}
		}		

		if (passedTimeStartEnemy >= enemyRespawnTime){
			if (we->wave != NULL) we->wave->StartEnemy();
			if (ai && ai->wave != NULL) ai->wave->StartEnemy();
			passedTimeStartEnemy = 0;
		}
	}
	else {
		//CCLog("New wave in %f", waveTimout - passedTimeTillNewWave);
		{ // display wave number
			char text[TEXT_SIZE];
			sprintf(text,"New wave in\n  %d sec\n\n", (int)(waveTimout - passedTimeTillNewWave));
			DisplayText(1,text,"Arial",50,0,0);
		}
	}

	{ // display money
		char text[TEXT_SIZE];
		sprintf(text,"%d", we->moneyManager.GetMoneyBalance());
		UI->displayText(1, text,"Arial",20,0,0,5,0);
	}

	we->ProcessStepLogic();
	if (ai) ai->ProcessStepLogic();


	if (we->outposts.OutpostDestroyed() && ai && ai->outposts.OutpostDestroyed()){
		StopGame("Draw!");
		return;
	} else if (ai && ai->outposts.OutpostDestroyed()){
		StopGame("You won!");
		return;
	} else if (we->outposts.OutpostDestroyed()){
		StopGame("You lost!");
		return;
	}

	if (we->wave != NULL){
		if (we->wave->GetEnemyCount() <= 0 && we->wave->AllEnemiesCreated()){
			if (we->wave->GetCurrentWaveNumber() < this->wavesCount){	
				//start new wave after some timout
				//CCLog("STart new wave in %d secs", this->waveTimout);
				
				if (!ai){
					passedTimeTillNewWave = 0;
				}
				else if (ai->wave){
					if (ai->wave->GetEnemyCount() <= 0 && ai->wave->AllEnemiesCreated()){
						if (ai->wave->GetCurrentWaveNumber() < this->wavesCount){	
							passedTimeTillNewWave = 0;
							delete ai->wave;
							ai->wave = NULL;
						}
					}
				}

				delete we->wave;
				we->wave = NULL;
			}
			else{				
				StopGame("You won!");
				
				// Next Scene();
				//this->scheduleOnce( schedule_selector(MainMenu::CreateScene), 2 );
			}
		}	
	}
}

void MainFieldScene::DisplayText(const int tag, const char *text, const char *font, const int size, const int locX, const int locY)
{
	static bool textDisplayed = false;
	
	if (textDisplayed){
		this->removeChildByTag(tag); 
		textDisplayed = false;
	}

	if (text == NULL)
		return;

	CCSize sizeWin = CCDirector::sharedDirector()->getWinSize();

	CCLabelTTF* pLabel = CCLabelTTF::create(text, font, size);
	pLabel->setPositionX(sizeWin.width / 2 + locX);
	pLabel->setPositionY(sizeWin.height / 2 + locY);
	
	this->addChild(pLabel, 2, tag);

	textDisplayed = true;;
}

void MainFieldScene::StopGame(char *text)
{
	//CCLog(text);

	this->unschedule( schedule_selector(MainFieldScene::GameLogic));

	DisplayText(4, text, "Arial", 70, 0, 0);

	if (we->wave){
		delete we->wave;
		we->wave = NULL;
	}
	
	if (ai && ai->wave){
		delete ai->wave;
		ai->wave = NULL;
	}
}

