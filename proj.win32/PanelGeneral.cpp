#include "PanelGeneral.h"

using namespace cocos2d;

PanelGeneral::PanelGeneral(CCNode *node, const CCPoint ccp, const CCSize size)
	: PanelBase(4,1, ccp, size)
{
	node->addChild(this->panelSprite);

	this->SetCellBorderImage(FILE_NAME_IMAGE_PANEL_BORDER);

	CCSprite *coin =  CCSprite::create(FILE_NAME_IMAGE_PANEL_COIN);
	coin->setScaleX(0.15f);
	coin->setScaleY(0.25f);
	this->SetCellContentSprite(coin, 0,0,-10,5);	
}


PanelGeneral::~PanelGeneral(void)
{
}
