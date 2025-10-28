#include "FireTower.h"

FireTower::FireTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/fireTower.png");
}

FireTower::~FireTower()
{
	CP_Image_Free(towerSprite);
}