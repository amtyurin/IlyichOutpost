#include "TowerArray.h"
#include "cocos2d.h"

using namespace std;
using std::set;
using namespace cocos2d;

TowerArray::TowerArray(MoneyManager *moneyManager)
{
	this->moneyManager = moneyManager;
	pthread_mutex_init (&mutex, NULL);
}

void TowerArray::addTower(Tower *tower){
	pthread_mutex_lock(&mutex);
	this->towerSet.push_back(tower);
	pthread_mutex_unlock(&mutex);
}

void TowerArray::removeTower(Tower *tower)
{
	pthread_mutex_lock(&mutex);
	towerSet.erase(std::remove(towerSet.begin(), towerSet.end(), tower), towerSet.end());
	pthread_mutex_unlock(&mutex);
}

Tower *TowerArray::createTower(TowerTypes type, CCPoint position){
	Tower *newTower = new Tower(moneyManager, type, position);	

	addTower(newTower);

	newTower->SetIndex(towerSet.size());
	return newTower;
}

vector<Tower*>::iterator TowerArray::begin() {
	vector<Tower*>::iterator it;
	pthread_mutex_lock(&mutex);
	it = towerSet.begin();
	pthread_mutex_unlock(&mutex);
	return it;
}

vector<Tower*>::iterator TowerArray::end(){
	vector<Tower*>::iterator it;
	pthread_mutex_lock(&mutex);
	it = towerSet.end();
	pthread_mutex_unlock(&mutex);
	return it;
}

TowerArray::~TowerArray(void)
{
}

Tower *TowerArray::GetTower(size_t index)
{
	index--;
	Tower *tower = NULL;

	pthread_mutex_lock(&mutex);
	if (index >= 0 && index < towerSet.size())
		tower = towerSet[index];
	pthread_mutex_unlock(&mutex);

	return tower;
}

bool TowerArray::Buy(TowerTypes type)
{
	return moneyManager->SpendMoney(Tower::GetPrice(type));
}

