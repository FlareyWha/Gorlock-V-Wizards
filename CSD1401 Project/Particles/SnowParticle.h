#pragma once
#include "Particle.h"
#include "cprocessing.h"

/*!
@file       SnowParticle.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the SnowParticle class
*//*_______________________________________________________________________*/

class SnowParticle : public Particle // Inherits from Particle
{
    private:
		static CP_Image particleImage; // Static image for all snow particles

    public:
		SnowParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime); // Constructor

		void Update() override; // Override Update method
		void Draw() const override; // Override Draw method

		static void LoadImage(const char* path); // Static method to load the particle image
};

