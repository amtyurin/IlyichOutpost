#include "GameAI.h"


GameAI::GameAI(cocos2d::CCLayer *ui, Waypoint *way, BuildCells *buildCells)
	: Player(way, buildCells)
{
	this->ui = ui;
}


GameAI::~GameAI(void)
{
}
