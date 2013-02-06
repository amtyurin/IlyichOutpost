#pragma once
#include "panelbase.h"
#include "TouchableTowerSprite.h"

class PanelTowers :
	public PanelBase
{
	CCSprite *selectionSprite;

public:
	PanelTowers(CCScene *scene, const CCPoint ccp, const CCSize size);
	virtual ~PanelTowers(void);

	void SelectCell(CCScene* scene, TouchableTowerSprite *tSprite);
	void UnSelectCell(CCScene* scene);
};

