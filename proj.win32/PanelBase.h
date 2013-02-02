#pragma once
#include "cocos2d.h"

#include "FileNames.h"

using namespace cocos2d;

#define TEXT_SIZE 30

struct PanelCell
{
	char text[TEXT_SIZE];
};

class PanelBase
{
	int cellsX;
	int cellsY;

	PanelCell **cells;	

protected:
	CCSprite *panelSprite;
	
public:
	PanelBase(CCScene *scene, const int cellsX, const int cellsY, const CCPoint ccp, const CCSize size);
	~PanelBase(void);

	void RemoveCellContentSprite(CCSprite *sprite);
	void SetCellBorderImage(const char* image);
	void SetCellContentImage(const char* image, const int cellX, const int cellY);
	void SetCellContentSprite(CCSprite *sprite, const int cellX, const int cellY);
	void DisplayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY);
};

