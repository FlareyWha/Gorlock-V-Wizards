#pragma once
#include "Particle.h"
#include "cprocessing.h"

class WindParticle : public Particle
{
public:
    WindParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime);
    void Update() override;
    void Draw() const override;
};

