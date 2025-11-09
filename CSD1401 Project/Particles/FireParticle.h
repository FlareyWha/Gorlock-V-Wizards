#pragma once
#include "Particle.h"
#include "cprocessing.h"

class FireParticle : public Particle
{
public:
    FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime);

    void Update() override;
    void Draw() const override;
};
