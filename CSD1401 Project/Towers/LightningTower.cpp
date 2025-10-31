#include "LightningTower.h"
LightningTower::LightningTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/lightningTower.png");
}

LightningTower::~LightningTower()
{
	CP_Image_Free(towerSprite);
}
