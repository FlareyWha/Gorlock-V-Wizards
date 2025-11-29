#pragma once
#include "Particle.h"
#include "cprocessing.h"

/*!
@file       WindParticle.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the WindParticle class
*//*_______________________________________________________________________*/

class WindParticle : public Particle
{
public:
    WindParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime);
    void Update() override;
    void Draw() const override;
};

