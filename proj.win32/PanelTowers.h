#pragma once
#include "panelbase.h"
#include "TouchableTowerSprite.h"

class PanelTowers :
	public PanelBase
{
public:
	PanelTowers(cocos2d::CCNode *node, const int cellsCount, const cocos2d::CCPoint ccp, const cocos2d::CCSize size);
	virtual ~PanelTowers(void);

	cocos2d::CCSprite * AddTower(TowerTypes type, const int cellX, const int cellY);
};

