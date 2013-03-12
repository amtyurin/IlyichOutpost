#pragma once
#include "player.h"

class GameAI :
	public Player
{
	cocos2d::CCLayer *ui;

public:
	GameAI(cocos2d::CCLayer *ui, Waypoint *way, BuildCells *buildCells);
	~GameAI(void);
};

