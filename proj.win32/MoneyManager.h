#pragma once
#include <pthread\pthread.h>

class MoneyManager
{
	int money;
	pthread_mutex_t mutex;

public:
	MoneyManager(void);
	~MoneyManager(void);

	int GetMoneyBalance() const;
	void AddMoney(const int amount);
	bool CanSpendMoney(const int amount);
	bool SpendMoney(const int amount);
};

