#include "WindTower.h"
WindTower::WindTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/windTower.png");
	setCooldown(0.5f);
}

WindTower::~WindTower()
{
	CP_Image_Free(towerSprite);
}
