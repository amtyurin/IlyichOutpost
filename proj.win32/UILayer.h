#pragma once
#include "cocos2d.h"
#include "TouchableTowerSprite.h"
#include "TowerArray.h"
#include "PanelGeneral.h"
#include "PanelTowers.h"
#include <vector>

#define TOWER_PANEL_POSITION 35
#define GENERAL_PANEL_POSITION 20

class UILayer : public cocos2d::CCLayer
{
private:
	PanelGeneral *panelGeneral;
	PanelTowers *panelTowers;

	UILayer(void);

	cocos2d::CCSize size;

	TouchableTowerSprite *touchedTowerSprite;
	TouchableTowerSprite *movingTowerSprite;
	std::vector<TouchableTowerSprite *> touchableSprites;

	cocos2d::CCScene *scene;
	TowerArray *towers;

	void addTouchableTower(TowerTypes towerType, cocos2d::CCPoint position);
	void addTowerToPanel(TowerTypes towerType, const int cellX, const int cellY);

public:
	UILayer(cocos2d::CCScene *scene, TowerArray *towers);
	~UILayer(void);
	const PanelTowers * getPanelTowersPointer()const{ return panelTowers;};
	const PanelGeneral * getPanelGeneralPointer()const{ return panelGeneral;};
	void displayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY);
	void SelectCell(cocos2d::CCScene* scene, TouchableTowerSprite *tSprite);
	void UnSelectCell(cocos2d::CCScene* scene);

	void addTouchableSprite(TouchableTowerSprite *sprite);

	void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	//void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
};

