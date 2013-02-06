#include "PanelTowers.h"

#include "MainFieldScene.h"
#include "PassingMap.h"

#include "TouchableTowerSprite.h"

PanelTowers::PanelTowers(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 1,5, ccp, size)
{	
	this->SetCellBorderImage("panel_border_common.png");

	CCSprite *tower1 =  CCSprite::create(FILE_NAME_IMAGE_TOWER_MACHINE_GUN);
	CCSprite *tower2 =  CCSprite::create(FILE_NAME_IMAGE_TOWER_HEAVY_GUN);
	this->SetCellContentSprite(tower1, 0,0,0,0);
	this->SetCellContentSprite(tower2, 0,1,0,0);

	CCSprite *coin =  CCSprite::create(FILE_NAME_IMAGE_PANEL_COIN);
	coin->setScale(0.15f);
	this->SetCellContentSprite(coin, 0,0,5,-15);
	coin = CCSprite::createWithTexture(coin->getTexture());
	coin->setScale(0.15f);
	this->SetCellContentSprite(coin, 0,1, 5, -15);

	char price[10];
	_itoa(Tower::GetPrice(MACHINE_GUN), price, 10);
	this->DisplayText(1, price, "Arial", 20,0,0,0,-17);
	_itoa(Tower::GetPrice(HEAVY_GUN), price, 10);
	this->DisplayText(2, price, "Arial", 20,0,1,0,-17);

	TouchableTowerSprite *tSprite = new TouchableTowerSprite();
	tSprite->towerType = MACHINE_GUN;
	tSprite->index = 0;
	tSprite->towerPlace = TOWER_MENU;
	tSprite->sprite = tower1;
	tSprite->cellX = 0;
	tSprite->cellY = 0;
	((MainFieldScene *)scene)->addTouchableSprite(tSprite);
	tSprite = new TouchableTowerSprite();
	tSprite->towerType = HEAVY_GUN;
	tSprite->index = 1;
	tSprite->towerPlace = TOWER_MENU;
	tSprite->sprite = tower2;
	tSprite->cellX = 0;
	tSprite->cellY = 1;
	((MainFieldScene *)scene)->addTouchableSprite(tSprite);
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