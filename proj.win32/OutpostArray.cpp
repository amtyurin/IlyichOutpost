#include "OutpostArray.h"


OutpostArray::OutpostArray(void)
{
	outpostSet.resize(0);
	outpostDestroyed = false;
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
					outpostDestroyed = true;
					break;
				}
			}
							
		}
	}
}

bool OutpostArray::OutpostDestroyed()
{
	return outpostDestroyed;
}
