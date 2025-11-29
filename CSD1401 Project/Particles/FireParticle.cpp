#include "FireParticle.h"

/*!
@file       FireParticle.cpp
@author     Chee Kang(l.cheekang)
@brief      This file contains the implementation of the FireParticle class
*//*_______________________________________________________________________*/

CP_Image FireParticle::particleImage = 0;

/**
 @brief Will construct a fire particle
 @param pos The position of the particle
 @param vel The velocity of the particle
 @param lifetime The lifetime of the particle
 @return void
 */
FireParticle::FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
}

/**
 @brief Loads the image for the fire particle
 @param path The file path of the image
 @return void
 */
void FireParticle::LoadImage(const char* path)
{
    if (particleImage == 0)
        particleImage = CP_Image_Load(path);
}

/**
 @brief Updates the fire particle
 @return void
 */
void FireParticle::Update()
{
    CP_Vector accel = CP_Vector_Set(0.0f, -0.002f);
    velocity = CP_Vector_Add(velocity, accel);
    velocity.x *= 0.99f;
    position = CP_Vector_Add(position, velocity);
    --life;
}

/**
 @brief Draws the fire particle
 @return void
 */
void FireParticle::Draw() const
{
    if (particleImage == 0) return;

    float t = (float)life / 30.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    
    float size = 50.0f * (2.0f - t) + 4.0f; //sets the size of the particle

    CP_Image_Draw(particleImage, position.x, position.y, size, size, (int)(255 * t));
}
