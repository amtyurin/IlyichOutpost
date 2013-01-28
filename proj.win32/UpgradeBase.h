#pragma once

#include "MoneyManager.h"

#define NEXT_LEVEL_PRICE_GROWTH 1.5
#define UPGRADE_LEVEL 1.2

class UpgradeBase
{
	int currLevel;
	int priceForNextLevel;
	int maxLevel;

	MoneyManager *moneyManager;

protected:
	void SetUpgPriceForNextLevel(const int priceForNextLevel);
	
public:
	UpgradeBase(MoneyManager *moneyManager, const int maxLevel);
	~UpgradeBase(void);


	int GetUpgradePrice() const;
	int GetMaxUpgLevel() const;
	int GetCurrentUpgLevel() const;

	bool CanUpgrade();
	virtual void Upgrade() = 0;
};

