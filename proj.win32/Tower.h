#pragma once

class Tower
{
private:
	int fireSpeed;
	int fireRadius;
	int damage;
	float normRotateX;
	float normRotateY;
	int posX;
	int posY;

public:
	Tower(void);
	Tower(int _damage, int _fireSpeed, int _fireRadius);
	~Tower(void);
	
};

