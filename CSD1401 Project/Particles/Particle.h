#pragma once
#include "cprocessing.h"

/*!
@file       Particle.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the Particle class
*//*_______________________________________________________________________*/

class Particle
{
public:
	CP_Vector position; // Current position of the particle
	CP_Vector velocity; // Current velocity of the particle
	int life; // Remaining life of the particle in frames

	Particle(const CP_Vector& pos, const CP_Vector& vel, int lifetime) // Constructor
        : position(pos), velocity(vel), life(lifetime) {
    }

	virtual ~Particle() = default; // Virtual destructor

	virtual void Update() = 0; // Pure virtual function to update the particle state
	virtual void Draw() const = 0; // Pure virtual function to draw the particle

	bool IsAlive() const { return life > 0; } // Check if the particle is still alive
};
