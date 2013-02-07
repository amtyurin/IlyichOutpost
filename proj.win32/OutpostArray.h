#pragma once
#include "cocos2d.h"
#include "Outpost.h"
#include <vector>

class OutpostArray
{
	std::vector<Outpost *> outpostSet;

	bool enemyOutpostDestroyed;
	bool ourOutpostDestroyed;
public:
	OutpostArray(void);
	~OutpostArray(void);

	void AddOutpost(Outpost *outpost);
	void ProcessEnemies(Wave *enemyWave);
	bool OutpostEnemyDestroyed();
	bool OutpostOurDestroyed();
};

