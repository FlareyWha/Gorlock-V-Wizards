#include "HurricaneTower.h"

HurricaneTower::HurricaneTower(CP_Vector position)
{
	this->setColor(CP_Color_Create(0, 0, 255, 255));
	this->setDamage(0.25f);
	this->setSpeed(500.f);
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/hurricaneTower.png");
	setCooldown(0.1f);
	setTowerType(TOWER_TYPE::HURRICANETOWER);
}

HurricaneTower::~HurricaneTower()
{
}
