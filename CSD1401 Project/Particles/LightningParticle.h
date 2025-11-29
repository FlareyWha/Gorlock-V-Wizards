#pragma once
#include "cprocessing.h"

/*!
@file       LightningParticle.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the LightningParticle class
*//*_______________________________________________________________________*/

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


