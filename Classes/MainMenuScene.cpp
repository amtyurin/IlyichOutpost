#include "MainMenuScene.h"

#include "MainFieldScene.h"

using namespace cocos2d;

CCScene* MainMenu::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        MainMenu *layer = MainMenu::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
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
            menu_selector(MainMenu::menuCloseCallback));
        CC_BREAK_IF(! pCloseItem);

        // Place the menu item bottom-right conner.
        pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));



        // 2. Add a label shows "Hello World".

        // Create a label and initialize with string "Hello World".
        CCLabelTTF* pLabel = CCLabelTTF::create("Welcome to Ilyich Outpost", "Arial", 24);
        CC_BREAK_IF(! pLabel);

        // Get window size and place the label upper. 
        CCSize size = CCDirector::sharedDirector()->getWinSize();
        pLabel->setPosition(ccp(size.width / 2, size.height - 50));

        // Add the label to MainMenu layer as a child layer.
        this->addChild(pLabel, 1);

        // 3. Add add a splash screen, show the cocos2d splash image.
        CCSprite* pSpriteMainMenu = CCSprite::create("MainMenu.png");
        CC_BREAK_IF(! pSpriteMainMenu);

		pSpriteMainMenu->setScaleX(size.width / pSpriteMainMenu->getContentSize().width);
		pSpriteMainMenu->setScaleY(size.height / pSpriteMainMenu->getContentSize().height);

        // Place the sprite on the center of the screen
        pSpriteMainMenu->setPosition(ccp(size.width/2, size.height/2));

        // Add the sprite to MainMenu layer as a child layer.
        this->addChild(pSpriteMainMenu, 0);
				
		// menu items
		CCMenuItemImage* startItem;
 
		startItem = CCMenuItemImage::create("\\MenuItems\\Start.png", "\\MenuItems\\StartPressed.png",
										    "\\MenuItems\\StartPressed.png", this, menu_selector(MainFieldScene::CreateScene)); 

		CCMenu* menu = CCMenu::create(startItem, NULL);
		menu->alignItemsVertically();
		this->addChild(menu);

		CCMenuItemImage *muteButton;
		muteButton = CCMenuItemImage::create("\\MenuItems\\Sound.png", 
			"\\MenuItems\\Sound.png", 
			"\\MenuItems\\Sound.png", 
			this, 
			menu_selector(MainMenu::muteSound));
		muteButton->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 60, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
        CCMenu* pMenu = CCMenu::create(pCloseItem, muteButton, NULL);
        pMenu->setPosition(CCPointZero);
        CC_BREAK_IF(! pMenu);

        // Add the menu to MainMenu layer as a child layer.
        this->addChild(pMenu, 1);

		
		// \menu items

		// sound
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(FILE_NAME_AUDIO_MAIN_MENU_BG, true);    
        bRet = true;
    } while (0);

    return bRet;
}

void MainMenu::CreateScene(CCObject* sender)
{
    CCScene* anScene = MainMenu::scene();
 
    CCDirector::sharedDirector()->replaceScene(anScene);
}

void MainMenu::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}


void MainMenu::muteSound(CCObject *sender){
	//CCLog("MutingSound");
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}