#include "OutpostArray.h"


OutpostArray::OutpostArray(void)
{
	outpostSet.resize(0);
	enemyOutpostDestroyed = false;
	ourOutpostDestroyed = false;
}


OutpostArray::~OutpostArray(void)
{
}

void OutpostArray::AddOutpost(Outpost *outpost)
{
	outpostSet.push_back(outpost);
}

void OutpostArray::ProcessEnemies(Wave *enemyWave){
	for (int i = 0; i < enemyWave->GetEnemyCount(); i++){
		for (unsigned int o = 0; o < outpostSet.size(); o++){
			if (outpostSet[o]->isTargetInRange(enemyWave->GetEnemyPosition(i))){
				enemyWave->MakeDamage(i, 1000000);
				if (outpostSet[o]->MakeDamage())
				{
					switch(outpostSet[o]->GetOutpostType()){
						case OUTPOST_TYPE_ENEMY:
							enemyOutpostDestroyed = true;
							break;
						case OUTPOST_TYPE_OUR:
							ourOutpostDestroyed = true;
							break;
					}
					continue;
				}
			}
							
		}
	}
}

bool OutpostArray::OutpostEnemyDestroyed()
{
	return enemyOutpostDestroyed;
}

bool OutpostArray::OutpostOurDestroyed()
{
	return ourOutpostDestroyed;
}
