#include "UILayer.h"

using namespace cocos2d;

UILayer::UILayer(void){
	//private hidden
}

UILayer::UILayer(CCScene *_scene):scene(_scene){
	this->size = CCDirector::sharedDirector()->getWinSize();
	this->panelGeneral =  new PanelGeneral(_scene, ccp(size.width/2, size.height - GENERAL_PANEL_POSITION),CCSize(size.width/2, 2 * GENERAL_PANEL_POSITION));
	this->panelTowers = new PanelTowers(_scene, ccp(size.width - TOWER_PANEL_POSITION, size.height/2), CCSize(2 * TOWER_PANEL_POSITION, size.height * 2 / 3));

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

void UILayer::addSprite(TouchableTowerSprite *sprite){
	this->touchableSprites.push_back(sprite);
}

/*virtual*/ bool UILayer::ccTouchBegan(CCTouch *touch, CCEvent *pEvent){
	
	CCPoint location = touch->getLocation();
	return true;
	/*
	if (touchedPanelSprite){
		UI->UnSelectCell((CCScene*)this);
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
			UI->SelectCell((CCScene*)this,sprite);
			touchedPanelSprite = sprite;		
			//touchedPanelSprite->setUserData();

			movingTowerSprite = CCSprite::createWithTexture(touchedPanelSprite->getTexture());
			this->addChild(movingTowerSprite);
		}
	}*/
}

/*virtual*/ void UILayer::ccTouchMoved(CCTouch *touch, CCEvent *pEvent){
}

/*virtual*/ void UILayer::ccTouchEnded(CCTouch *touch, CCEvent *pEvent){

}