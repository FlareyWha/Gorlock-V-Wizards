#include "WindParticle.h"

/*!
@file       WindParticle.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the implementation of the WindParticle class
*//*_______________________________________________________________________*/

/**
 @brief This will construct a wind particle
 @param pos The position of the particle
 @param vel The velocity of the particle
 @param lifetime The lifetime of the particle
 @return void
 */

WindParticle::WindParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
}

/**
 @brief Updates the wind particle
 @return void
 */

void WindParticle::Update()
{
    CP_Vector accel = CP_Vector_Set(0.001f, 0.0f);
    velocity = CP_Vector_Add(velocity, accel);

    position = CP_Vector_Add(position, velocity);
    --life;
}

/**
 @brief Draws the wind particle
 @return void
 */

void WindParticle::Draw() const
{
    float t = (float)life / 60.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    int r = 150;
    int g = 200;
    int b = 255;
    int a = (int)(255 * t);

    float size = 5.0f * t + 2.0f;

    CP_Settings_Fill(CP_Color_Create(r, g, b, a));
    CP_Graphics_DrawEllipse(position.x, position.y, size, size);
}
