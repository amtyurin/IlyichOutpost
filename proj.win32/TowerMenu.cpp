#include "TowerMenu.h"

using namespace cocos2d;

TowerMenu::TowerMenu(CCNode *scene)
{
	this->scene = scene;
}

TowerMenu::~TowerMenu(void)
{
}

CCSprite * TowerMenu::AddMenuItem(TowerMenuItem item, TouchableTowerSprite *tower, cocos2d::CCPoint position)
{
	char text[15]="\0";
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

