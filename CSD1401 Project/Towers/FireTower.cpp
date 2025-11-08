#include "FireTower.h"

FireTower::FireTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/fireTower.png");
	setDamage(1.0f);                             
	setSpeed(400.f);
	setCooldown(0.5f);
	setTowerType(TOWER_TYPE::FIRETOWER);
}

FireTower::~FireTower()
{
	CP_Image_Free(towerSprite);
}