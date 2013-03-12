#include "Player.h"

Player::Player(Waypoint *way, BuildCells *buildCells)
{
	this->buildCells = buildCells;
	this->way = way;
	this->wave = NULL;
	this->towers = new TowerArray(&this->moneyManager);
}

Player::~Player(void)
{
}

void Player::ProcessStepLogic()
{
	if (this->wave != NULL){	
		for (std::vector<Tower*>::iterator it = this->towers->begin(); it != this->towers->end(); it++){
			(*it)->processEnemies(this->wave);
		}	

		outposts.ProcessEnemies(this->wave);
	}
}
