#include "TowerMenu.h"

using namespace cocos2d;

TowerMenu::TowerMenu(CCNode *scene)
{
	this->scene = scene;
	this->tower = NULL;
	this->position.x = 100;
	this->position.y = 100;
	this->upgradeButton = new TouchableSprite();
	this->sellButton = new TouchableSprite();
	this->upgradeButton->sprite = CCSprite::create(FILE_NAME_UPGRADE_TOWER_BUTTON);
	this->sellButton->sprite = CCSprite::create(FILE_NAME_SELL_TOWER_BUTTON);
	this->upgradeButton->sprite->setPosition(ccp(-100,-100));
	this->sellButton->sprite->setPosition(ccp(-100, -100));
	this->upgradeButton->sprite->setScale(0.8f);
	this->sellButton->sprite->setScale(0.8f);
	scene->addChild(this->upgradeButton->sprite);
	scene->addChild(this->sellButton->sprite);
	this->upgradeButton->spriteType = MENU_BUTTON;
	this->sellButton->spriteType = MENU_BUTTON;
}

TowerMenu::~TowerMenu(void)
{
}

CCSprite * TowerMenu::AddMenuItem(TowerMenuItem item, TouchableSprite *tower, cocos2d::CCPoint position)
{
	char text[15] = {0};
	switch(item){
		case UPGRADE:
			snprintf(text, 15, "Upgrade:%d",tower->tower->GetUpgradePrice());
			position.setPoint(position.x, position.y + 25);
			break;
		case DESTROY:
			snprintf(text, 15, "Destroy:+%d",Tower::GetPrice(tower->towerType) / 2);
			position.setPoint(position.x, position.y - 25);
			break;
	};	

	CCLabelTTF* pLabel = CCLabelTTF::create(text, "Arial", 18);
	pLabel->setPosition(position);
	pLabel->setColor(ccc3(255,255,255));
			
	//CCSprite *sprite = CCSprite::create();
	//sprite->addChild(pLabel, 200);
	scene->addChild(pLabel);

	return pLabel;
}


void TowerMenu::Hide()
{
	//this->panelSprite->setPositionY(-100);

}

void TowerMenu::attachToTower(Tower *tower){
	this->detachFromTower();
	this->tower = tower;
	this->position.x = tower->getX();
	this->position.y = tower->getY();
	this->chooseButtonsPositions();
}

void TowerMenu::detachFromTower(){
	this->tower = NULL;
	this->position.x = -100;
	this->position.y = -100;
	this->chooseButtonsPositions();
}

void TowerMenu::chooseButtonsPositions(){
	this->upgradeButton->sprite->setPositionX(this->position.x);
	this->upgradeButton->sprite->setPositionY(this->position.y + 25);
	this->sellButton->sprite->setPositionX(this->position.x);
	this->sellButton->sprite->setPositionY(this->position.y - 25);
}

void TowerMenu::buttonPressed(TouchableSprite *sprite){
	if (sprite == upgradeButton){
		this->tower->Upgrade();
		CCLog("Upgrade button pressed");
	}
	else if (sprite == sellButton){
		//this->tower->Sell();
	}
}