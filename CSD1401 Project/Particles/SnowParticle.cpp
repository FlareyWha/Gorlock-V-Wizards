#include "SnowParticle.h"

/*!
@file       SnowParticle.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the implementation of the SnowParticle class
*//*_______________________________________________________________________*/

CP_Image SnowParticle::particleImage = 0;

/**
 @brief Will construct a snow particle
 @param pos The position of the particle
 @param vel The velocity of the particle
 @param lifetime The lifetime of the particle
 @return void
 */

SnowParticle::SnowParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
}

/**
 @brief The image for the snow particle is loaded
 @param path The file path of the image
 @return void
 */

void SnowParticle::LoadImage(const char* path)
{
    if (particleImage == 0)
        particleImage = CP_Image_Load(path);
}

/**
 @brief Will update the snow particle
 @return void
 */

void SnowParticle::Update()
{
    CP_Vector accel = CP_Vector_Set(0.0f, -0.002f);
    velocity = CP_Vector_Add(velocity, accel);
    velocity.x *= 0.99f;
    position = CP_Vector_Add(position, velocity);
    --life;
}

/**
 @brief Draws the snow particle
 @return void
 */

void SnowParticle::Draw() const
{
    if (particleImage == 0) return;

    float t = (float)life / 30.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;


    float size = 50.0f * (2.0f - t) + 4.0f;

    CP_Image_Draw(particleImage, position.x, position.y, size, size, (int)(255 * t));
}