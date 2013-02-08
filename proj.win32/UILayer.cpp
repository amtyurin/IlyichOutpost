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
	this->panelTowers = new PanelTowers(this, ccp(size.width - TOWER_PANEL_POSITION, size.height/2), CCSize(2 * TOWER_PANEL_POSITION, size.height * 3 / 4));
	
	this->touchedTowerSprite = NULL;
	this->movingTowerSprite = NULL;

	this->setTouchEnabled(true);

	this->towers = towers;

	addTowerToPanel(MACHINE_GUN, 0, 0);
	addTowerToPanel(HEAVY_GUN, 0, 1);
	addTowerToPanel(SNIPER_GUN, 0, 2);
	addTowerToPanel(ANTITANK_GUN, 0, 3);
	addTowerToPanel(LASER_GUN, 0, 4);
	addTowerToPanel(ROCKET_GUN, 0, 5);
	addTowerToPanel(ELECTROMAGNETIC_GUN, 0, 6);
	addTowerToPanel(FLAME_GUN, 0, 7);
	addTowerToPanel(NAPALM_GUN, 0, 8);
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
	//CCLog("%f %f", sprite->sprite->getPositionX(), sprite->sprite->getPositionY());
	this->touchableSprites.push_back(sprite);
}

void UILayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){	
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
	
	if (this->touchedTowerSprite){		
		Tower *tower = towers->GetTower(touchedTowerSprite->index);
		if(tower){
			tower->HideRange();
		}		
		this->touchedTowerSprite = NULL;
	}

	TouchableTowerSprite *sprite = NULL;
	for (unsigned int i = 0; i < this->touchableSprites.size(); i++){
		CCRect rect = touchableSprites[i]->sprite->boundingBox();
		if (rect.containsPoint(location)){			
			sprite = touchableSprites[i];
			break;
		}
	}
	
	this->movingTowerSprite = NULL;
	if (sprite != NULL){	
		if (sprite->towerPlace == TOWER_MENU){
			CCLog("begin Touch Sprite in menu tower");
			this->movingTowerSprite = sprite;
			this->movingTowerSprite->SaveInitialPosition();
			PassingMap::ShowDebugGrid(this->scene, STATE_CELL_BUILD);
		}
		else if (sprite->towerPlace == TOWER_SCENE){
			this->touchedTowerSprite = sprite;
			Tower *tower = towers->GetTower(sprite->index);
			if(tower){
				tower->ShowRange();
			}
		}
	}
}

void UILayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
	if (movingTowerSprite != NULL){
		movingTowerSprite->sprite->setPosition(location);
	}
}

void UILayer::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent){
	// Choose one of the touches to work with
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();
	
    PassingMap::HideDebugGrid(this->scene);

	if (this->movingTowerSprite != NULL){
		this->movingTowerSprite->ReturnToOriginalPosition();
		const float x = touch->getLocation().x;
		const float y = touch->getLocation().y;
		Cell *touchedCell = PassingMap::GetCellByScreenCoords(x, y);
		CCLog("%f %f %d %d", x, y, touchedCell->x, touchedCell->y);
		if (touchedCell !=NULL && touchedCell->type == STATE_CELL_BUILD){
			this->addTouchableTower(movingTowerSprite->towerType, ccp(touchedCell->x, touchedCell->y));
		}

	}
}

void UILayer::addTouchableTower(TowerTypes towerType, cocos2d::CCPoint position){
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
	tSprite->sprite->setScale(1.1f);

	this->addChild(tSprite->sprite, 100);

	addTouchableSprite(tSprite);	
}
