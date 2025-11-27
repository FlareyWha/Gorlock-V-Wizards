#pragma once
#include "Particle.h"
#include "cprocessing.h"

/*!
@file       FireParticle.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the FireParticle class
*//*_______________________________________________________________________*/

class FireParticle : public Particle
{
private:
    static CP_Image particleImage;
    
public:
    FireParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime);
    CP_Vector GetPosition() const { return position; }
    void Update() override;
    void Draw() const override;

    static void LoadImage(const char* path);
};