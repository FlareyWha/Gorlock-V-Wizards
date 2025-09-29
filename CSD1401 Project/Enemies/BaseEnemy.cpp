#include "BaseEnemy.h"
#include <stdio.h>

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

Direction BaseEnemy::GetPrevDirection(void)
{
    return prevDirection;
}

void BaseEnemy::SetPrevDirection(Direction direction)
{
    this->prevDirection = direction;
}

void BaseEnemy::Move(Map* map)
{
    // Check tiles around enemy
    Tile tiles[9] = {};
    int tileId = 0;
    for (float y = -spriteSize; y <= spriteSize; y += spriteSize)
    {
        for (float x = -spriteSize; x <= spriteSize; x += spriteSize)
        {
            float tilePosX = location.x - 24.0f + x;
            float tilePosY = location.y - 24.0f + y;
            if (!(tilePosX < 0 || tilePosY < 0))
                tiles[tileId] = map->getTile(tilePosX, tilePosY);
            
            printf("%d ", tiles[tileId].tileType);

            ++tileId;
        }
        printf("\n");
    }
    printf("\n");
    
    // Move enemy to tile
    for (int i = 0; i < 9; ++i)
    {
        TILE_TYPE type = tiles[i].tileType;
        if (type > 100 && type <= 200)
        {
            switch (i)
            {
            case 1:     // Up
                if (prevDirection == DOWN)
                    continue;
                SetDirectionVector(0, -1);
                SetPrevDirection(DOWN);
                break;
            case 3:     // Left
                if (prevDirection == RIGHT)
                    continue;
                SetDirectionVector(-1, 0);
                SetPrevDirection(RIGHT);
                break;
            case 5:     // Right
                if (prevDirection == LEFT)
                    continue;
                SetDirectionVector(1, 0);
                SetPrevDirection(LEFT);
                break;
            case 7:     // Down
                if (prevDirection == UP)
                    continue;
                SetDirectionVector(0, 1);
                SetPrevDirection(UP);
                break;
            }
        }
    }

    location = CP_Vector_Add(location, CP_Vector_Scale(directionVector, speed * CP_System_GetDt()));
}

void BaseEnemy::Render(void)
{
    CP_Image_Draw(sprite, location.x, location.y, spriteSize, spriteSize, 255);
}
