#include "PanelTowers.h"

#include "MainFieldScene.h"
#include "PassingMap.h"

PanelTowers::PanelTowers(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 1,5, ccp, size)
{	
	this->SetCellBorderImage("panel_border_common.png");

	CCSprite *tower1 =  CCSprite::create(FILE_NAME_IMAGE_TOWER_MACHINE_GUN);
	CCSprite *tower2 =  CCSprite::create(FILE_NAME_IMAGE_TOWER_HEAVY_GUN);
	this->SetCellContentSprite(tower1, 0,0);
	this->SetCellContentSprite(tower2, 0,1);

	((MainFieldScene *)scene)->addTouchableSprite(tower1, TAG_TOWER_MENU_MASK | 0 << 8  | 0);
	((MainFieldScene *)scene)->addTouchableSprite(tower2, TAG_TOWER_MENU_MASK | 0 << 8  | 1);	
}


PanelTowers::~PanelTowers(void)
{
}

void PanelTowers::SelectCell(CCScene* scene, CCSprite *sprite)
{	
	int tag = sprite->getTag() ^ TAG_TOWER_MENU_MASK;

	selectionSprite = CCSprite::create(FILE_NAME_IMAGE_PANEL_TOWER_SELECTION);
	this->SetCellContentSprite(selectionSprite, tag >> 8, tag & 0xf);
	selectionSprite->setOpacity(100);

	PassingMap::ShowDebugGrid(scene, STATE_CELL_BUILD);
}

void PanelTowers::UnSelectCell(CCScene* scene)
{
	this->RemoveCellContentSprite(selectionSprite);
	selectionSprite = NULL;

	PassingMap::HideDebugGrid(scene);
}