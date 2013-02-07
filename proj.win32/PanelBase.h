#pragma once
#include "cocos2d.h"

#include "FileNames.h"

#define TEXT_SIZE 30

struct PanelCell
{
	char text[TEXT_SIZE];
	cocos2d::CCSprite *spriteCell;
};

class PanelBase
{
	int cellsX;
	int cellsY;

	PanelCell **cells;	

protected:
	cocos2d::CCSprite *panelSprite;
	
public:
	PanelBase(const int cellsX, const int cellsY, const cocos2d::CCPoint ccp, const cocos2d::CCSize size);
	~PanelBase(void);

	void RemoveCellContentSprite(cocos2d::CCSprite *sprite);
	void SetCellBorderImage(const char* image);
	void SetCellContentImage(const char* image, const int cellX, const int cellY);
	void SetCellContentSprite(cocos2d::CCSprite *sprite, const int cellX, const int cellY, const int locX, const int locY);
	void DisplayText(const int tag, const char *text, const char *font, const int size, const int cellX, const int cellY, const int locX, const int locY);
};

