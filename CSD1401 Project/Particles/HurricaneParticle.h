#pragma once
#include "Particle.h"
#include "cprocessing.h"

class HurricaneParticle : public Particle
{
private:
    static CP_Image particleImage;

public:
    HurricaneParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime);

    void Update() override;
    void Draw() const override;

    static void LoadImage(const char* path);
};

