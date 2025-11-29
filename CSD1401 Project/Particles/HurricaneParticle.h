#pragma once
#include "Particle.h"
#include "cprocessing.h"

/*!
@file       HurricaneParticle.h
@author     Chee Kang(l.cheekang)
@brief      This file contains the declaration of the HurricaneParticle class
*//*_______________________________________________________________________*/

class HurricaneParticle : public Particle
{
private:
	static CP_Image particleImage; // Shared image for all hurricane particles

public:
	HurricaneParticle(const CP_Vector& pos, const CP_Vector& vel, int lifetime); // Constructor

	void Update() override; // Update the particle's state
	void Draw() const override; // Overides the current draw state and draws the particle

	static void LoadImage(const char* path); // Load the image for hurricane particles 
};

