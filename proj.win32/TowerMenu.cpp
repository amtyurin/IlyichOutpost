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

