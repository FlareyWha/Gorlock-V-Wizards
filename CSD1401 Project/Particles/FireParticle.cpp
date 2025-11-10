#include "FireParticle.h"

CP_Image FireParticle::particleImage = 0;

FireParticle::FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
}

// Load image once
void FireParticle::LoadImage(const char* path)
{
    if (particleImage == 0)
        particleImage = CP_Image_Load(path);
}

void FireParticle::Update()
{
    // simple upward movement + slight spread
    CP_Vector accel = CP_Vector_Set(0.0f, -0.002f);
    velocity = CP_Vector_Add(velocity, accel);
    velocity.x *= 0.99f;
    position = CP_Vector_Add(position, velocity);
    --life;
}

void FireParticle::Draw() const
{
    if (particleImage == 0) return; // safety check

    float t = (float)life / 30.0f; // fade over lifetime
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    
    float size = 25.0f * (2.0f - t) + 4.0f;

    // Draw the particle image with alpha fade
    CP_Image_Draw(particleImage, position.x, position.y, size, size, 255 * t);
}
