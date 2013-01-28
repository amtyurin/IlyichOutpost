#include "UpgradeBase.h"


UpgradeBase::UpgradeBase(MoneyManager *moneyManager, const int maxLevel)
{
	this->moneyManager = moneyManager;
	this->currLevel = 1;
	this->maxLevel = maxLevel;
	this->priceForNextLevel = priceForNextLevel;
}


UpgradeBase::~UpgradeBase(void)
{
}

void UpgradeBase::SetUpgPriceForNextLevel(const int priceForNextLevel)
{
	this->priceForNextLevel = priceForNextLevel;
}

int UpgradeBase::GetUpgradePrice() const
{
	return this->priceForNextLevel;
}

int UpgradeBase::GetMaxUpgLevel() const
{
	return this->maxLevel;
}

int UpgradeBase::GetCurrentUpgLevel() const
{
	return this->currLevel;
}

bool UpgradeBase::CanUpgrade()
{
	if (currLevel < maxLevel){
		return moneyManager->CanSpendMoney(priceForNextLevel);
	}
	return false;
}

void UpgradeBase::Upgrade()
{
	if (currLevel < maxLevel){
		if (moneyManager->SpendMoney(priceForNextLevel)){
			currLevel++;
			priceForNextLevel *= NEXT_LEVEL_PRICE_GROWTH;
		}
	}
}
