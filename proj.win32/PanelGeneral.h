#pragma once
#include "panelbase.h"

class PanelGeneral :
	public PanelBase
{
public:
	PanelGeneral(cocos2d::CCNode *node, const cocos2d::CCPoint ccp, const cocos2d::CCSize size);
	virtual ~PanelGeneral(void);
};

