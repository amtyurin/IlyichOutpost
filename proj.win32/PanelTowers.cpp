#include "PanelTowers.h"

#include "MainFieldScene.h"
#include "PassingMap.h"

PanelTowers::PanelTowers(cocos2d::CCNode *node, const int cellsCount, const CCPoint ccp, const CCSize size)
	: PanelBase(1, cellsCount, ccp, size)
{	
	node->addChild(this->panelSprite);

	this->SetCellBorderImage(FILE_NAME_IMAGE_PANEL_BORDER);
}


PanelTowers::~PanelTowers(void)
{
}

CCSprite * PanelTowers::AddTower(TowerTypes type, const int cellX, const int cellY)
{
	CCSprite *tower =  CCSprite::create(Tower::GetImage(type));
	this->SetSpriteCoords(tower, cellX,cellY,0,0);

	CCSprite *coin =  CCSprite::create(FILE_NAME_IMAGE_PANEL_COIN);
	coin->setScale(0.15f);
	this->SetCellContentSprite(coin, cellX, cellY, 0, -15);

	char price[10];
	_itoa(Tower::GetPrice(type), price, 10);
	this->DisplayText(cellX * 10 + cellY, price, "Arial", ccc3(255,255,51), 20, cellX, cellY, 0, -17);

	return tower;
}