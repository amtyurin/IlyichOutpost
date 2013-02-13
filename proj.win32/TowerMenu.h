#pragma once
#include "panelbase.h"
#include "TouchableTowerSprite.h"

enum TowerMenuItem
{
	UPGRADE,
	DESTROY
};

class TowerMenu:
	public PanelBase
{
public:
	TowerMenu(const int cellsX, const int cellsY, cocos2d::CCNode * node, const cocos2d::CCSize size);
	~TowerMenu(void);

	cocos2d::CCSprite * AddMenuItem(TowerMenuItem item, TouchableTowerSprite *tower, const int cellX, const int cellY);

	void Hide();
};

