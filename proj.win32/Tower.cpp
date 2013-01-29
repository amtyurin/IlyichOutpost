#include "Tower.h"

using namespace cocos2d;

Tower::Tower(MoneyManager *moneyManager, int type, CCPoint _position) : 
		UpgradeBase(moneyManager, UPGRADES_COUNT_TOWER){
	//CCLog("Type: %d\n", type);
	this->moneyManager = moneyManager;

	char *image = NULL;
	switch (type){
		case MACHINE_GUN:
			this->damage = 10;
			this->fireSpeed = 10;
			this->fireRadius = 150;
			image = FILE_NAME_IMAGE_TOWER_MACHINE_GUN;
			CC_BREAK_IF(! this->spritePtr);
			break;
		case HEAVY_GUN:
			this->damage = 20;
			this->fireSpeed = 7;
			this->fireRadius = 170;
			image = FILE_NAME_IMAGE_TOWER_HEAVY_GUN;
			CC_BREAK_IF(! this->spritePtr);
			break;
		default:
			this->damage = 0;
			this->fireSpeed = 0;
			this->fireRadius = 0;
	}
	this->spritePtr = CCSprite::create(image);
	this->price = (this->damage + this->fireRadius + this->fireSpeed) / 2;
	this->SetUpgPriceForNextLevel(this->price * 2);	

	this->position=_position;
	this->spritePtr->setPosition(_position);
	this->reloadTime = 0;
	//CCLog("FireRadius: %d\n", this->fireRadius);
}


Tower::~Tower(void){
	//this->spritePtr->release();
}

void Tower::setX(float newX){
	this->position.x = newX;
}

void Tower::setY(float newY){
	this->position.y = newY;
}

CCSprite * Tower::getSprite() const{
	return this->spritePtr;
}

const bool Tower::operator < (const Tower &tower) const{
	/*int compareValue = this->position.x * 10000 + this->position.y;
	int compareValue2 = tower.getX() * 10000 + tower.getY();
	return compareValue < compareValue2;*/
	return (this < &tower);
}

void Tower::turnTo(const CCPoint point) const{
	//CCLog ("TurnTo called");
	double dx = this->position.x - point.x;
	double dy = this->position.y - point.y;
	int circleHalf;
	if (dy < 0){
		circleHalf = LOWER_HALF;
	}else{
		circleHalf = UPPER_HALF;
	}
	
	double tanOfAngle = (dx/dy);
	double angle = atan(tanOfAngle)*57.2957795135;
	if (circleHalf == UPPER_HALF){
		angle+=180;
	}
	if (angle >= 0 && angle <= 360){
		this->spritePtr->setRotation(angle);
	}
}

const bool Tower::operator> (const Tower &tower) const{
	return !(*this < tower);
}

const bool Tower::isTargetInRange(CCPoint target) const{
	//std::cout<<this->position.x<<"\t"<<this->position.y<<std::endl;
	//std::cout<<target.x<<"\t"<<target.y<<std::endl;
	double dX = abs(this->position.x - target.x);
	double dY = abs(this->position.y - target.y);
	double range = sqrt(pow(dX, 2) + pow(dY, 2));
	//CCLog("%f\t%d\n", range, this->fireRadius);
	if (range <= this->fireRadius) {
		return true;
	}else{
		return false;
	}
}

void Tower::processEnemies(Wave *wave){
	for (int i = 0; i < wave->GetEnemyCount(); i++){
		if (this->isTargetInRange(wave->GetEnemyPosition(i))){
			this->turnTo(wave->GetEnemyPosition(i));
			this->fire(wave, i);
			break;
		}
	}
}

void Tower::fire(Wave *wave, int index){
	if (this->isAbleToFire()){
#ifdef DEBUG_LOGS
		CCLog("Making damage");
#endif
		wave->MakeDamage(index, this->damage);
		this->reloadTime = GAME_SPEED / this->fireSpeed;
	}else{
#ifdef DEBUG_LOGS
		CCLog("Reloading");
#endif
		this->reloadTime--;
	}
}

const bool Tower::isAbleToFire() const{
	return (this->reloadTime <= 0);
}

void Tower::Upgrade()
{
#ifdef DEBUG_LOGS
	CCLog("Perform tower upgrade");
#endif
	UpgradeBase::Upgrade();	

	fireSpeed *= UPGRADE_COEF_TOWER;
	fireRadius *= UPGRADE_COEF_TOWER;
	damage *= UPGRADE_COEF_TOWER;
	reloadTime *= UPGRADE_COEF_TOWER;
}

bool Tower::CanBuy()
{
	return moneyManager->CanSpendMoney(this->price);
}

void Tower::Buy()
{
	moneyManager->SpendMoney(this->price);
}