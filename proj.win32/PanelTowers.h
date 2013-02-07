#pragma once
#include "panelbase.h"
#include "TouchableTowerSprite.h"

class PanelTowers :
	public PanelBase
{
	cocos2d::CCSprite *selectionSprite;

public:
	PanelTowers(cocos2d::CCNode *node, const cocos2d::CCPoint ccp, const cocos2d::CCSize size);
	virtual ~PanelTowers(void);

	CCSprite * AddTower(TowerTypes type, const int cellX, const int cellY);

	void SelectCell(cocos2d::CCScene* scene, TouchableTowerSprite *tSprite);
	void UnSelectCell(cocos2d::CCScene* scene);
};

