#pragma once

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

using namespace cocos2d;

enum CellState
{
	STATE_CELL_FREE = 0,
	STATE_CELL_BUSY,
	STATE_CELL_BUILD
};

struct Cell
{
	CellState type;
};

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

	static Cell map[MAP_HEIGHT_MAX][MAP_WIDTH_MAX];	
	
public:

	static void ClearMap();

	static CellState GetCellSTate(int x, int y);
	static void SetCellState(int x, int y, CellState state);

	static void ShowDebugGrid(CCScene *scene);	


	
	~PassingMap(void);
};
