#include "IceTower.h"

IceTower::IceTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/iceTower.png");
}

IceTower::~IceTower()
{
}
