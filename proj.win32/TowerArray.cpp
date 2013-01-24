#include "TowerArray.h"
#include "cocos2d.h"

using std::set;
using namespace cocos2d;

TowerArray::TowerArray(void)
{
}

void TowerArray::addTower(Tower &tower){
	this->towerSet.push_back(tower);
}

void TowerArray::removeTower(Tower &tower){
	//this->towerSet.erase(tower);
}

vector<Tower>::iterator TowerArray::begin() {
	return towerSet.begin();
}

vector<Tower>::iterator TowerArray::end(){
	return towerSet.end();
}

TowerArray::~TowerArray(void)
{
}