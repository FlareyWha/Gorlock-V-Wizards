#pragma once
#include "Particle.h"
#include "cprocessing.h"

// FireParticle inherits from Particle
class FireParticle : public Particle
{
public:
    // Constructor: position, velocity, lifetime in frames
    FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime);

    // Override virtual methods
    void Update() override;
    void Draw() const override;
};
