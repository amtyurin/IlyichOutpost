#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

#include "Waypoint.h"

class PassingMap
{
public:
	static int const MAP_CELL_SIZE = 32;
	static int const MAP_WIDTH_MAX = 800 / MAP_CELL_SIZE; // 800
	static int const MAP_HEIGHT_MAX = 600 / MAP_CELL_SIZE; // 600	

private:
	PassingMap(void);
	PassingMap(PassingMap const&);              // Don't Implement
    void operator=(PassingMap const&); // Don't implement	

	static Cell map[MAP_WIDTH_MAX][MAP_HEIGHT_MAX];	

	static cocos2d::CCSprite *spriteAll;	
public:

	static void ClearMap();

	static CellState GetCellSTate(const int x, const int y);
	static Cell* GetCell(const int x, const int y);
	static void SetCellState(const int x, const int y, const CellState state);

	static void ShowDebugGrid(cocos2d::CCScene *scene, CellState type);	
	static void HideDebugGrid(cocos2d::CCScene *scene);

	static void ShowWaypoint(Waypoint *way, cocos2d::CCScene *scene);
	
	~PassingMap(void);
};
