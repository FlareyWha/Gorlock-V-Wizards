#include "FireParticle.h"
#include "cprocessing.h"

FireParticle::FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
    : Particle(pos, vel, lifetime)
{
    // optionally randomise initial state
}

void FireParticle::Update()
{
    // simple upward drift + slow horizontal damping + life decay
    // apply a little upwards acceleration (smaller than gravity — here flames go up)
    CP_Vector accel = CP_Vector_Set(0.0f, -0.002f);
    velocity = CP_Vector_Add(velocity, accel);

    // horizontal damping
    velocity.x *= 0.99f;

    // move and decay
    position = CP_Vector_Add(position, velocity);
    --life;
}

void FireParticle::Draw() const
{
    // color and size based on remaining life
    float t = (float)life / 60.0f; // assuming max lifetime ~60; clamp if needed
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;

    // interpolate color from yellow (young) to red -> transparent
    int r = (int)(255);
    int g = (int)(200 * t);  // fades out green component
    int b = 0;
    int a = (int)(255 * t);

    // size grows a bit then fades
    float size = 6.0f * (1.0f - t) + 2.0f; // tweak to taste

    CP_Settings_Fill(CP_Color_Create(r, g, b, a));
    CP_Graphics_DrawEllipse(position.x, position.y, size, size);
}