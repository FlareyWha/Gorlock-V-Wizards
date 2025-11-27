#include "LightningParticle.h"
#include <math.h>
#include <cmath>
#include <cstdlib>

/*!
@file       LightningParticle.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the implementation of the LightningParticle class
*//*_______________________________________________________________________*/

const float PI = 3.14159265359f;

/**
 @brief This will construct a lightning particle
 @param start The starting position of the lightning
 @param len The length of the lightning
 @param ang The angle of the lightning
 @param lifetime The lifetime of the lightning
 @return void
 */

LightningParticle::LightningParticle(const CP_Vector& start, float len, float ang, int lifetime)
    : start(start), length(len), angle(ang), life(lifetime)
{
}

/**
 @brief Updates the lightning particle
 @return void
 */

void LightningParticle::Update()
{
    life--;
}

/**
 @brief Draws the lightning particle which are light streaks of lightnings
 @return void
 */

void LightningParticle::Draw() const
{
    if (life <= 0) return;

    CP_Settings_Stroke(CP_Color_Create(255, 255, 0, 255));

    int segments = 5;
    CP_Vector prev = start;
    const float PI = 3.14159265359f;

    for (int i = 1; i <= segments; i++)
    {
        float t = i / (float)segments;
        CP_Vector next;
        next.x = start.x + cos(angle) * length * t;
        next.y = start.y + sin(angle) * length * t;

        float offsetAmount = 3.0f;
        float perpendicularAngle = angle + PI / 2.0f;
        float offset = ((rand() % 100) / 100.0f - 0.5f) * 2 * offsetAmount;

        next.x += cos(perpendicularAngle) * offset;
        next.y += sin(perpendicularAngle) * offset;

        CP_Graphics_DrawLine(prev.x, prev.y, next.x, next.y);
        prev = next;
    }

    CP_Settings_Stroke(CP_Color_Create(0, 0, 0, 255));
}





