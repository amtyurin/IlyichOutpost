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
        CCSprite* pSpriteBg = CCSprite::create(FILE_NAME_IMAGE_BACKGROUND);
        CC_BREAK_IF(! pSpriteBg);

		pSpriteBg->setScaleX(size.width / pSpriteBg->getContentSize().width);
		pSpriteBg->setScaleY(size.height / pSpriteBg->getContentSize().height);

        // Place the sprite on the center of the screen
        pSpriteBg->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainMenu layer as a child layer.
        this->addChild(pSpriteBg, 0);		

		this->setTouchEnabled(true);

		PassingMap::ClearMap();
		PassingMap::SetCellState(5,5,STATE_CELL_BUSY);
		PassingMap::SetCellState(5,6,STATE_CELL_BUSY);
		PassingMap::SetCellState(3,8,STATE_CELL_BUILD);
		PassingMap::SetCellState(10,10,STATE_CELL_BUILD);
		PassingMap::SetCellState(11,11,STATE_CELL_BUILD);
		//PassingMap::ShowDebugGrid((CCScene*)this);

		way.AddPoint(PassingMap::GetCell(1,1));
		way.AddPoint(PassingMap::GetCell(2,2));
		way.AddPoint(PassingMap::GetCell(4,4));
		way.AddPoint(PassingMap::GetCell(7,5));
		way.AddPoint(PassingMap::GetCell(12,9));
		PassingMap::ShowWaypoint(&way,(CCScene*)this);

		touchedTowerSprite = NULL;
		touchedPanelSprite = NULL;
		wave = NULL;		
		wavesCount = 5;
		waveTimout = 5;
		gameLogicTimeout = 0.1f;
		enemyRespawnTime = 2;

		moneyManager = new MoneyManager();
		moneyManager->AddMoney(100);

		towers = new TowerArray(moneyManager);
		Outpost *outpost = new Outpost((CCScene*)this, OUTPOST_TYPE_OUR, CCRect(350, 250, 80, 80));
		outposts.AddOutpost(outpost);

		// sound
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILE_NAME_AUDIO_MAIN_SCENE_BG, true);  

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

	{// display time
		char curTime[TEXT_SIZE];
		sprintf(curTime, "%d:%d:%d", (int)(passedTimeTotal / 60 / 60) % 24, (int)(passedTimeTotal / 60) % 60, (int)passedTimeTotal % 60);
		panelGeneral->DisplayText(2, curTime, "Arial", 20, 2, 0, 0,0);
	}

	static float passedTimeStartEnemy = 0;
	passedTimeStartEnemy += dt;

	static float passedTimeTillNewWave = 0;
	passedTimeTillNewWave += dt;

	if (passedTimeTillNewWave >= waveTimout){		

		DisplayText(1,NULL,"Arial",50,0,0);

		if (this->wave == NULL){
			this->wave = new Wave((CCScene *)this, &way, moneyManager);

			CCLog("New wave started");
		
			{ // display wave number
				char waveNum[TEXT_SIZE];
				sprintf(waveNum, "Wave %d", this->wave->GetCurrentWaveNumber());
				panelGeneral->DisplayText(3, waveNum, "Arial", 18, 1, 0, 0,0);
			}
		}		

		if (passedTimeStartEnemy >= enemyRespawnTime){
			this->wave->StartEnemy();
			passedTimeStartEnemy = 0;
		}
	}
	else {
		CCLog("New wave in %f", waveTimout - passedTimeTillNewWave);
		{ // display wave number
			char text[TEXT_SIZE];
			sprintf(text,"New wave in\n  %d sec\n\n", (int)(waveTimout - passedTimeTillNewWave));
			DisplayText(1,text,"Arial",50,0,0);
		}
	}

	{ // display money
		char text[TEXT_SIZE];
		sprintf(text,"%d", moneyManager->GetMoneyBalance());
		panelGeneral->DisplayText(1, text,"Arial",20,0,0,5,0);
	}

	if (this->wave != NULL){	
		for (towerArrayIterator it = this->towers->begin(); it != this->towers->end(); it++){
			(*it)->processEnemies(this->wave);
		}

		if (this->wave->GetEnemyCount() <= 0 && this->wave->AllEnemiesCreated()){
			if (this->wave->GetCurrentWaveNumber() < this->wavesCount)	{	
				//start new wave after some timout
				CCLog("STart new wave in %d secs", this->waveTimout);
				passedTimeTillNewWave = 0;

				delete this->wave;
				this->wave = NULL;
				return;
			}
			else{				
				StopGame("You won!");
				
				// Next Scene();
				//this->scheduleOnce( schedule_selector(MainMenu::CreateScene), 2 );

				delete this->wave;
				this->wave = NULL;
				return;
			}
		}	
		else{
			// check if enemy reached base and make some damage to base
			// base can be our and/or enemy
			// bool
			this->outposts.ProcessEnemies(this->wave);
			
			if (this->outposts.OutpostEnemyDestroyed() && this->outposts.OutpostOurDestroyed()){
				StopGame("Draw!");
				return;
			} else if (this->outposts.OutpostEnemyDestroyed()){
				StopGame("You won!");
				return;
			} else if (this->outposts.OutpostOurDestroyed()){
				StopGame("You lost!");
				return;
			}
		}
	}
}

