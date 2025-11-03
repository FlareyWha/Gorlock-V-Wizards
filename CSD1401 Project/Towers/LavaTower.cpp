#include "LavaTower.h"

LavaTower::LavaTower(CP_Vector position)
{
	setPos(position.x, position.y);
	towerSprite = CP_Image_Load("Assets/Towers/lavaTower.png");
}

LavaTower::~LavaTower()
{
	CP_Image_Free(towerSprite);
}