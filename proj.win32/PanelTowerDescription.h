#pragma once
#include "panelbase.h"
#include "TouchableTowerSprite.h"

class PanelTowerDescription:
	public PanelBase
{
	cocos2d::CCSize size;
public:
	PanelTowerDescription(cocos2d::CCNode * node, const cocos2d::CCSize size);
	~PanelTowerDescription(void);

	void Show(TouchableTowerSprite *tower);
	void Hide();
};

