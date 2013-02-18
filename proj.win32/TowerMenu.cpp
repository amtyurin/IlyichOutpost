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
	scene->addChild(this->upgradeButton->sprite, 200);
	scene->addChild(this->sellButton->sprite, 200);
	this->upgradeButton->spriteType = MENU_BUTTON;
	this->sellButton->spriteType = MENU_BUTTON;

	this->upgradeButton->tower = NULL;
	this->sellButton->tower = NULL;
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

	this->sellButton->tower = tower;
	this->upgradeButton->tower = tower;
	this->sellButton->towerType = tower->GetType();
	this->upgradeButton->towerType = tower->GetType();

	this->upgradeButton->sprite->removeAllChildren();
	char text[10];
	snprintf(text, 10, "%d",tower->GetUpgradePrice());
	CCLabelTTF* pLabel = CCLabelTTF::create(text, "Arial", 17);
	pLabel->setColor(ccc3(155,155,151));
	pLabel->setPositionX(this->upgradeButton->sprite->getContentSize().width / 2 + 25);
	pLabel->setPositionY(this->upgradeButton->sprite->getContentSize().height / 2);
	this->upgradeButton->sprite->addChild(pLabel);

	this->sellButton->sprite->removeAllChildren();
	snprintf(text, 10, "%d",tower->GetSellPrice());
	pLabel = CCLabelTTF::create(text, "Arial", 17);
	pLabel->setColor(ccc3(155,155,151));
	pLabel->setPositionX(this->sellButton->sprite->getContentSize().width / 2 + 25);
	pLabel->setPositionY(this->sellButton->sprite->getContentSize().height / 2);
	this->sellButton->sprite->addChild(pLabel);
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

