#include "WindTower.h"

WindTower::WindTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/windTower.png");
}

WindTower::~WindTower()
{
}
