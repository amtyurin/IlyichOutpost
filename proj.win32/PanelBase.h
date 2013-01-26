#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class PanelBase
{
	CCSprite *panelSprite;

	int cellsX;
	int cellsY;
	
public:
	PanelBase(CCScene *scene, const int cellsX, const int cellsY, const CCPoint ccp, const CCSize size);
	~PanelBase(void);

	void SetCellBorderImage(const char* image);
	void SetCellContentImage(const char* image, const int cellX, const int cellY);
	void SetCellContentSprite(CCSprite *sprite, const int cellX, const int cellY);
	void DisplayText(const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY);
};

