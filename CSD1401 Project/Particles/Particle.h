#pragma once
#include "cprocessing.h"

class Particle
{
public:
    CP_Vector position;
    CP_Vector velocity;
    int life;

    Particle(const CP_Vector& pos, const CP_Vector& vel, int lifetime)
        : position(pos), velocity(vel), life(lifetime) {
    }

    virtual ~Particle() = default;

    virtual void Update() = 0;
    virtual void Draw() const = 0;

    bool IsAlive() const { return life > 0; }
};
