#include "BaseEnemy.h"
#include <stdio.h>
#include <stdlib.h>

int BaseEnemy::GetHealth(void)
{
    return health;
}

void BaseEnemy::SetHealth(int health)
{
    health >= 0 ? this->health = health : this->health = 0;
}

int BaseEnemy::GetMaxHealth(void)
{
    return maxHealth;
}

void BaseEnemy::SetMaxHealth(int health)
{
    this->maxHealth = health;
}

int BaseEnemy::GetReward(void)
{
    return reward;
}

void BaseEnemy::SetReward(int rewardAmt)
{
    reward = rewardAmt;
}

float BaseEnemy::GetSpeed(void)
{
    return speed;
}

void BaseEnemy::SetSpeed(float speed)
{
    this->speed = speed;
}

float BaseEnemy::GetSpriteSize()
{
    return spriteSize;
}

CP_Image BaseEnemy::GetSprite(void)
{
    return sprite;
}

void BaseEnemy::SetSprite(CP_Image sprite)
{
    this->sprite = sprite;
}

CP_Image BaseEnemy::GetSpriteLeft(void)
{
    return spriteLeft;
}

void BaseEnemy::SetSpriteLeft(CP_Image sprite)
{
    this->spriteLeft = sprite;
}

CP_Vector BaseEnemy::GetLocation(void)
{
    return location;
}

void BaseEnemy::SetLocation(float x, float y)
{
    this->location = CP_Vector_Set(x, y);
}

void BaseEnemy::SetLocation(CP_Vector location)
{
    this->location = location;
}

CP_Vector BaseEnemy::GetDirectionVector(void)
{
    return directionVector;
}

void BaseEnemy::SetDirectionVector(float x, float y)
{
    this->directionVector = CP_Vector_Set(x, y);
}

void BaseEnemy::SetDirectionVector(CP_Vector direction)
{
    this->directionVector = direction;
}

EnemyType BaseEnemy::GetEnemyType(void)
{
    return type;
}

void BaseEnemy::SetEnemyType(EnemyType type)
{
    this->type = type;
}

void BaseEnemy::Move(Map* map)
{
    std::vector<CP_Vector> path = map->getPath();

    if (path.size() == pathId) return;

    // Move toward next location in queue
    SetDirectionVector(CP_Vector_Normalize(CP_Vector_Set(path[pathId].x - location.x, path[pathId].y - location.y)));

    location = CP_Vector_Add(location, CP_Vector_Scale(directionVector, speed * CP_System_GetDt()));

    // Remove location from queue when reached
    if (CP_Vector_Distance(location, path[pathId]) <= spriteSize * 0.25f)
        ++pathId;
}

void BaseEnemy::Render(void)
{
    if (directionVector.x > 0)
        CP_Image_Draw(sprite, location.x, location.y, spriteSize, spriteSize, 255);
    else if (directionVector.x < 0)
        CP_Image_Draw(spriteLeft, location.x, location.y, spriteSize, spriteSize, 255);

    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(location.x, location.y - spriteSize * 0.5f, (float)health / (float)maxHealth * 50.f, 10.f);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
}
