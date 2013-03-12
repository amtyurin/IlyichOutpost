#pragma once

#include "Waypoint.h"
#include "Wave.h"
#include "Tower.h"
#include "TowerArray.h"
#include "OutpostArray.h"
#include "MoneyManager.h"
#include "BuildCells.h"

class Player
{
public:

	BuildCells *buildCells;	
	Wave *wave;
	Waypoint *way;

	TowerArray *towers;
	OutpostArray outposts;

	MoneyManager moneyManager;	

	Player(Waypoint *way, BuildCells *buildCells);
	~Player(void);

	void ProcessStepLogic();
};

