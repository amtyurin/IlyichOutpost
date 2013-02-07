#include "UILayer.h"

#include "PassingMap.h"

using namespace cocos2d;

UILayer::UILayer(void){
	//private hidden
}

UILayer::UILayer(CCScene *_scene, TowerArray *towers):scene(_scene){
	CCLayer::init();

	this->size = CCDirector::sharedDirector()->getWinSize();
	this->panelGeneral =  new PanelGeneral(this, ccp(size.width/2, size.height - GENERAL_PANEL_POSITION),CCSize(size.width/2, 2 * GENERAL_PANEL_POSITION));
	this->panelTowers = new PanelTowers(this, ccp(size.width - TOWER_PANEL_POSITION, size.height/2), CCSize(2 * TOWER_PANEL_POSITION, size.height * 2 / 3));
	
	this->touchedTowerSprite = NULL;
	this->touchedPanelSprite = NULL;
	this->movingTowerSprite = NULL;

	this->setTouchEnabled(true);

	this->towers = towers;

	addTowerToPanel(MACHINE_GUN, 0, 0);
	addTowerToPanel(HEAVY_GUN, 0, 1);
}

UILayer::~UILayer(void){
}

void UILayer::displayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY){
	this->panelGeneral->DisplayText(tag, text, font, size, cellX, cellY, locX, locY);
}

void UILayer::SelectCell(CCScene *scene, TouchableTowerSprite *tSprite){
	this->panelTowers->SelectCell(scene, tSprite);
}

void UILayer::UnSelectCell(CCScene *scene){
	this->panelTowers->UnSelectCell(scene);
}

void UILayer::addTouchableSprite(TouchableTowerSprite *sprite){
	CCLog("%f %f", sprite->sprite->getPositionX(), sprite->sprite->getPositionY());
	this->touchableSprites.push_back(sprite);
}

void UILayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){
	
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
	
	if (touchedPanelSprite){
		UnSelectCell((CCScene*)this);
		touchedPanelSprite = NULL;
	}
	CCLog("%d", touchableSprites.size());
	TouchableTowerSprite *sprite = NULL;
	for (unsigned int i = 0; i < this->touchableSprites.size(); i++){
		CCPoint point = touchableSprites[i]->sprite->convertToNodeSpace(location);
		CCRect rect = touchableSprites[i]->sprite->boundingBox();
		//rect.containsPoint(location);
		//if (touchableSprites[i]->sprite->boundingBox().containsPoint(touchableSprites[i]->sprite->convertToNodeSpace(location))){
		if (rect.containsPoint(location)){
			sprite = touchableSprites[i];
			break;
		}
	}
	if (sprite != NULL){		

		if (sprite->towerPlace == TOWER_MENU){
			CCLog("begin Touch Sprite in menu tower");
			SelectCell((CCScene*)this,sprite);
			touchedPanelSprite = sprite;		
			//touchedPanelSprite->setUserData();

			movingTowerSprite = CCSprite::createWithTexture(touchedPanelSprite->sprite->getTexture());
			this->addChild(movingTowerSprite);
		}
	}
}

void UILayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
	if (movingTowerSprite != NULL){
		movingTowerSprite->setPosition(location);
	}
}

void UILayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	// Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
    //location = CCDirector::sharedDirector()->convertToGL(location);
		
	TouchableTowerSprite *sprite = NULL;
	for (unsigned int i = 0; i < this->touchableSprites.size(); i++){
		if (touchableSprites[i]->sprite->boundingBox().containsPoint(location)){
			sprite = touchableSprites[i];
			break;
		}
	}
	if (sprite == NULL){
		if (this->touchedTowerSprite && this->touchedTowerSprite->towerPlace == TOWER_SCENE){
			Tower *tower = towers->GetTower(this->touchedTowerSprite->index);
			if(tower){
				tower->HideRange();
			}
			this->touchedTowerSprite = NULL;
		}
	}
	else if (sprite != this->touchedTowerSprite){	

		if (sprite->towerPlace == TOWER_SCENE){
			CCLog("Touched Sprite is tower");
			Tower *tower = towers->GetTower(sprite->index);
			if(tower){
				tower->ShowRange();
			}
			if (this->touchedTowerSprite){
				Tower *tower = towers->GetTower(sprite->index);
				if(tower){
					tower->HideRange();
				}
			}
			this->touchedTowerSprite = sprite;
		}
	}

	if (touchedPanelSprite){
		Cell *touchedCell = NULL;
		for (int x = 0; x < PassingMap::MAP_WIDTH_MAX; x++){
			for(int y = 0; y < PassingMap::MAP_HEIGHT_MAX; y++){
				if (PassingMap::GetCell(x, y)->sprite &&
					PassingMap::GetCell(x, y)->sprite->boundingBox().containsPoint(location)){
					touchedCell = PassingMap::GetCell(x, y);
					break;
				}
			}
		}

		if (touchedCell){
			this->addTower(touchedPanelSprite->towerType, ccp(touchedCell->x, touchedCell->y));
		}

		UnSelectCell((CCScene*)this);
		touchedPanelSprite = NULL;
	}

	if (movingTowerSprite != NULL){
		movingTowerSprite->removeFromParent();
		movingTowerSprite = NULL;
	}
}

void UILayer::addTower(TowerTypes towerType, cocos2d::CCPoint position){
	if (towers->Buy(towerType)){
		Tower *newTower = towers->createTower(towerType, position);
		this->addChild(newTower->getSprite(), 100);

		TouchableTowerSprite *tSprite = new TouchableTowerSprite();
		tSprite->towerType = towerType;
		tSprite->index = newTower->GetIndex();
		tSprite->towerPlace = TOWER_SCENE;
		tSprite->sprite = newTower->getSprite();
		tSprite->cellX = 0;
		tSprite->cellY = 0;
		//tSprite->sprite->setPosition(ccp(760, 300));
		addTouchableSprite(tSprite);
	}
}

void UILayer::addTowerToPanel(TowerTypes towerType, const int cellX, const int cellY){	

	CCSprite *sprite = panelTowers->AddTower(towerType, cellX, cellY);

	TouchableTowerSprite *tSprite = new TouchableTowerSprite();
	tSprite->towerType = towerType;
	tSprite->index = 0;
	tSprite->towerPlace = TOWER_MENU;
	tSprite->sprite = sprite;
	tSprite->cellX = cellX;
	tSprite->cellY = cellY;
	tSprite->sprite->setPositionX(800 - (cellX+1)*42);
	tSprite->sprite->setPositionY(cellY*80 + 150);
	tSprite->sprite->setScale(1.3);
	this->addChild(tSprite->sprite);
	//tSprite->sprite->setVertexZ(25);
	//this->addChild(tSprite->sprite, 100);
	addTouchableSprite(tSprite);	
}
