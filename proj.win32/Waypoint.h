#pragma once

#include <stdlib.h>
#include <vector>

#include "cocos2d.h"

#include "FileNames.h"

using namespace std;

enum CellState
{
	STATE_CELL_FREE = 0,
	STATE_CELL_BUSY,
	STATE_CELL_BUILD
};

struct Cell
{
	CellState type;
	int x; // center of cell
	int y; // center of cell

	cocos2d::CCSprite *sprite;
};

class Waypoint
{
	vector<Cell *> way;

public:
	Waypoint(void);
	~Waypoint(void);

	void AddPoint(Cell *);
	void RemovePoint(const Cell *);

	Cell* GetPoint(const int index);
};

