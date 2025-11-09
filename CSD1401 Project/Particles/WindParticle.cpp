#include "WindParticle.h"

WindParticle::WindParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
}

void WindParticle::Update()
{
    // drift in wind direction + slow fade
    CP_Vector accel = CP_Vector_Set(0.001f, 0.0f); // small constant rightward drift
    velocity = CP_Vector_Add(velocity, accel);

    // move and decay
    position = CP_Vector_Add(position, velocity);
    --life;
}

void WindParticle::Draw() const
{
    float t = (float)life / 60.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    // light blue fading
    int r = 150;
    int g = 200;
    int b = 255;
    int a = (int)(255 * t);

    float size = 5.0f * t + 2.0f;

    CP_Settings_Fill(CP_Color_Create(r, g, b, a));
    CP_Graphics_DrawEllipse(position.x, position.y, size, size);
}
