#include "BaseEnemy.h"
#include <stdio.h>
#include <stdlib.h>

float BaseEnemy::GetHealth(void)
{
    return health;
}

void BaseEnemy::SetHealth(float health)
{
    health >= 0 ? this->health = health : this->health = 0;
}

float BaseEnemy::GetMaxHealth(void)
{
    return maxHealth;
}

void BaseEnemy::SetMaxHealth(float health)
{
    this->maxHealth = health;
}

bool BaseEnemy::IsSlowed()
{
    return slowed;
}

void BaseEnemy::Slow(bool slow)
{
    this->slowed = slow;
}

bool BaseEnemy::IsBurned()
{
    return burned;
}

void BaseEnemy::Burn(bool burned)
{
    this->burned = burned;
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

float BaseEnemy::GetMaxSpeed(void)
{
    return maxSpeed;
}

void BaseEnemy::SetMaxSpeed(float maxSpeed)
{
    this->maxSpeed = maxSpeed;  
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
    printf("Health: %f\n", health);
    dotTimer += -1 * CP_System_GetDt();
    slowTimer += -1 * CP_System_GetDt();
    printf("Burn Timer: %f\n", burnTimer);
    burnTimer += -1 * CP_System_GetDt();
    std::vector<CP_Vector> path = map->getPath();

    if (path.size() == pathId) return;

    // Move toward next location in queue
    SetDirectionVector(CP_Vector_Normalize(CP_Vector_Set(path[pathId].x - location.x, path[pathId].y - location.y)));

    location = CP_Vector_Add(location, CP_Vector_Scale(directionVector, speed * CP_System_GetDt()));

    // Remove location from queue when reached
    if (CP_Vector_Distance(location, path[pathId]) <= spriteSize * 0.25f)
        ++pathId;

    if (slowed == true)
    {
        slowTimer = maxSlowTimer;
        slowed = false;
    }
    if (slowTimer <= 0)
    {
        speed = GetMaxSpeed();
    }
    else
    {
        SetSpeed(GetMaxSpeed() / 2.0f);
    }
    if (burned == true)
    {
        dotTimer = maxDOTTimer;
        burnStacks++;
        burnTimer = maxBurnTimer;
        burned = false;
        isBurning = true;
    }
    if (dotTimer <=0 && burnTimer >0 && isBurning)
    {
        SetHealth(GetHealth() - (burnDamage * burnStacks));
        printf("Burn Damage: %f\n", burnDamage * burnStacks);
        if (burnTimer >= maxDOTTimer)
        {
            dotTimer = maxDOTTimer;
        }
        else
        {
            isBurning = false;
            burnStacks = 0;
        }
    }
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
