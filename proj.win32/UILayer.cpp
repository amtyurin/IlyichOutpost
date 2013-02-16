#include "UILayer.h"

#include "PassingMap.h"

using namespace cocos2d;

UILayer::UILayer(CCScene *_scene, TowerArray *towers):scene(_scene){
	CCLayer::init();

	this->size = CCDirector::sharedDirector()->getWinSize();
	this->panelGeneral =  new PanelGeneral(this, ccp(size.width/2, size.height - GENERAL_PANEL_POSITION),CCSize(size.width/2, 2 * GENERAL_PANEL_POSITION));
	int cellsCount = 9;
	this->panelTowers = new PanelTowers(this, cellsCount, ccp(size.width - TOWER_PANEL_POSITION, size.height/2), CCSize(2 * TOWER_PANEL_POSITION, size.height * 3 / 4));
	this->towerDescription = new PanelTowerDescription(this, CCSize(TOWER_PANEL_POSITION, size.height * 3 / 4 / cellsCount));
	this->towerMenu = new TowerMenu(this);
	this->touchableSprites.push_back(towerMenu->getUpgradeButton());
	this->touchableSprites.push_back(towerMenu->getSellButton());
	
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
	isMenuOnScreen = false;
}

UILayer::~UILayer(void){
}

void UILayer::displayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY){
	this->panelGeneral->DisplayText(tag, text, font, ccc3(0,0,0), size, cellX, cellY, locX, locY);
}

void UILayer::addTouchableSprite(TouchableSprite *sprite){
	//CCLog("%f %f", sprite->sprite->getPositionX(), sprite->sprite->getPositionY());
	if (std::find(this->touchableSprites.begin(), this->touchableSprites.end(), sprite) == this->touchableSprites.end()){
		this->touchableSprites.push_back(sprite);
	}
}

void UILayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent){	
    CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
	CCPoint location = touch->getLocation();

	//CCTime::gettimeofdayCocos2d(&touchStartTime, NULL);
	
	if (this->touchedTowerSprite){		
		if(this->touchedTowerSprite->tower){
			this->touchedTowerSprite->tower->HideRange();
			this->towerMenu->detachFromTower();
		}		
		this->touchedTowerSprite = NULL;
	}

	TouchableSprite *sprite = NULL;
	for (unsigned int i = 0; i < this->touchableSprites.size(); i++){
		CCRect rect = touchableSprites[i]->sprite->boundingBox();
		CCLog("%f %f %f %f %d", touchableSprites[i]->sprite->boundingBox().getMinX(), touchableSprites[i]->sprite->boundingBox().getMaxX(),
				touchableSprites[i]->sprite->boundingBox().getMinY(), touchableSprites[i]->sprite->boundingBox().getMaxY(), touchableSprites[i]->spriteType);
		if (rect.containsPoint(location)){			
			sprite = touchableSprites[i];
			//break;
		}
	}
	
	this->movingTowerSprite = NULL;
	if (sprite != NULL){	
		if (sprite->spriteType == TOWER_ON_PANEL){
			CCLog("begin Touch Sprite in menu tower");
			this->movingTowerSprite = sprite;
			this->movingTowerSprite->SaveInitialPosition();

			PassingMap::ShowDebugGrid(this->scene, STATE_CELL_BUILD);

			this->towerDescription->Show(sprite);
		} else if (sprite->spriteType == TOWER_ON_SCENE){
			this->touchedTowerSprite = sprite;
			if(this->touchedTowerSprite->tower){
				this->touchedTowerSprite->tower->ShowRange();
				this->towerMenu->attachToTower(this->touchedTowerSprite->tower);
			}
		} else if (sprite->spriteType == MENU_BUTTON){
			CCLog("Tower Menu Item Pressed");
			this->towerMenu->buttonPressed(sprite);
			sprite->tower->Upgrade();
			sprite->tower->ShowRange();	
			this->touchedTowerSprite = sprite;
		}
	}
}

void UILayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){
	if (movingTowerSprite != NULL){
		CCTouch* touch = (CCTouch*)( pTouches->anyObject() );
		CCPoint touchLocation = touch->getLocation();
		CCPoint position;
		Cell *cell = PassingMap::GetCellByScreenCoords(touchLocation.x, touchLocation.y);
		if (cell->type == STATE_CELL_BUILD){
			position.x = cell->x;
			position.y = cell->y;
		}else{
			position.x = touchLocation.x;
			position.y = touchLocation.y;
		}
		movingTowerSprite->sprite->setPosition(position);
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
		//CCLog("%f %f %d %d", x, y, touchedCell->x, touchedCell->y);
		if (touchedCell !=NULL && touchedCell->type == STATE_CELL_BUILD){
			this->addTouchableTower(movingTowerSprite->towerType, ccp(touchedCell->x, touchedCell->y));
		}
	}
	else{	
		this->towerDescription->Hide();
	}

	if (this->touchedTowerSprite){ //maybe we should delete it
		//do_nothing
	}
	else{
		//do_nothing either
	}

}

void UILayer::addTouchableTowerMenuItem(TowerMenuItem item, TouchableSprite *tower){	
	CCSprite *sprite = this->towerMenu->AddMenuItem(item, this->touchedTowerSprite, tower->sprite->getPosition());

	TouchableSprite *tSprite = new TouchableSprite();
	tSprite->towerType = tower->towerType;
	tSprite->tower = tower->tower;
	tSprite->spriteType = MENU_BUTTON;
	tSprite->sprite = sprite;
	tSprite->cellX = tower->cellX;
	tSprite->cellY = tower->cellY;


	addTouchableSprite(tSprite);
}

void UILayer::addTouchableTower(TowerTypes towerType, cocos2d::CCPoint position){
	if (towers->Buy(towerType)){
		Tower *newTower = towers->createTower(towerType, position);
		this->addChild(newTower->getSprite(), 100);

		TouchableSprite *tSprite = new TouchableSprite();
		tSprite->towerType = towerType;
		tSprite->tower = newTower;
		tSprite->spriteType = TOWER_ON_SCENE;
		tSprite->sprite = newTower->getSprite();
		tSprite->cellX = 0;
		tSprite->cellY = 0;

		addTouchableSprite(tSprite);
	}
}

void UILayer::addTowerToPanel(TowerTypes towerType, const int cellX, const int cellY){	

	CCSprite *sprite = panelTowers->AddTower(towerType, cellX, cellY);

	TouchableSprite *tSprite = new TouchableSprite();
	tSprite->towerType = towerType;
	tSprite->tower = NULL;
	tSprite->spriteType = TOWER_ON_PANEL;
	tSprite->sprite = sprite;
	tSprite->cellX = cellX;
	tSprite->cellY = cellY;
	tSprite->sprite->setScale(1.1f);

	this->addChild(tSprite->sprite, 100);

	addTouchableSprite(tSprite);	
}
