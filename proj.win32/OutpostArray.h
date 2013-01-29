#pragma once
#include "cocos2d.h"
#include "Outpost.h"
#include <vector>

using namespace std;

class OutpostArray
{
	vector<Outpost *> outpostSet;

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

