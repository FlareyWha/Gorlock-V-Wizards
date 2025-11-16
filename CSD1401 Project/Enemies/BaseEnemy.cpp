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

void BaseEnemy::Slow(bool slow,float slowFactor)
{
    this->slowed = slow;
    if (this->slowFactor > slowFactor)
    {
        this->slowFactor = slowFactor;
    }
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

void BaseEnemy::RandomizeTurn(void)
{
    turn = rand() % 2;
}

void BaseEnemy::Move(Map* map)
{
    dotTimer += -1 * CP_System_GetDt();
    slowTimer += -1 * CP_System_GetDt();
    burnTimer += -1 * CP_System_GetDt();

    // Start movement if enemy just spawned
    if (directionVector.x == 0 && directionVector.y == 0)
    {
        for (int x = -1; x < 2; x += 2)    // Check left and right
        {
            TILE_TYPE tileType = map->getTile(location.x + spriteSize * x, location.y).tileType;
            if (tileType >= MIDDLE_ROAD && tileType < STARTPOINT)
                directionVector.x = x;
        }
        for(int y = -1; y < 2; y += 2)    // Check up and down
        {
            if (directionVector.x != 0) break;
            TILE_TYPE tileType = map->getTile(location.x, location.y + spriteSize * y).tileType;
            if (tileType >= MIDDLE_ROAD && tileType < STARTPOINT)
                directionVector.y = y;
        }
    }

    // Get tile under enemy
    TILE_TYPE tileType = TOTAL;
    if (directionVector.x > 0) tileType = map->getTile(location.x - spriteSize * 0.5f, location.y).tileType;
    else if (directionVector.y > 0) tileType = map->getTile(location.x, location.y - spriteSize * 0.5f).tileType;
    else if (directionVector.x < 0) tileType = map->getTile(location.x + spriteSize * 0.5f, location.y).tileType;
    else if (directionVector.y < 0)
        tileType = map->getTile(location.x, location.y + spriteSize * 0.5f).tileType;

    switch (tileType)
    {
    case CORNER_TOP_LEFT_ROAD:
        if (directionVector.y < 0) directionVector = CP_Vector_Set(1, 0);
        else if (directionVector.x < 0) directionVector = CP_Vector_Set(0, 1);
        break;
    case CORNER_TOP_RIGHT_ROAD:
        if (directionVector.y < 0) directionVector = CP_Vector_Set(-1, 0);
        else if (directionVector.x > 0) directionVector = CP_Vector_Set(0, 1);
        break;
    case CORNER_BOTTOM_LEFT_ROAD:
        if (directionVector.y > 0) directionVector = CP_Vector_Set(1, 0);
        else if (directionVector.x < 0) directionVector = CP_Vector_Set(0, -1);
        break;
    case CORNER_BOTTOM_RIGHT_ROAD:
        if (directionVector.y > 0) directionVector = CP_Vector_Set(-1, 0);
        else if (directionVector.x > 0) directionVector = CP_Vector_Set(0, -1);
        break;
    }
    location = CP_Vector_Add(location, CP_Vector_Scale(directionVector, speed * CP_System_GetDt()));

    if (slowed == true)
    {
        slowTimer = maxSlowTimer;
        slowed = false;
    }
    if (slowTimer <= 0)
    {
        speed = GetMaxSpeed();
        slowFactor = 0.75f;
    }
    else
    {
        SetSpeed(GetMaxSpeed() * slowFactor);
    }

    if (burned == true)
    {
        //dotTimer = maxDOTTimer;
        burnStacks++;
        burnTimer = maxBurnTimer;
        burned = false;
        isBurning = true;
    }
    if (dotTimer <=0 && burnTimer > 0 && isBurning)
    {
        SetHealth(GetHealth() - (burnDamage * burnStacks));
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
    if (directionVector.x >= 0)
        CP_Image_Draw(sprite, location.x, location.y, spriteSize, spriteSize, 255);
    else if (directionVector.x <= 0)
        CP_Image_Draw(spriteLeft, location.x, location.y, spriteSize, spriteSize, 255);

    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(location.x, location.y - spriteSize * 0.5f, (float)health / (float)maxHealth * 50.f, 10.f);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
}
