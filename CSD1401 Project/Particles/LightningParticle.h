#pragma once
#include "cprocessing.h"

class LightningParticle
{

protected:
    CP_Vector start;
    float length;
    float angle;
    

public:

	int life;

    LightningParticle(const CP_Vector& start, float length, float angle, int life);

    void Update();
    void Draw() const;
};


