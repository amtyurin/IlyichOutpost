#pragma once
#include "cocos2d.h"
#include "PanelGeneral.h"
#include "PanelTowers.h"

class UILayer:public cocos2d::CCLayer
{
private:
	PanelGeneral *panelGeneral;
	PanelTowers *panelTowers;
public:
	UILayer(void);
	UILayer(CCScene *scene, CCPoint position, const CCSize size);
	~UILayer(void);
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
	virtual bool ccTouchEnd(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
	virtual bool ccTouchMove(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);

};

