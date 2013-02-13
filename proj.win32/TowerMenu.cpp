#include "TowerMenu.h"

using namespace cocos2d;

TowerMenu::TowerMenu(const int cellsX, const int cellsY, cocos2d::CCNode * node, const cocos2d::CCSize size)
	: PanelBase(cellsX,cellsY, ccp(0,0), size)
{
	node->addChild(this->panelSprite);
	
	this->SetCellBorderImage(NULL);

	CCSprite *sprite = CCSprite::create(FILE_NAME_IMAGE_PANEL_BORDER);
	sprite->setOpacity(100);
	this->SetCellContentSprite(sprite,0,0,0,0);
	sprite = CCSprite::create(FILE_NAME_IMAGE_PANEL_BORDER);
	sprite->setOpacity(100);
	this->SetCellContentSprite(sprite,0,2,0,0);
}


TowerMenu::~TowerMenu(void)
{
}

CCSprite * TowerMenu::AddMenuItem(TowerMenuItem item, TouchableTowerSprite *tower, const int cellX, const int cellY)
{
	this->panelSprite->setPositionX(tower->sprite->getPositionX());
	this->panelSprite->setPositionY(tower->sprite->getPositionY());

	char text[15]="\0";
	switch(item){
		case UPGRADE:
			snprintf(text, 15, "Upgrade:%d",tower->tower->GetUpgradePrice());
			break;
		case DESTROY:
			snprintf(text, 15, "Destroy:+%d",Tower::GetPrice(tower->towerType) / 2);
			break;
	};
	this->DisplayText(cellX * 100 + cellY, text, "Arial", ccc3(255,255,255), 18, cellX,cellY, 0,0);

	return this->GetSprite(cellX, cellY);
}


void TowerMenu::Hide()
{
	this->panelSprite->setPositionY(-100);
}

