#include "PanelTowers.h"

#include "MainFieldScene.h"

PanelTowers::PanelTowers(CCScene *scene, const CCPoint ccp, const CCSize size)
	: PanelBase(scene, 1,5, ccp, size)
{	
	this->SetCellBorderImage("panel_border_common.png");

	CCSprite *tower1 =  CCSprite::create(FILE_NAME_IMAGE_TOWER_MACHINE_GUN);
	CCSprite *tower2 =  CCSprite::create(FILE_NAME_IMAGE_TOWER_HEAVY_GUN);
	this->SetCellContentSprite(tower1, 0,0);
	this->SetCellContentSprite(tower2, 0,1);

	((MainFieldScene *)scene)->addTouchableSprite(tower1, TAG_TOWER_MENU_MASK | 1);
	((MainFieldScene *)scene)->addTouchableSprite(tower2, TAG_TOWER_MENU_MASK | 2);	
}


PanelTowers::~PanelTowers(void)
{
}

void PanelTowers::SelectCell(CCSprite *sprite)
{	
	selectionSprite = CCSprite::create(FILE_NAME_IMAGE_PANEL_TOWER_SELECTION);
	selectionSprite->setPosition(sprite->getPosition());
	selectionSprite->setScale(sprite->getScaleX() * sprite->getContentSize().width / selectionSprite->getContentSize().width);
	selectionSprite->setOpacity(100);
	sprite->addChild(selectionSprite);
}

void PanelTowers::UnSelectCell(CCSprite *sprite)
{
	sprite->removeChild(selectionSprite,false);	
	selectionSprite = NULL;
}