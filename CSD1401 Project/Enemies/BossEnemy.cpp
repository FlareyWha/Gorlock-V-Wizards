#include "BossEnemy.h"
#include "cprocessing.h"
#include "../Towers/BaseTower.h"
#include "../Utils/Utils.h"

BaseTower Tower;
BaseEnemy enemy;

BossEnemy::BossEnemy(CP_Vector location)
{
	SetLocation(location);
	SetHealth(200);
	SetMaxHealth(200);
	SetSpeed(25.0f);
	SetSprite(CP_Image_Load("Assets/Enemies/Boss.png"));
	SetSpriteLeft(CP_Image_Load("Assets/Enemies/Boss_Left.png"));
	SetReward(10000);
}

void BossEnemy::Render(void)
{
	if (directionVector.x > 0)
		CP_Image_Draw(sprite, location.x, location.y, spriteSize, spriteSize, 255);
	else if (directionVector.x < 0)
		CP_Image_Draw(spriteLeft, location.x, location.y, spriteSize, spriteSize, 255);

	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
	CP_Graphics_DrawRect(location.x, location.y - spriteSize * 0.5f, (float)health / (float)maxHealth * 50.f, 10.f);
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 50));
	CP_Graphics_DrawCircle(location.x, location.y, 155);
}

void BossEnemy::isIntersect(void){
		if (areCirclesIntersecting(Tower.getPosition(), Tower.getDetectionDistance(), GetLocation(),77.5))
		{
			//CP_Vector direction = CP_Vector_Normalize(CP_Vector_Set(enemy->GetLocation().x - tower->getPosition().x, enemy->GetLocation().y - tower->getPosition().y));
			Tower.setCooldown(0.0f);
			Tower.setCooldownTime(0.0f);
		}
}

BossEnemy::~BossEnemy()
{
	CP_Image_Free(GetSprite());
}



