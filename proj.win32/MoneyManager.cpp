#include "MoneyManager.h"


MoneyManager::MoneyManager(void)
{
	pthread_mutex_init (&mutex, NULL);
	money = 0;
}


MoneyManager::~MoneyManager(void)
{
}

int MoneyManager::GetMoneyBalance() const
{
	return money;
}

void MoneyManager::AddMoney(const int amount)
{
	pthread_mutex_lock(&mutex);

	money += amount;

	pthread_mutex_unlock(&mutex);
}

bool MoneyManager::SpendMoney(const int amount)
{
	int res = false;
	pthread_mutex_lock(&mutex);

	if (money >= amount){
		money -= amount;
		res = true;
	}

	pthread_mutex_unlock(&mutex);

	return res;
}

bool MoneyManager::CanSpendMoney(const int amount)
{
	int res = false;
	pthread_mutex_lock(&mutex);

	if (money >= amount){
		res = true;
	}

	pthread_mutex_unlock(&mutex);

	return res;
}
