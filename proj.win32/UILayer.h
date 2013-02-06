#pragma once
#include "cocos2d.h"
#include "PanelGeneral.h"
#include "PanelTowers.h"
#include "TouchableTowerSprite.h"
#include <vector>

#define TOWER_PANEL_POSITION 45
#define GENERAL_PANEL_POSITION 20

class UILayer:public cocos2d::CCLayer
{
private:
	PanelGeneral *panelGeneral;
	PanelTowers *panelTowers;
	UILayer(void);
	CCSize size;
	cocos2d::CCSprite *touchedPanel;
	cocos2d::CCSprite *touchedSprite;
	std::vector<TouchableTowerSprite *> touchableSprites;
	cocos2d::CCScene *scene;

public:
	UILayer(CCScene *scene);
	~UILayer(void);
	const PanelTowers * getPanelTowersPointer()const{ return panelTowers;};
	const PanelGeneral * getPanelGeneralPointer()const{ return panelGeneral;};
	void displayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY);
	void SelectCell(CCScene* scene, TouchableTowerSprite *tSprite);
	void UnSelectCell(CCScene* scene);
	void addSprite(TouchableTowerSprite *sprite);
	virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
	virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *pEvent);
};

