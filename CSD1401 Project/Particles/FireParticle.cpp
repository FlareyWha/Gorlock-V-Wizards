#include "FireParticle.h"
#include "cprocessing.h"

FireParticle::FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
    // optionally randomise initial state
}

void FireParticle::Update()
{
    CP_Vector accel = CP_Vector_Set(0.0f, -0.002f);
    velocity = CP_Vector_Add(velocity, accel);

    velocity.x *= 0.99f;

    position = CP_Vector_Add(position, velocity);
    --life;
}

void FireParticle::Draw() const
{
    float t = (float)life / 60.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    int r = (int)(255);
    int g = (int)(200 * t);
    int b = 0;
    int a = (int)(255 * t);

    float size = 6.0f * (1.0f - t) + 2.0f;

    CP_Settings_Fill(CP_Color_Create(r, g, b, a));
    CP_Graphics_DrawEllipse(position.x, position.y, size, size);
}