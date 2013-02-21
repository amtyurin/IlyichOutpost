#include "Tower.h"

using namespace cocos2d;

Tower::Tower(MoneyManager *moneyManager, TowerTypes type, CCPoint _position) : 
		UpgradeBase(moneyManager, UPGRADES_COUNT_TOWER){
	//CCLog("Type: %d\n", type);
	this->index = 0;

	this->damage = GetDamage(type);
	this->fireSpeed = GetFireSpeed(type);
	this->fireRadius = GetRadius(type);
	this->spritePtr = CCSprite::create(GetImage(type));
	this->SetUpgPriceForNextLevel(GetPrice(type) * 2);	

	this->position=_position;
	this->spritePtr->setPosition(_position);
	this->reloadTime = 0;	
	this->type = type;

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
	double range = ccpDistance(spritePtr->getPosition(), target);
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
		this->startFireAnimation(this->position, wave->GetEnemyPosition(index));		
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
	if (UpgradeBase::CanUpgrade()){
		UpgradeBase::Upgrade();

		fireSpeed *= UPGRADE_COEF_TOWER;
		fireRadius *= UPGRADE_COEF_TOWER;
		damage *= UPGRADE_COEF_TOWER;
		reloadTime *= UPGRADE_COEF_TOWER;
	}
}

void Tower::SetIndex(const int i)
{
	this->index = i;
}

void Tower::ShowRange()
{	
	this->spriteRangePtr = CCSprite::create(FILE_NAME_IMAGE_TOWER_RANGE);
	this->spriteRangePtr->setPosition(this->spritePtr->getPosition());
	this->spriteRangePtr->setScale((float)this->fireRadius / (this->spriteRangePtr->getContentSize().width / 2.0));
	this->spriteRangePtr->setOpacity(50);
	this->spritePtr->getParent()->addChild(this->spriteRangePtr, 5);	
}

void Tower::HideRange()
{	
	if (this->spriteRangePtr){
		this->spritePtr->getParent()->removeChild(this->spriteRangePtr, true);
		this->spriteRangePtr = NULL;
	}
}

int Tower::GetPrice(TowerTypes type)
{
	return (GetDamage(type) + GetFireSpeed(type) + GetRadius(type) * 0.8);
}

int Tower::GetDamage(TowerTypes type)
{
	int damage = 0;
	switch (type){
		case MACHINE_GUN:
			damage = 10;			
			break;
		case HEAVY_GUN:
			damage = 20;			
			break;
		case SNIPER_GUN:
			damage = 40;
			break;
		case ANTITANK_GUN:
			damage = 80;
			break;
		case LASER_GUN:
			damage = 100;
			break;
		case ROCKET_GUN:
			damage = 60;
			break;
		case ELECTROMAGNETIC_GUN:
			damage = 40;
			break;
		case FLAME_GUN:
			damage = 80;
			break;
		case NAPALM_GUN:
			damage = 150;
			break;
	}
	return damage;
}

int Tower::GetFireSpeed(TowerTypes type)
{
	int speed = 0;
	switch (type){
		case MACHINE_GUN:
			speed = 7;			
			break;
		case HEAVY_GUN:
			speed = 9;			
			break;
		case SNIPER_GUN:
			speed = 1;
			break;
		case ANTITANK_GUN:
			speed = 3;
			break;
		case LASER_GUN:
			speed = 4;
			break;
		case ROCKET_GUN:
			speed = 7;
			break;
		case ELECTROMAGNETIC_GUN:
			speed = 2;
			break;
		case FLAME_GUN:
			speed = 5;
			break;
		case NAPALM_GUN:
			speed = 5;
			break;
	}
	return speed;
}

int Tower::GetRadius(TowerTypes type)
{
	int radius = 0;
	switch (type){
		case MACHINE_GUN:
			radius = 100;			
			break;
		case HEAVY_GUN:
			radius = 150;			
			break;
		case SNIPER_GUN:
			radius = 300;
			break;
		case ANTITANK_GUN:
			radius = 150;
			break;
		case LASER_GUN:
			radius = 250;
			break;
		case ROCKET_GUN:
			radius = 200;
			break;
		case ELECTROMAGNETIC_GUN:
			radius = 100;
			break;
		case FLAME_GUN:
			radius = 100;
			break;
		case NAPALM_GUN:
			radius = 150;
			break;
	}
	return radius;
}

char* Tower::GetImage(TowerTypes type)
{
	char *image = NULL;
	switch (type){
		case MACHINE_GUN:			
			image = FILE_NAME_IMAGE_TOWER_MACHINE_GUN;
			break;
		case HEAVY_GUN:
			image = FILE_NAME_IMAGE_TOWER_HEAVY_GUN;
			break;
		case SNIPER_GUN:
			image = FILE_NAME_IMAGE_TOWER_SNIPER_GUN;
			break;
		case ANTITANK_GUN:
			image = FILE_NAME_IMAGE_TOWER_ANTITANK_GUN;
			break;
		case LASER_GUN:
			image = FILE_NAME_IMAGE_TOWER_LASER_GUN;
			break;
		case ROCKET_GUN:
			image = FILE_NAME_IMAGE_TOWER_ROCKET_GUN;
			break;
		case ELECTROMAGNETIC_GUN:
			image = FILE_NAME_IMAGE_TOWER_ELECTROMAGNETIC_GUN;
			break;
		case FLAME_GUN:
			image = FILE_NAME_IMAGE_TOWER_FLAME_GUN;
			break;
		case NAPALM_GUN:
			image = FILE_NAME_IMAGE_TOWER_NAPALM_GUN;
			break;
	}
	return image;
}

void Tower::startFireAnimation(const CCPoint startPosition, const CCPoint endPosition){
	CCSprite *shellSprite = CCSprite::create(FILE_NAME_MACHINEGUN_BULLET);
	CCNode *parent = this->spritePtr->getParent();
	shellSprite->setPosition(startPosition);
	shellSprite->setScale(0.3f);
	CCFiniteTimeAction *actionMove = CCMoveTo::create(TIMEOUT_ANIMATION, endPosition);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(parent, callfuncN_selector(Tower::deleteShell));
	parent->addChild(shellSprite);
	shellSprite->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
}

void Tower::deleteShell(CCNode *sender){
	CCSprite *shellSprite = (CCSprite*) sender;
	shellSprite->removeFromParent();
}

TowerTypes Tower::GetType() const
{
	return type;
}

int Tower::GetSellPrice() const
{
	return GetCurrentUpgLevel() * Tower::GetPrice(GetType()) / 2;
}