Tower *MainFieldScene::addTower(int towerType, cocos2d::CCPoint position){
	Tower *newTower = towers->createTower(towerType, position);
	this->addChild(newTower->getSprite(), 10);
	this->addTouchableSprite(newTower->getSprite(), TAG_TOWER_SCENE_MASK | newTower->GetIndex());
	return newTower;
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
	CCLog(text);

	this->unschedule( schedule_selector(MainFieldScene::GameLogic));

	DisplayText(4, text, "Arial", 70, 0, 0);

	delete this->wave;
	this->wave = NULL;
}

void MainFieldScene::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
	CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocation();

	if (touchedPanelSprite){
		panelTower->UnSelectCell((CCScene*)this);
		touchedPanelSprite = NULL;
	}

	CCSprite *sprite = NULL;
	for (int i = 0; i < this->touchableSprites.size(); i++){
		CCPoint point = touchableSprites[i]->convertToNodeSpace(location);
		CCRect rect = touchableSprites[i]->boundingBox();
		if (touchableSprites[i]->boundingBox().containsPoint(touchableSprites[i]->convertToNodeSpace(location))){
			sprite = touchableSprites[i];
			break;
		}
	}
	if (sprite != NULL){		
		int tagNew = sprite->getTag();	

		if (tagNew & TAG_TOWER_MENU_MASK){
			CCLog("begin Touch Sprite in menu tower: %d", tagNew);
			panelTower->SelectCell((CCScene*)this,sprite);
			touchedPanelSprite = sprite;			
		}
	}
}

void MainFieldScene::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
}

void MainFieldScene::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	// Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)( touches->anyObject() );
	CCPoint location = touch->getLocation();
    //location = CCDirector::sharedDirector()->convertToGL(location);
	
	//this->addTower(MACHINE_GUN, ccp(location.x, location.y));
	
	CCSprite *sprite = NULL;
	for (int i = 0; i < this->touchableSprites.size(); i++){
		if (touchableSprites[i]->boundingBox().containsPoint(location)){
			sprite = touchableSprites[i];
			break;
		}
	}
	if (sprite == NULL){
		if (this->touchedTowerSprite && this->touchedTowerSprite->getTag() & TAG_TOWER_SCENE_MASK){
			Tower *tower = towers->GetTower(this->touchedTowerSprite->getTag() ^ TAG_TOWER_SCENE_MASK);
			if(tower){
				tower->HideRange();
			}
			this->touchedTowerSprite = NULL;
		}
	}
	else if (sprite != this->touchedTowerSprite){		
		int tagNew = sprite->getTag();		

		if (tagNew & TAG_TOWER_SCENE_MASK){
			CCLog("Touched Sprite is tower: %d", tagNew);
			int indexNew = tagNew ^ TAG_TOWER_SCENE_MASK;
			Tower *tower = towers->GetTower(tagNew ^ TAG_TOWER_SCENE_MASK);
			if(tower){
				tower->ShowRange();
			}
			if (this->touchedTowerSprite){
				Tower *tower = towers->GetTower(this->touchedTowerSprite->getTag() ^ TAG_TOWER_SCENE_MASK);
				if(tower){
					tower->HideRange();
				}
			}
			this->touchedTowerSprite = sprite;
		}
	}

	if (touchedPanelSprite){
		panelTower->UnSelectCell((CCScene*)this);
		touchedPanelSprite = NULL;
	}
}

void MainFieldScene::ccTouchesCancelled(CCSet* touches, CCEvent* event)
{
}

void MainFieldScene::addTouchableSprite(CCSprite * child, int tag)
{
	child->setTag(tag);
	touchableSprites.push_back(child);	
}

void MainFieldScene::removeTouchableSprite(CCSprite * child)
{
	touchableSprites.erase(std::remove(touchableSprites.begin(), touchableSprites.end(), child), touchableSprites.end());
}