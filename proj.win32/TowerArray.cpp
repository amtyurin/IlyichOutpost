#include "TowerArray.h"
#include "cocos2d.h"

using std::set;
using namespace cocos2d;

TowerArray::TowerArray(MoneyManager *moneyManager)
{
	this->moneyManager = moneyManager;
}

void TowerArray::addTower(Tower *tower){
	this->towerSet.push_back(tower);
}

Tower *TowerArray::createTower(int type, CCPoint position){
	Tower *newTower = new Tower(moneyManager, type, position);	
	towerSet.push_back(newTower);
	newTower->SetIndex(towerSet.size());
	return newTower;
}

vector<Tower*>::iterator TowerArray::begin() {
	return towerSet.begin();
}

vector<Tower*>::iterator TowerArray::end(){
	return towerSet.end();
}

TowerArray::~TowerArray(void)
{
}

Tower *TowerArray::GetTower(int index)
{
	index--;
	if (index >= 0 && index < towerSet.size())
		return towerSet[index];
	else
		return NULL;
}
