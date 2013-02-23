#include "ElectromagneticTower.h"

using namespace cocos2d;

ElectromagneticTower::ElectromagneticTower(MoneyManager *moneyManager, TowerTypes type, CCPoint _position):
	Tower(moneyManager, type, _position)
{
}


ElectromagneticTower::~ElectromagneticTower(void)
{
}

void ElectromagneticTower::processEnemies(Wave *wave){
	for (int i = 0; i < wave->GetEnemyCount(); i++){
		if (this->isTargetInRange(wave->GetEnemyPosition(i))){
			//this->turnTo(wave->GetEnemyPosition(i));
			this->fire(wave, i);
		}
	}
}

void ElectromagneticTower::fire(Wave *wave, int index){
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

void ElectromagneticTower::startFireAnimation(const CCPoint startPosition, const CCPoint endPosition){
	CCSprite *shellSprite = CCSprite::create(FILE_NAME_MACHINEGUN_BULLET);
	CCNode *parent = this->spritePtr->getParent();
	shellSprite->setPosition(startPosition);
	shellSprite->setScale(0.3f);
	CCFiniteTimeAction *actionMove = CCMoveTo::create(TIMEOUT_ANIMATION, endPosition);
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create(parent, callfuncN_selector(ElectromagneticTower::deleteShell));
	parent->addChild(shellSprite);
	shellSprite->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));

	this->firingSprite = CCSprite::create(GetFiringSprite(this->type));
	this->firingSprite->setPosition(this->position);
	this->firingSprite->setRotation(this->spritePtr->getRotation());
	parent->addChild(this->firingSprite);

	CCFiniteTimeAction *pause = CCDelayTime::create(0.1);
	CCFiniteTimeAction *getAway = CCCallFuncN::create(parent, callfuncN_selector(ElectromagneticTower::endFireAnimation));
	this->firingSprite->runAction(CCSequence::create(pause, getAway, NULL));
}

void ElectromagneticTower::deleteShell(CCNode *sender){
	CCSprite *shellSprite = (CCSprite*) sender;
	shellSprite->removeFromParent();
}

void ElectromagneticTower::endFireAnimation(CCNode *sender){
	CCSprite *fireSprite = (CCSprite*) sender;
	fireSprite->removeFromParent();
}
