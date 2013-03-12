#pragma once

#include <stdlib.h>
#include <vector>

#include "cocos2d.h"

#include "FileNames.h"

enum CellState
{
	STATE_CELL_FREE = 0,
	STATE_CELL_BUSY,
	STATE_CELL_BUILD_FOR_US,
	STATE_CELL_BUILD_FOR_ENEMY
};

struct Cell
{
	CellState type;
	int x; // center of cell
	int y; // center of cell
	int indX;
	int indY;

	cocos2d::CCSprite *sprite;
};

class Waypoint
{
	std::vector<Cell *> way;

public:
	Waypoint(void);
	~Waypoint(void);

	void AddPoint(Cell *);
	void RemovePoint(const Cell *);

	Cell* GetPoint(const size_t index);
};
