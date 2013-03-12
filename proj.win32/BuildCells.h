#pragma once

#include <vector>

#include "cocos2d.h"

#include "FileNames.h"
#include "Waypoint.h"

class BuildCells
{	
public:
	BuildCells(void);
	~BuildCells(void);

	std::vector<Cell *> cells;
};

