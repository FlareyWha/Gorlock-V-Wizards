#include "BaseEnemy.h"
#include <stdio.h>
#include <stdlib.h>

int BaseEnemy::GetHealth(void)
{
    return health;
}

void BaseEnemy::SetHealth(int health)
{
    this->health = health;
}

float BaseEnemy::GetSpeed(void)
{
    return speed;
}

void BaseEnemy::SetSpeed(float speed)
{
    this->speed = speed;
}

CP_Image BaseEnemy::GetSprite(void)
{
    return sprite;
}

void BaseEnemy::SetSprite(CP_Image sprite)
{
    this->sprite = sprite;
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

void BaseEnemy::AddToPath(CP_Vector newPoint)
{
    path.push(newPoint);
}

void BaseEnemy::SetPath(Map* map, CP_Vector pos, CP_Vector oldPos)
{
    TILE_TYPE tileType = TILE_TYPE::NONE;
    for (int i = 0; i < 4; ++i)
    {
        switch (i)
        {
        case 0: // Up
            (pos.y - spriteSize) >= 0 ? tileType = map->getTile(pos.x, pos.y - spriteSize).tileType : tileType;
            if (((tileType > 100 && tileType <= 200) || tileType == 202) && CP_Vector_Distance(CP_Vector_Set(pos.x, pos.y - spriteSize), oldPos) != 0)
            {
                path.push(CP_Vector_Set(pos.x, pos.y - spriteSize));
                SetPath(map, CP_Vector_Set(pos.x, pos.y - spriteSize), pos);
            }
            break;
        case 1: // Left
            (pos.x - spriteSize) >= 0 ? tileType = map->getTile(pos.x - spriteSize, pos.y).tileType : tileType;
            if (((tileType > 100 && tileType <= 200) || tileType == 202) && CP_Vector_Distance(CP_Vector_Set(pos.x - spriteSize, pos.y), oldPos) != 0)
            {
                path.push(CP_Vector_Set(pos.x - spriteSize, pos.y));
                SetPath(map, CP_Vector_Set(pos.x - spriteSize, pos.y), pos);
            }
            break;
        case 2: // Down
            tileType = map->getTile(pos.x, pos.y + spriteSize).tileType;
            if (((tileType > 100 && tileType <= 200) || tileType == 202) && CP_Vector_Distance(CP_Vector_Set(pos.x, pos.y + spriteSize), oldPos) != 0)
            {
                path.push(CP_Vector_Set(pos.x, pos.y + spriteSize));
                SetPath(map, CP_Vector_Set(pos.x, pos.y + spriteSize), pos);
            }
            break;
        case 3: // Right
            tileType = map->getTile(pos.x + spriteSize, pos.y).tileType;
            if (((tileType > 100 && tileType <= 200) || tileType == 202) && CP_Vector_Distance(CP_Vector_Set(pos.x + spriteSize, pos.y), oldPos) != 0)
            {
                path.push(CP_Vector_Set(pos.x + spriteSize, pos.y));
                SetPath(map, CP_Vector_Set(pos.x + spriteSize, pos.y), pos);
            }
            break;
        }
    }
}

void BaseEnemy::Move()
{
    if (path.empty()) return;

    // Move toward next location in queue
    SetDirectionVector(CP_Vector_Normalize(CP_Vector_Set(path.front().x - location.x, path.front().y - location.y)));

    location = CP_Vector_Add(location, CP_Vector_Scale(directionVector, speed * CP_System_GetDt()));

    // Remove location from queue when reached
    if (CP_Vector_Distance(location, path.front()) <= spriteSize * 0.5f)
        path.pop();
}

void BaseEnemy::Render(void)
{
    CP_Image_Draw(sprite, location.x, location.y, spriteSize, spriteSize, 255);
}
