#include "PanelTowerDescription.h"

using namespace cocos2d;

PanelTowerDescription::PanelTowerDescription(CCNode * node, const cocos2d::CCSize size)
	: PanelBase(1,3, ccp(0,0), size)
{
	this->size = size;
	node->addChild(this->panelSprite);

	SetCellBorderImage(NULL);
}

PanelTowerDescription::~PanelTowerDescription(void)
{
}

void PanelTowerDescription::Show(TouchableTowerSprite *tower)
{
	this->panelSprite->setPositionX(tower->sprite->getPositionX() - 2 * this->size.width);
	this->panelSprite->setPositionY(tower->sprite->getPositionY());

	char text[15]="\0";
	snprintf(text, 15, "Range:%d",Tower::GetRadius(tower->towerType));
	this->DisplayText(200, text, "Arial", ccc3(255,255,255), 18, 0,2, 0,0);
	snprintf(text, 15, "Damage:%d",Tower::GetDamage(tower->towerType));
	this->DisplayText(201, text, "Arial", ccc3(255,255,255), 18, 0,1, 0,0);
	snprintf(text, 15, "Speed:%d",Tower::GetFireSpeed(tower->towerType));
	this->DisplayText(202, text, "Arial", ccc3(255,255,255), 18, 0,0, 0,0);
}

void PanelTowerDescription::Hide()
{
	this->panelSprite->setPositionY(-100);
}
