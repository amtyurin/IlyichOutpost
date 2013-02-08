#include "PanelTowers.h"

#include "MainFieldScene.h"
#include "PassingMap.h"

PanelTowers::PanelTowers(cocos2d::CCNode *node, const CCPoint ccp, const CCSize size)
	: PanelBase(1,9, ccp, size)
{	
	node->addChild(this->panelSprite);

	this->SetCellBorderImage("panel_border_common.png");
}


PanelTowers::~PanelTowers(void)
{
}

void PanelTowers::SelectCell(CCScene* scene, TouchableTowerSprite *tSprite)
{	
	selectionSprite = CCSprite::create(FILE_NAME_IMAGE_PANEL_TOWER_SELECTION);
	this->SetCellContentSprite(selectionSprite, tSprite->cellX, tSprite->cellY,0,0);
	selectionSprite->setOpacity(100);

	PassingMap::ShowDebugGrid(scene, STATE_CELL_BUILD);
}

void PanelTowers::UnSelectCell(CCScene* scene)
{
	this->RemoveCellContentSprite(selectionSprite);
	selectionSprite = NULL;

	PassingMap::HideDebugGrid(scene);
}

CCSprite * PanelTowers::AddTower(TowerTypes type, const int cellX, const int cellY)
{
	CCSprite *tower =  CCSprite::create(Tower::GetImage(type));
	this->SetSpriteCoords(tower, cellX,cellY,0,0);

	CCSprite *coin =  CCSprite::create(FILE_NAME_IMAGE_PANEL_COIN);
	coin->setScale(0.15f);
	this->SetCellContentSprite(coin, cellX,cellY,5,-15);

	char price[10];
	_itoa(Tower::GetPrice(type), price, 10);
	this->DisplayText(cellX * 10 + cellY, price, "Arial", 20, cellX, cellY, 0, -17);

	return tower;
}